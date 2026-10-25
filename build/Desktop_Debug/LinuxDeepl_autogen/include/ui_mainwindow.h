/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *language_von;
    QPushButton *swap;
    QComboBox *language_nach;
    QLabel *lbl_txt_von;
    QLabel *lbl_txt_nach;
    QPlainTextEdit *txt_von;
    QPlainTextEdit *txt_nach;
    QPushButton *translate;
    QPushButton *copy_txt_von;
    QPushButton *copy_txt_nach;
    QPushButton *clear_txt_nach;
    QProgressBar *fortschritt;
    QPushButton *save_as;
    QLabel *lbl_txt_akt;
    QLCDNumber *lcdNr_akt;
    QPushButton *clear_txt_von;
    QLabel *rest_txt_monat;
    QLCDNumber *lcdNr_max;
    QLabel *Konstrukteure;
    QPushButton *btn_abo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(727, 440);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(153, 193, 241, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        MainWindow->setPalette(palette);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        language_von = new QComboBox(centralwidget);
        language_von->setObjectName("language_von");
        language_von->setGeometry(QRect(110, 50, 181, 27));
        swap = new QPushButton(centralwidget);
        swap->setObjectName("swap");
        swap->setGeometry(QRect(335, 50, 51, 27));
        QPalette palette1;
        QBrush brush2(QColor(51, 209, 122, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush2);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush2);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush2);
        swap->setPalette(palette1);
        language_nach = new QComboBox(centralwidget);
        language_nach->setObjectName("language_nach");
        language_nach->setGeometry(QRect(480, 50, 181, 27));
        lbl_txt_von = new QLabel(centralwidget);
        lbl_txt_von->setObjectName("lbl_txt_von");
        lbl_txt_von->setGeometry(QRect(60, 50, 41, 27));
        lbl_txt_von->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lbl_txt_nach = new QLabel(centralwidget);
        lbl_txt_nach->setObjectName("lbl_txt_nach");
        lbl_txt_nach->setGeometry(QRect(420, 50, 41, 27));
        lbl_txt_nach->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        txt_von = new QPlainTextEdit(centralwidget);
        txt_von->setObjectName("txt_von");
        txt_von->setGeometry(QRect(60, 90, 291, 141));
        txt_nach = new QPlainTextEdit(centralwidget);
        txt_nach->setObjectName("txt_nach");
        txt_nach->setGeometry(QRect(370, 90, 291, 141));
        translate = new QPushButton(centralwidget);
        translate->setObjectName("translate");
        translate->setGeometry(QRect(60, 310, 101, 71));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush2);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush2);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush2);
        translate->setPalette(palette2);
        copy_txt_von = new QPushButton(centralwidget);
        copy_txt_von->setObjectName("copy_txt_von");
        copy_txt_von->setGeometry(QRect(280, 310, 71, 27));
        QPalette palette3;
        QBrush brush3(QColor(192, 191, 188, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush3);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush3);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush3);
        copy_txt_von->setPalette(palette3);
        copy_txt_nach = new QPushButton(centralwidget);
        copy_txt_nach->setObjectName("copy_txt_nach");
        copy_txt_nach->setGeometry(QRect(370, 310, 71, 27));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush3);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush3);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush3);
        copy_txt_nach->setPalette(palette4);
        clear_txt_nach = new QPushButton(centralwidget);
        clear_txt_nach->setObjectName("clear_txt_nach");
        clear_txt_nach->setGeometry(QRect(450, 310, 61, 27));
        QPalette palette5;
        QBrush brush4(QColor(255, 163, 72, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush4);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush4);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush4);
        clear_txt_nach->setPalette(palette5);
        fortschritt = new QProgressBar(centralwidget);
        fortschritt->setObjectName("fortschritt");
        fortschritt->setGeometry(QRect(170, 350, 491, 31));
        fortschritt->setValue(24);
        save_as = new QPushButton(centralwidget);
        save_as->setObjectName("save_as");
        save_as->setGeometry(QRect(560, 310, 101, 27));
        QPalette palette6;
        QBrush brush5(QColor(237, 51, 59, 255));
        brush5.setStyle(Qt::BrushStyle::SolidPattern);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush5);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush5);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush5);
        save_as->setPalette(palette6);
        lbl_txt_akt = new QLabel(centralwidget);
        lbl_txt_akt->setObjectName("lbl_txt_akt");
        lbl_txt_akt->setGeometry(QRect(60, 250, 131, 20));
        lbl_txt_akt->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lcdNr_akt = new QLCDNumber(centralwidget);
        lcdNr_akt->setObjectName("lcdNr_akt");
        lcdNr_akt->setGeometry(QRect(200, 250, 71, 23));
        QPalette palette7;
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        lcdNr_akt->setPalette(palette7);
        lcdNr_akt->setFrameShape(QFrame::Shape::NoFrame);
        lcdNr_akt->setFrameShadow(QFrame::Shadow::Raised);
        lcdNr_akt->setSmallDecimalPoint(false);
        lcdNr_akt->setDigitCount(7);
        lcdNr_akt->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);
        lcdNr_akt->setProperty("intValue", QVariant(500000));
        clear_txt_von = new QPushButton(centralwidget);
        clear_txt_von->setObjectName("clear_txt_von");
        clear_txt_von->setGeometry(QRect(210, 310, 61, 27));
        QPalette palette8;
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush4);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush4);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush4);
        clear_txt_von->setPalette(palette8);
        rest_txt_monat = new QLabel(centralwidget);
        rest_txt_monat->setObjectName("rest_txt_monat");
        rest_txt_monat->setGeometry(QRect(440, 250, 221, 20));
        rest_txt_monat->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lcdNr_max = new QLCDNumber(centralwidget);
        lcdNr_max->setObjectName("lcdNr_max");
        lcdNr_max->setGeometry(QRect(370, 250, 71, 23));
        lcdNr_max->setFrameShape(QFrame::Shape::NoFrame);
        lcdNr_max->setFrameShadow(QFrame::Shadow::Raised);
        lcdNr_max->setDigitCount(7);
        lcdNr_max->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);
        lcdNr_max->setProperty("intValue", QVariant(500000));
        Konstrukteure = new QLabel(centralwidget);
        Konstrukteure->setObjectName("Konstrukteure");
        Konstrukteure->setGeometry(QRect(60, 280, 601, 20));
        Konstrukteure->setStyleSheet(QString::fromUtf8("background-color: #e5e5e5;"));
        Konstrukteure->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btn_abo = new QPushButton(centralwidget);
        btn_abo->setObjectName("btn_abo");
        btn_abo->setGeometry(QRect(320, 250, 31, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 727, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "LinuxDeepl \342\200\223 DeepL-\303\234bersetzer", nullptr));
        swap->setText(QCoreApplication::translate("MainWindow", "swap", nullptr));
        lbl_txt_von->setText(QCoreApplication::translate("MainWindow", "von:", nullptr));
        lbl_txt_nach->setText(QCoreApplication::translate("MainWindow", "nach:", nullptr));
        translate->setText(QCoreApplication::translate("MainWindow", "\303\234bersetzen", nullptr));
        copy_txt_von->setText(QCoreApplication::translate("MainWindow", "kopieren", nullptr));
        copy_txt_nach->setText(QCoreApplication::translate("MainWindow", "kopieren", nullptr));
        clear_txt_nach->setText(QCoreApplication::translate("MainWindow", "leeren", nullptr));
        save_as->setText(QCoreApplication::translate("MainWindow", "speichern...", nullptr));
        lbl_txt_akt->setText(QCoreApplication::translate("MainWindow", "aktuelle Zeichen:", nullptr));
        clear_txt_von->setText(QCoreApplication::translate("MainWindow", "leeren", nullptr));
        rest_txt_monat->setText(QCoreApplication::translate("MainWindow", "verbleibende Zeichen / Periode", nullptr));
        Konstrukteure->setText(QCoreApplication::translate("MainWindow", "Rig & Deek w\303\274nschen allen Spa\303\237 im Leben !", nullptr));
        btn_abo->setText(QCoreApplication::translate("MainWindow", "Abo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
