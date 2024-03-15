#include "home.h"
#include "ui_home.h"


Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags);

    ui->tab->setCurrentIndex(0);

    InitWatchers();

    // non bold font size=24
    fontNonBold.setBold(false);
    fontNonBold.setPointSize(24);

    // non bold font size=32
    fontNonBold32.setBold(false);
    fontNonBold32.setPointSize(32);

    // bold font size=24
    fontBold.setBold(true);
    fontBold.setPointSize(24);

    // speed timer
    speedTimer = new QTimer(this);
    connect(speedTimer, SIGNAL(timeout()), this, SLOT(UpdateSpeed()));
    speedTimer->start(200);

    // total cap + battery timer
    EstTotalCapacity();
    batteryTimer = new QTimer(this);
    connect(batteryTimer, SIGNAL(timeout()), this, SLOT(UpdateBattery()));
    batteryTimer->start(1000);

    // distance timer
    distanceTimer = new QTimer(this);
    connect(distanceTimer, SIGNAL(timeout()), this, SLOT(UpdateDistance()));
    distanceTimer->start(200);

    UpdateTime();
    // clock timer
    clockTimer = new QTimer(this);
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(UpdateTime()));
    clockTimer->start(30000);

}
Home::~Home()
{
    speedTimer->stop();
    batteryTimer->stop();
    distanceTimer->stop();
    clockTimer->stop();
    delete ui;
}


/* update speed info */
void Home::UpdateSpeed()
{
    // update currentSpeed
    currentSpeed = g_gokart_speed;
    currentSpeedString = QString("%1").arg(currentSpeed);
    ui->currentSpeedLabel->setText(currentSpeedString);

    TopSpeed();             // top speed
}

/* update battery info */
void Home::UpdateBattery()
{
    EstCapacityLeft();      // battery cap left
    BatteryProgress();      // battery prog bar
    CurrentBatteryTemp();   // current battery temp
    PeakBatteryTemp();      // peak battery temp
}

/* update distance info */
void Home::UpdateDistance()
{
    CurrentDistance();      // calculate current distance
    CurrentPosition();      // show GPS position
}

void Home::UpdateTime()
{
    timeHour = g_clock_hours;
    timeMin = g_clock_minutes;

    if (timeHour < 9)
    {
        timeString = QString("0%1:%2").arg(timeHour).arg(timeMin);
        if (timeMin < 9)
        {
           timeString = QString("0%1:0%2").arg(timeHour).arg(timeMin);
        }
    }
    else if (timeMin < 9)
    {
        timeString = QString("%1:0%2").arg(timeHour).arg(timeMin);
    }
    else
    {
        timeString = QString("%1:%2").arg(timeHour).arg(timeMin);
    }

    ui->timeBox->setFont(fontNonBold32);
    ui->timeBox->setText(timeString);
}


/*  driving mode buttons  */
void Home::on_ecoPushButton_clicked()
{
    // set driving mode = ECO
    user_settings.driving_mode = DRIVE_MODE_ECO;

    // modeBox 1 and 2
    ui->modeBox->setFont(fontBold);
    ui->modeBox_2->setFont(fontBold);
    ui->modeBox->setText("ECO");
    ui->modeBox_2->setText("ECO");
}

void Home::on_normPushButton_clicked()
{
    // set driving mode = NORMAL
    user_settings.driving_mode = DRIVE_MODE_NORMAL;

    // modeBox 1 and 2
    ui->modeBox->setFont(fontBold);
    ui->modeBox_2->setFont(fontBold);
    ui->modeBox->setText("NORMAL");
    ui->modeBox_2->setText("NORMAL");
}

void Home::on_racePushButton_clicked()
{
    // set driving mode = RACE
    user_settings.driving_mode = DRIVE_MODE_RACE;

    // modeBox 1 and 2
    ui->modeBox->setFont(fontBold);
    ui->modeBox_2->setFont(fontBold);
    ui->modeBox->setText("RACE");
    ui->modeBox_2->setText("RACE");
}
