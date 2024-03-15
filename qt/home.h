#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QFileSystemWatcher>
#include <QFile>
#include "ddDetails.h"
#include "battery.h"
#include "ourCAN.h"
#include "globals.h"
#include "gpio.h"
#include <QTime>
#include <QDebug>
#include <QElapsedTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void on_ecoPushButton_clicked();
    void on_racePushButton_clicked();
    void on_normPushButton_clicked();



    void on_testKillAllButton_clicked();

    void on_AlarmTextBox_textChanged();

public slots:
    // home tab
    void UpdateSpeed(void);
    void UpdateBattery(void);
    void UpdateDistance(void);
    void UpdateTime(void);

    // ddDetails tab
    void TopSpeed(void);
    void CurrentDistance(void);
    void CurrentPosition(void);

    // battery tab
    void EstTotalCapacity(void);
    void EstCapacityLeft(void);
    void BatteryProgress(void);
    void CurrentBatteryTemp(void);
    void PeakBatteryTemp(void);

    // shutdown tab
    void on_shutdownButton_clicked();
    void on_rebootButton_clicked();

    // gpio
    void InitWatchers(void);
    void DrivingModeUp(const QString &path);
    void DrivingModeDown(const QString &path);
    void TabIndexUp(const QString &path);
    void TabIndexDown(const QString &path);
    void EmergencyStop(const QString &path);



private:

public:
    Ui::Home *ui;

    // qstring for displaying integers
    QString currentSpeedString;
    QString topSpeedString;
    QString currentDistString;
    QString currentLongitudeString;
    QString currentLatitudeString;

    QString currentBattTempString;
    QString peakBattTempString;
    QString capLeftString;
    QString totalCapString;

    QString timeString;

    // qtimer for updating GUI
    QTimer *speedTimer;
    QTimer *batteryTimer;
    QTimer *distanceTimer;
    QTimer *clockTimer;

    // qfont for formatting GUI
    QFont fontNonBold;
    QFont fontNonBold32;
    QFont fontBold;

    // file system watcher
    QFileSystemWatcher *watcher;

    // variables
    int currentSpeed = 0;
    int topSpeed = 0;
    float currentDist = 0.0f;
    float tempDist = 0.0f;
    float currentLongitude = 0.0f;
    float currentLatitude = 0.0f;

    int currentBattTemp = 0;
    int peakBattTemp = 0;
    int capLeft = 0;
    const int totalCap = 2800;
    int battPercent1 = 100;
    int battPercent2 = 100;

    int timeHour = 0;
    int timeMin = 0;
    bool gReset = false;
    int btnPressed = 0;
    int currentTabIndex;
    int dmCount;

    char on = 49;
    char off = 48;

};
#endif // HOME_H
