#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QLCDNumber>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QClipboard>
#include <QApplication>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QStatusBar>
#include <QCloseEvent>
#include <QVector>

#include <QDesktopServices>
#include <QUrl>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

struct Lang { const char *code; const char *name; };

static const QVector<Lang> sourceLangs = {
    {"auto", "Automatisch erkennen"},
    {"AR","Arabisch"},{"BG","Bulgarisch"},{"ZH","Chinesisch"},
    {"DA","Dänisch"},{"DE","Deutsch"},{"EN","Englisch"},
    {"ET","Estnisch"},{"FI","Finnisch"},{"FR","Französisch"},
    {"EL","Griechisch"},{"ID","Indonesisch"},{"IT","Italienisch"},
    {"JA","Japanisch"},{"KO","Koreanisch"},{"LV","Lettisch"},
    {"LT","Litauisch"},{"NL","Niederländisch"},{"NB","Norwegisch"},
    {"PL","Polnisch"},{"PT","Portugiesisch"},{"RO","Rumänisch"},
    {"RU","Russisch"},{"SV","Schwedisch"},{"SK","Slowakisch"},
    {"SL","Slowenisch"},{"ES","Spanisch"},{"CS","Tschechisch"},
    {"TR","Türkisch"},{"HU","Ungarisch"},{"UK","Ukrainisch"},
    };

static const QVector<Lang> targetLangs = {
    {"AR","Arabisch"},{"BG","Bulgarisch"},{"ZH","Chinesisch (vereinfacht)"},
    {"ZH-HANT","Chinesisch (traditionell)"},{"DA","Dänisch"},
    {"DE","Deutsch"},{"EN-GB","Englisch (UK)"},{"EN-US","Englisch (US)"},
    {"ET","Estnisch"},{"FI","Finnisch"},{"FR","Französisch"},
    {"EL","Griechisch"},{"ID","Indonesisch"},{"IT","Italienisch"},
    {"JA","Japanisch"},{"KO","Koreanisch"},{"LV","Lettisch"},
    {"LT","Litauisch"},{"NL","Niederländisch"},{"NB","Norwegisch"},
    {"PL","Polnisch"},{"PT-BR","Portugiesisch (Brasilien)"},
    {"PT-PT","Portugiesisch (Portugal)"},{"RO","Rumänisch"},
    {"RU","Russisch"},{"SV","Schwedisch"},{"SK","Slowakisch"},
    {"SL","Slowenisch"},{"ES","Spanisch"},{"CS","Tschechisch"},
    {"TR","Türkisch"},{"HU","Ungarisch"},{"UK","Ukrainisch"},
    };

// ---------------------------------------------------------------- Konstruktor

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->txt_nach->setReadOnly(true);
    ui->fortschritt->setVisible(false);
    ui->fortschritt->setRange(0, 0);   // indeterminate
    ui->translate->setEnabled(false);
    ui->lcdNr_akt->display(0);

    populateLanguages();

    m_network = new QNetworkAccessManager(this);

    // Signale
    connect(ui->swap,          &QPushButton::clicked, this, &MainWindow::onSwap);
    connect(ui->translate,     &QPushButton::clicked, this, &MainWindow::onTranslate);
    connect(ui->btn_abo, &QPushButton::clicked, this, &MainWindow::onOpenAboPage);
    connect(ui->copy_txt_von,  &QPushButton::clicked, this, &MainWindow::onCopyFrom);
    connect(ui->copy_txt_nach, &QPushButton::clicked, this, &MainWindow::onCopyTo);
    connect(ui->clear_txt_von, &QPushButton::clicked, this, &MainWindow::onClearFrom);
    connect(ui->clear_txt_nach,&QPushButton::clicked, this, &MainWindow::onClearTo);
    connect(ui->save_as,       &QPushButton::clicked, this, &MainWindow::onSave);
    connect(ui->txt_von, &QPlainTextEdit::textChanged, this, &MainWindow::onInputChanged);

    readSettings();

    // Kontingent holen — nur wenn ein Key existiert
    QSettings s;
    if (!s.value("deepl/api_key").toString().trimmed().isEmpty()) {
        refetchUsage();
        statusBar()->showMessage(tr("Bereit"));
    } else {
        statusBar()->showMessage(
            tr("Kein API-Key — wird beim ersten Übersetzen abgefragt"));
    }
}

MainWindow::~MainWindow() { delete ui; }

// ------------------------------------------------------------------ Sprachen

void MainWindow::populateLanguages()
{
    for (const auto &l : sourceLangs)
        ui->language_von->addItem(QString::fromUtf8(l.name), QString::fromLatin1(l.code));
    for (const auto &l : targetLangs)
        ui->language_nach->addItem(QString::fromUtf8(l.name), QString::fromLatin1(l.code));

    ui->language_von->setCurrentIndex(0);   // Auto
    int idx = ui->language_nach->findData("DE");
    ui->language_nach->setCurrentIndex(idx >= 0 ? idx : 0);
}

// ------------------------------------------------------------------ Slots

void MainWindow::onSwap()
{
    const QString src = ui->language_von->currentData().toString();
    const QString tgt = ui->language_nach->currentData().toString();

    if (src == "auto") {
        statusBar()->showMessage(tr("Tausch nicht möglich: Quelle = Automatisch erkennen"));
        return;
    }

    int srcIdx = ui->language_von->findData(tgt);
    int tgtIdx = ui->language_nach->findData(src);
    if (srcIdx >= 0) ui->language_von->setCurrentIndex(srcIdx);
    if (tgtIdx >= 0) ui->language_nach->setCurrentIndex(tgtIdx);

    const QString in  = ui->txt_von->toPlainText();
    const QString out = ui->txt_nach->toPlainText();
    ui->txt_von->setPlainText(out);
    ui->txt_nach->setPlainText(in);

    statusBar()->showMessage(tr("Sprachen und Text getauscht"));
}

void MainWindow::onOpenAboPage()
{
    QDesktopServices::openUrl(QUrl("https://www.deepl.com/de/pro/change-plan#api"));
}

void MainWindow::onTranslate()
{
    QSettings s;
    QString apiKey = s.value("deepl/api_key").toString().trimmed();

    // Erststart / Key fehlt → einmalig abfragen
    if (apiKey.isEmpty()) {
        bool ok = false;
        // Der erklärende Text mit dem Link zur DeepL-Produktseite
        const QString dialogText =
            tr("DeepL API-Key eingeben (endet auf \":fx\")\n\n"
               "⚠ NUR API-Key — KEIN Pro-Abo!\n"
               "Ein Translator-Abo (Web/Desktop) funktioniert hier NICHT.\n\n"
               "Kostenlosen API-Key holen (1.000.000 Zeichen, einmalig):\n"
               "https://www.deepl.com/de/developers\n\n"
               "Hinweis: Die E-Mail für den Gratis-Key kann später für ein "
               "kostenpflichtiges Abo blockiert sein — ggf. andere E-Mail nutzen.");

        apiKey = QInputDialog::getText(
                     this, tr("DeepL API-Key einrichten"),
                     dialogText,
                     QLineEdit::Password, QString(), &ok).trimmed();

        if (!ok || apiKey.isEmpty()) {
            statusBar()->showMessage(tr("Ohne API-Key keine Übersetzung"));
            return;
        }
        s.setValue("deepl/api_key", apiKey);
    }


    const QString text = ui->txt_von->toPlainText().trimmed();
    if (text.isEmpty()) {
        statusBar()->showMessage(tr("Kein Text zum Übersetzen"));
        return;
    }

    const QString targetCode = ui->language_nach->currentData().toString();
    const QString sourceCode = ui->language_von->currentData().toString();

    QJsonObject body;
    body["text"]        = QJsonArray{ text };
    body["target_lang"] = targetCode;
    if (sourceCode != "auto")
        body["source_lang"] = sourceCode;

    QNetworkRequest req(QUrl("https://api-free.deepl.com/v2/translate"));
    req.setRawHeader("Authorization", ("DeepL-Auth-Key " + apiKey).toUtf8());
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setTransferTimeout(20000);

    setBusy(true);

    QNetworkReply *reply = m_network->post(
        req, QJsonDocument(body).toJson(QJsonDocument::Compact));

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onTranslateReplyFinished(reply);
        reply->deleteLater();
    });
}

void MainWindow::onTranslateReplyFinished(QNetworkReply *reply)
{
    setBusy(false);

    if (reply->error() != QNetworkReply::NoError) {
        handleNetworkError(reply);
        return;
    }

    const QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.isObject()) {
        statusBar()->showMessage(tr("Ungültige Antwort von DeepL"));
        return;
    }

    const QJsonArray arr = doc.object().value("translations").toArray();
    if (arr.isEmpty()) {
        statusBar()->showMessage(tr("Keine Übersetzung erhalten"));
        return;
    }

    const QJsonObject first = arr.first().toObject();
    const QString translated = first.value("text").toString();
    const QString detected   = first.value("detected_source_language").toString();

    ui->txt_nach->setPlainText(translated);

    QString msg = tr("Übersetzt");
    if (!detected.isEmpty() && ui->language_von->currentData().toString() == "auto")
        msg += tr(" (erkannt: %1)").arg(detected);
    statusBar()->showMessage(msg);
    // Erkannte Sprache in die Quell-ComboBox übernehmen (nur bei "Auto")
    if (ui->language_von->currentData().toString() == "auto" && !detected.isEmpty()) {
        int idx = ui->language_von->findData(detected);
        if (idx >= 0) {
            ui->language_von->setCurrentIndex(idx);
        }
    }
    refetchUsage();
}

void MainWindow::onCopyFrom()
{
    QApplication::clipboard()->setText(ui->txt_von->toPlainText());
    statusBar()->showMessage(tr("Eingabe in Zwischenablage kopiert"));
}

void MainWindow::onCopyTo()
{
    QApplication::clipboard()->setText(ui->txt_nach->toPlainText());
    statusBar()->showMessage(tr("Übersetzung in Zwischenablage kopiert"));
}

void MainWindow::onClearFrom()
{
    ui->txt_von->clear();
    statusBar()->showMessage(tr("Eingabe geleert"));
}

void MainWindow::onClearTo()
{
    ui->txt_nach->clear();
    statusBar()->showMessage(tr("Übersetzung geleert"));
}

void MainWindow::onSave()
{
    const QString text = ui->txt_nach->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::information(this, tr("Speichern"), tr("Kein Text zum Speichern."));
        return;
    }
    const QString path = QFileDialog::getSaveFileName(
        this, tr("Übersetzung speichern"), QString(),
        tr("Textdatei (*.txt);;Markdown (*.md);;Alle Dateien (*)"));
    if (path.isEmpty()) return;

    QFile f(path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Fehler"), tr("Konnte Datei nicht schreiben."));
        return;
    }
    QTextStream ts(&f);
    ts << text;
    statusBar()->showMessage(tr("Gespeichert: %1").arg(path));
}

void MainWindow::onInputChanged()
{
    ui->lcdNr_akt->display(static_cast<int>(ui->txt_von->toPlainText().size()));    updateTranslateEnabled();
}

// ------------------------------------------------------------- Usage-Abfrage

void MainWindow::refetchUsage()
{
    QSettings s;
    const QString apiKey = s.value("deepl/api_key").toString().trimmed();
    if (apiKey.isEmpty()) return;

    QNetworkRequest req(QUrl("https://api-free.deepl.com/v2/usage"));
    req.setRawHeader("Authorization", ("DeepL-Auth-Key " + apiKey).toUtf8());
    req.setTransferTimeout(10000);

    QNetworkReply *reply = m_network->get(req);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onUsageReplyFinished(reply);
        reply->deleteLater();
    });
}

void MainWindow::onUsageReplyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        // Bei Usage-Fehler nicht mit Dialog nerven — nur Status
        const int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (status == 401 || status == 403)
            statusBar()->showMessage(tr("API-Key ungültig (Usage-Abfrage)"));
        return;
    }

    const QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.isObject()) return;

    const QJsonObject obj = doc.object();
    const qint64 count = obj.value("character_count").toVariant().toLongLong();
    const qint64 limit = obj.value("character_limit").toVariant().toLongLong();
    const qint64 remaining = (limit > count) ? (limit - count) : 0;

    m_remaining = remaining;
    ui->lcdNr_max->display(static_cast<int>(remaining));
    updateTranslateEnabled();

    statusBar()->showMessage(
        tr("Kontingent: %1 von %2 Zeichen verbraucht — verbleibend: %3")
            .arg(count).arg(limit).arg(remaining));
}

// ---------------------------------------------------------------- Fehler

void MainWindow::handleNetworkError(QNetworkReply *reply)
{
    const int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (reply->error() == QNetworkReply::OperationCanceledError ||
        reply->error() == QNetworkReply::TimeoutError) {
        statusBar()->showMessage(tr("Keine Antwort von DeepL (Timeout)"));
        return;
    }

    switch (status) {
    case 401:
    case 403:
        QMessageBox::warning(this, tr("API-Key ungültig"),
                             tr("DeepL hat den API-Key abgelehnt.\n\n"
                                "Der Key wird aus den Einstellungen entfernt.\n"
                                "Beim nächsten Übersetzen wirst du neu gefragt."));
        {
            QSettings s;
            s.remove("deepl/api_key");
        }
        statusBar()->showMessage(tr("API-Key ungültig — bitte neu eingeben"));
        break;

    case 456:
        QMessageBox::information(this, tr("Kontingent verbraucht"),
                                 tr("Kontingent Free verbraucht.\n"
                                    "DeepL vergibt neues Kontingent."));
        statusBar()->showMessage(tr("Kontingent verbraucht — warte auf Reset"));
        m_remaining = 0;
        ui->lcdNr_max->display(0);
        updateTranslateEnabled();
        break;

    case 429:
        QMessageBox::warning(this, tr("Zu viele Anfragen"),
                             tr("DeepL bittet um eine kurze Pause.\n"
                                "Bitte in ein paar Sekunden erneut versuchen."));
        statusBar()->showMessage(tr("Zu viele Anfragen — kurz warten"));
        break;

    default:
        statusBar()->showMessage(
            tr("Fehler %1: %2").arg(status).arg(reply->errorString()));
        break;
    }
}

// ---------------------------------------------------------------- Helfer

void MainWindow::setBusy(bool busy)
{
    ui->swap->setEnabled(!busy);
    ui->language_von->setEnabled(!busy);
    ui->language_nach->setEnabled(!busy);
    ui->copy_txt_nach->setEnabled(!busy);
    ui->clear_txt_nach->setEnabled(!busy);
    ui->save_as->setEnabled(!busy);

    ui->fortschritt->setVisible(busy);
    if (busy) {
        ui->translate->setEnabled(false);
        statusBar()->showMessage(tr("Übersetze…"));
    } else {
        updateTranslateEnabled();
    }
}

void MainWindow::updateTranslateEnabled()
{
    const bool hasText = !ui->txt_von->toPlainText().trimmed().isEmpty();
    const bool hasQuota = (m_remaining != 0);
    ui->translate->setEnabled(hasText && hasQuota && ui->fortschritt->isHidden());
}

// ---------------------------------------------------------------- Settings

void MainWindow::readSettings()
{
    QSettings s;

    const QString srcCode = s.value("lang/source", "auto").toString();
    const QString tgtCode = s.value("lang/target", "DE").toString();

    int srcIdx = ui->language_von->findData(srcCode);
    if (srcIdx >= 0) ui->language_von->setCurrentIndex(srcIdx);
    int tgtIdx = ui->language_nach->findData(tgtCode);
    if (tgtIdx >= 0) ui->language_nach->setCurrentIndex(tgtIdx);

    ui->txt_von->setPlainText(s.value("text/input").toString());
    ui->txt_nach->setPlainText(s.value("text/output").toString());

ui->lcdNr_akt->display(static_cast<int>(ui->txt_von->toPlainText().size()));    updateTranslateEnabled();
}

void MainWindow::writeSettings()
{
    QSettings s;
    s.setValue("lang/source", ui->language_von->currentData().toString());
    s.setValue("lang/target", ui->language_nach->currentData().toString());
    s.setValue("text/input",  ui->txt_von->toPlainText());
    s.setValue("text/output", ui->txt_nach->toPlainText());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    QMainWindow::closeEvent(event);
}