/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QWidget *centralwidget;
    QTabWidget *tab;
    QWidget *homeTab;
    QProgressBar *battProgBar;
    QLabel *currentSpeedLabel;
    QLabel *battCapLabel;
    QTextBrowser *rangeBox;
    QLabel *rangeLabel;
    QTextBrowser *modeBox;
    QLabel *modeLabel;
    QPushButton *ecoPushButton;
    QPushButton *normPushButton;
    QPushButton *racePushButton;
    QLabel *kmhrsLabel;
    QTextBrowser *timeBox;
    QLabel *timeLabel;
    QWidget *ddTab;
    QLabel *speedLabel;
    QTextBrowser *speedBox;
    QLabel *topSpeedLabel;
    QTextBrowser *topSpeedBox;
    QLabel *rangeLabel_2;
    QTextBrowser *rangeBox_2;
    QLabel *modeLabel_2;
    QTextBrowser *modeBox_2;
    QTextBrowser *longitudeBox;
    QLabel *longitudeLabel;
    QLabel *latitudeLabel;
    QTextBrowser *latitudeBox;
    QWidget *batteryTab;
    QLabel *battEstTotCapLabel;
    QTextBrowser *battEstTotCapBox;
    QLabel *battEstCapLeftLabel;
    QTextBrowser *battEstCapLeftBox;
    QLabel *currentBattTempLabel;
    QProgressBar *battProgBar_2;
    QLabel *battCapLabel_2;
    QLabel *peakBattTempLabel;
    QTextBrowser *currentBattTempBox;
    QTextBrowser *peakBattTempBox;
    QWidget *mpTab;
    QWidget *alarmTab;
    QTextBrowser *AlarmTextBox;
    QWidget *shutdownTab;
    QPushButton *shutdownButton;
    QPushButton *rebootButton;
    QPushButton *testKillAllButton;

    void setupUi(QMainWindow *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName(QString::fromUtf8("Home"));
        Home->resize(800, 480);
        Home->setMaximumSize(QSize(800, 480));
        centralwidget = new QWidget(Home);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tab = new QTabWidget(centralwidget);
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setGeometry(QRect(0, 0, 800, 480));
        tab->setMaximumSize(QSize(800, 480));
        tab->setIconSize(QSize(16, 16));
        tab->setMovable(false);
        tab->setTabBarAutoHide(true);
        homeTab = new QWidget();
        homeTab->setObjectName(QString::fromUtf8("homeTab"));
        battProgBar = new QProgressBar(homeTab);
        battProgBar->setObjectName(QString::fromUtf8("battProgBar"));
        battProgBar->setGeometry(QRect(10, 380, 511, 61));
        QFont font;
        font.setPointSize(32);
        battProgBar->setFont(font);
        battProgBar->setValue(0);
        currentSpeedLabel = new QLabel(homeTab);
        currentSpeedLabel->setObjectName(QString::fromUtf8("currentSpeedLabel"));
        currentSpeedLabel->setGeometry(QRect(40, 20, 341, 191));
        QFont font1;
        font1.setPointSize(160);
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        currentSpeedLabel->setFont(font1);
        currentSpeedLabel->setTextFormat(Qt::PlainText);
        battCapLabel = new QLabel(homeTab);
        battCapLabel->setObjectName(QString::fromUtf8("battCapLabel"));
        battCapLabel->setGeometry(QRect(10, 340, 421, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Ubuntu"));
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        battCapLabel->setFont(font2);
        rangeBox = new QTextBrowser(homeTab);
        rangeBox->setObjectName(QString::fromUtf8("rangeBox"));
        rangeBox->setGeometry(QRect(610, 10, 171, 61));
        rangeLabel = new QLabel(homeTab);
        rangeLabel->setObjectName(QString::fromUtf8("rangeLabel"));
        rangeLabel->setGeometry(QRect(430, 20, 191, 41));
        QFont font3;
        font3.setPointSize(18);
        rangeLabel->setFont(font3);
        modeBox = new QTextBrowser(homeTab);
        modeBox->setObjectName(QString::fromUtf8("modeBox"));
        modeBox->setGeometry(QRect(610, 90, 171, 61));
        modeLabel = new QLabel(homeTab);
        modeLabel->setObjectName(QString::fromUtf8("modeLabel"));
        modeLabel->setGeometry(QRect(430, 90, 161, 51));
        modeLabel->setFont(font3);
        ecoPushButton = new QPushButton(homeTab);
        ecoPushButton->setObjectName(QString::fromUtf8("ecoPushButton"));
        ecoPushButton->setGeometry(QRect(440, 170, 101, 81));
        QFont font4;
        font4.setPointSize(12);
        ecoPushButton->setFont(font4);
        normPushButton = new QPushButton(homeTab);
        normPushButton->setObjectName(QString::fromUtf8("normPushButton"));
        normPushButton->setGeometry(QRect(560, 170, 101, 81));
        normPushButton->setFont(font4);
        racePushButton = new QPushButton(homeTab);
        racePushButton->setObjectName(QString::fromUtf8("racePushButton"));
        racePushButton->setGeometry(QRect(680, 170, 101, 81));
        racePushButton->setFont(font4);
        kmhrsLabel = new QLabel(homeTab);
        kmhrsLabel->setObjectName(QString::fromUtf8("kmhrsLabel"));
        kmhrsLabel->setGeometry(QRect(190, 210, 241, 71));
        QFont font5;
        font5.setPointSize(60);
        font5.setBold(true);
        font5.setWeight(75);
        kmhrsLabel->setFont(font5);
        timeBox = new QTextBrowser(homeTab);
        timeBox->setObjectName(QString::fromUtf8("timeBox"));
        timeBox->setGeometry(QRect(580, 370, 181, 71));
        timeLabel = new QLabel(homeTab);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setGeometry(QRect(580, 330, 81, 41));
        timeLabel->setFont(font2);
        tab->addTab(homeTab, QString());
        ddTab = new QWidget();
        ddTab->setObjectName(QString::fromUtf8("ddTab"));
        speedLabel = new QLabel(ddTab);
        speedLabel->setObjectName(QString::fromUtf8("speedLabel"));
        speedLabel->setGeometry(QRect(20, 30, 111, 41));
        QFont font6;
        font6.setPointSize(20);
        speedLabel->setFont(font6);
        speedBox = new QTextBrowser(ddTab);
        speedBox->setObjectName(QString::fromUtf8("speedBox"));
        speedBox->setGeometry(QRect(240, 20, 161, 61));
        QFont font7;
        font7.setPointSize(22);
        speedBox->setFont(font7);
        topSpeedLabel = new QLabel(ddTab);
        topSpeedLabel->setObjectName(QString::fromUtf8("topSpeedLabel"));
        topSpeedLabel->setGeometry(QRect(20, 110, 151, 41));
        topSpeedLabel->setFont(font6);
        topSpeedBox = new QTextBrowser(ddTab);
        topSpeedBox->setObjectName(QString::fromUtf8("topSpeedBox"));
        topSpeedBox->setGeometry(QRect(240, 100, 161, 61));
        topSpeedBox->setFont(font7);
        rangeLabel_2 = new QLabel(ddTab);
        rangeLabel_2->setObjectName(QString::fromUtf8("rangeLabel_2"));
        rangeLabel_2->setGeometry(QRect(20, 190, 121, 41));
        rangeLabel_2->setFont(font7);
        rangeBox_2 = new QTextBrowser(ddTab);
        rangeBox_2->setObjectName(QString::fromUtf8("rangeBox_2"));
        rangeBox_2->setGeometry(QRect(240, 180, 161, 61));
        modeLabel_2 = new QLabel(ddTab);
        modeLabel_2->setObjectName(QString::fromUtf8("modeLabel_2"));
        modeLabel_2->setGeometry(QRect(20, 270, 191, 41));
        modeLabel_2->setFont(font7);
        modeBox_2 = new QTextBrowser(ddTab);
        modeBox_2->setObjectName(QString::fromUtf8("modeBox_2"));
        modeBox_2->setGeometry(QRect(240, 260, 161, 61));
        longitudeBox = new QTextBrowser(ddTab);
        longitudeBox->setObjectName(QString::fromUtf8("longitudeBox"));
        longitudeBox->setGeometry(QRect(630, 20, 151, 61));
        longitudeBox->setFont(font7);
        longitudeLabel = new QLabel(ddTab);
        longitudeLabel->setObjectName(QString::fromUtf8("longitudeLabel"));
        longitudeLabel->setGeometry(QRect(440, 30, 181, 41));
        longitudeLabel->setFont(font6);
        latitudeLabel = new QLabel(ddTab);
        latitudeLabel->setObjectName(QString::fromUtf8("latitudeLabel"));
        latitudeLabel->setGeometry(QRect(440, 110, 151, 41));
        latitudeLabel->setFont(font6);
        latitudeBox = new QTextBrowser(ddTab);
        latitudeBox->setObjectName(QString::fromUtf8("latitudeBox"));
        latitudeBox->setGeometry(QRect(630, 100, 151, 61));
        latitudeBox->setFont(font7);
        tab->addTab(ddTab, QString());
        batteryTab = new QWidget();
        batteryTab->setObjectName(QString::fromUtf8("batteryTab"));
        battEstTotCapLabel = new QLabel(batteryTab);
        battEstTotCapLabel->setObjectName(QString::fromUtf8("battEstTotCapLabel"));
        battEstTotCapLabel->setGeometry(QRect(20, 30, 261, 41));
        battEstTotCapLabel->setFont(font7);
        battEstTotCapBox = new QTextBrowser(batteryTab);
        battEstTotCapBox->setObjectName(QString::fromUtf8("battEstTotCapBox"));
        battEstTotCapBox->setGeometry(QRect(340, 20, 161, 61));
        battEstCapLeftLabel = new QLabel(batteryTab);
        battEstCapLeftLabel->setObjectName(QString::fromUtf8("battEstCapLeftLabel"));
        battEstCapLeftLabel->setGeometry(QRect(20, 110, 241, 41));
        battEstCapLeftLabel->setFont(font7);
        battEstCapLeftBox = new QTextBrowser(batteryTab);
        battEstCapLeftBox->setObjectName(QString::fromUtf8("battEstCapLeftBox"));
        battEstCapLeftBox->setGeometry(QRect(340, 100, 161, 61));
        battEstCapLeftBox->setFont(font7);
        currentBattTempLabel = new QLabel(batteryTab);
        currentBattTempLabel->setObjectName(QString::fromUtf8("currentBattTempLabel"));
        currentBattTempLabel->setGeometry(QRect(20, 180, 311, 41));
        currentBattTempLabel->setFont(font7);
        battProgBar_2 = new QProgressBar(batteryTab);
        battProgBar_2->setObjectName(QString::fromUtf8("battProgBar_2"));
        battProgBar_2->setGeometry(QRect(7, 380, 781, 61));
        battProgBar_2->setFont(font);
        battProgBar_2->setValue(0);
        battCapLabel_2 = new QLabel(batteryTab);
        battCapLabel_2->setObjectName(QString::fromUtf8("battCapLabel_2"));
        battCapLabel_2->setGeometry(QRect(10, 340, 421, 41));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Ubuntu"));
        font8.setPointSize(22);
        font8.setBold(false);
        font8.setItalic(false);
        font8.setWeight(50);
        battCapLabel_2->setFont(font8);
        peakBattTempLabel = new QLabel(batteryTab);
        peakBattTempLabel->setObjectName(QString::fromUtf8("peakBattTempLabel"));
        peakBattTempLabel->setGeometry(QRect(20, 270, 301, 41));
        peakBattTempLabel->setFont(font7);
        currentBattTempBox = new QTextBrowser(batteryTab);
        currentBattTempBox->setObjectName(QString::fromUtf8("currentBattTempBox"));
        currentBattTempBox->setGeometry(QRect(340, 180, 161, 61));
        peakBattTempBox = new QTextBrowser(batteryTab);
        peakBattTempBox->setObjectName(QString::fromUtf8("peakBattTempBox"));
        peakBattTempBox->setGeometry(QRect(340, 260, 161, 61));
        peakBattTempBox->setFont(font7);
        tab->addTab(batteryTab, QString());
        mpTab = new QWidget();
        mpTab->setObjectName(QString::fromUtf8("mpTab"));
        tab->addTab(mpTab, QString());
        alarmTab = new QWidget();
        alarmTab->setObjectName(QString::fromUtf8("alarmTab"));
        AlarmTextBox = new QTextBrowser(alarmTab);
        AlarmTextBox->setObjectName(QString::fromUtf8("AlarmTextBox"));
        AlarmTextBox->setGeometry(QRect(20, 10, 741, 321));
        AlarmTextBox->setAutoFillBackground(true);
        tab->addTab(alarmTab, QString());
        shutdownTab = new QWidget();
        shutdownTab->setObjectName(QString::fromUtf8("shutdownTab"));
        shutdownButton = new QPushButton(shutdownTab);
        shutdownButton->setObjectName(QString::fromUtf8("shutdownButton"));
        shutdownButton->setGeometry(QRect(110, 110, 201, 151));
        QFont font9;
        font9.setPointSize(24);
        shutdownButton->setFont(font9);
        rebootButton = new QPushButton(shutdownTab);
        rebootButton->setObjectName(QString::fromUtf8("rebootButton"));
        rebootButton->setGeometry(QRect(470, 110, 201, 151));
        rebootButton->setFont(font9);
        testKillAllButton = new QPushButton(shutdownTab);
        testKillAllButton->setObjectName(QString::fromUtf8("testKillAllButton"));
        testKillAllButton->setGeometry(QRect(330, 350, 121, 71));
        testKillAllButton->setFont(font4);
        tab->addTab(shutdownTab, QString());
        Home->setCentralWidget(centralwidget);

        retranslateUi(Home);

        tab->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QMainWindow *Home)
    {
        Home->setWindowTitle(QApplication::translate("Home", "Home", nullptr));
        currentSpeedLabel->setText(QApplication::translate("Home", "90", nullptr));
        battCapLabel->setText(QApplication::translate("Home", "<html><head/><body><p><span style=\" font-size:22pt;\">Battery capacity remaining</span></p></body></html>", nullptr));
        rangeBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:24pt;\">0  km</span></p></body></html>", nullptr));
        rangeLabel->setText(QApplication::translate("Home", "<html><head/><body><p>Range</p></body></html>", nullptr));
        modeBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:24pt; font-weight:600;\">NORMAL</span></p></body></html>", nullptr));
        modeLabel->setText(QApplication::translate("Home", "<html><head/><body><p>Driving Mode</p></body></html>", nullptr));
        ecoPushButton->setText(QApplication::translate("Home", "ECO", nullptr));
        normPushButton->setText(QApplication::translate("Home", "NORMAL", nullptr));
        racePushButton->setText(QApplication::translate("Home", "RACE", nullptr));
        kmhrsLabel->setText(QApplication::translate("Home", "km/h", nullptr));
        timeBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:32pt;\">00:00</span></p></body></html>", nullptr));
        timeLabel->setText(QApplication::translate("Home", "<html><head/><body><p><span style=\" font-size:22pt;\">Time</span></p></body></html>", nullptr));
        tab->setTabText(tab->indexOf(homeTab), QApplication::translate("Home", "Home", nullptr));
        speedLabel->setText(QApplication::translate("Home", "Speed", nullptr));
        speedBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:22pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0  km/h</p></body></html>", nullptr));
        topSpeedLabel->setText(QApplication::translate("Home", "Top speed", nullptr));
        topSpeedBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:22pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0  km/h</p></body></html>", nullptr));
        rangeLabel_2->setText(QApplication::translate("Home", "Range", nullptr));
        rangeBox_2->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt;\">0  km</span></p></body></html>", nullptr));
        modeLabel_2->setText(QApplication::translate("Home", "Driving Mode", nullptr));
        modeBox_2->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:24pt; font-weight:600;\">NORMAL</span></p></body></html>", nullptr));
        longitudeBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:22pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        longitudeLabel->setText(QApplication::translate("Home", "Longitude (N)", nullptr));
        latitudeLabel->setText(QApplication::translate("Home", "Latitude (E)", nullptr));
        latitudeBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:22pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        tab->setTabText(tab->indexOf(ddTab), QApplication::translate("Home", "Driving Details", nullptr));
        battEstTotCapLabel->setText(QApplication::translate("Home", "Est. total capacity", nullptr));
        battEstTotCapBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt;\">2800 Wh</span></p></body></html>", nullptr));
        battEstCapLeftLabel->setText(QApplication::translate("Home", "Est. capacity left", nullptr));
        battEstCapLeftBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:22pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1400 Wh</p></body></html>", nullptr));
        currentBattTempLabel->setText(QApplication::translate("Home", "Current battery temp", nullptr));
        battCapLabel_2->setText(QApplication::translate("Home", "Battery capacity remaining", nullptr));
        peakBattTempLabel->setText(QApplication::translate("Home", "Peak battery temp", nullptr));
        currentBattTempBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt;\">42 C</span></p></body></html>", nullptr));
        peakBattTempBox->setHtml(QApplication::translate("Home", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:22pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">69 C</p></body></html>", nullptr));
        tab->setTabText(tab->indexOf(batteryTab), QApplication::translate("Home", "Battery", nullptr));
        tab->setTabText(tab->indexOf(mpTab), QApplication::translate("Home", "Music Player", nullptr));
        tab->setTabText(tab->indexOf(alarmTab), QApplication::translate("Home", "Alarms", nullptr));
        shutdownButton->setText(QApplication::translate("Home", "Shutdown", nullptr));
        rebootButton->setText(QApplication::translate("Home", "Reboot", nullptr));
        testKillAllButton->setText(QApplication::translate("Home", "KILLALL", nullptr));
        tab->setTabText(tab->indexOf(shutdownTab), QApplication::translate("Home", "Shutdown", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
