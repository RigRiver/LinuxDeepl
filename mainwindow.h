#pragma once
#include <QMainWindow>

namespace Ui { class MainWindow; }

class QNetworkAccessManager;
class QNetworkReply;
class QCloseEvent;
class QTextToSpeech;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onSwap();
    void onOpenAboPage();
    void onTranslate();
    void onCopyFrom();
    void onCopyTo();
    void onClearFrom();
    void onClearTo();
    void writePiperConf(const QString &langCode);
    void onSave();
    void onInputChanged();

    void onTranslateReplyFinished(QNetworkReply *reply);
    void onUsageReplyFinished(QNetworkReply *reply);

    void onSpeakFrom();
    void onSpeakTo();

private:
    void populateLanguages();
    void readSettings();
    void writeSettings();

    void refetchUsage();
    void handleNetworkError(QNetworkReply *reply);
    void setBusy(bool busy);
    void updateTranslateEnabled();

    QTextToSpeech *m_speech = nullptr;

    Ui::MainWindow         *ui;
    QNetworkAccessManager  *m_network = nullptr;
    qint64                  m_remaining = -1;   // -1 = unbekannt
};