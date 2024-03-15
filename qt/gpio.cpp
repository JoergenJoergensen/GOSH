#include "gpio.h"

void Home::InitWatchers()
{
    auto dmuWatcher = new QFileSystemWatcher(this);
    dmuWatcher->addPath(GPIO13_PATH);
    connect(dmuWatcher, &QFileSystemWatcher::fileChanged, this, &Home::DrivingModeUp);

    auto dmdWatcher = new QFileSystemWatcher(this);
    dmdWatcher->addPath(GPIO19_PATH);
    connect(dmdWatcher, &QFileSystemWatcher::fileChanged, this, &Home::DrivingModeDown);

    auto tiuWatcher = new QFileSystemWatcher(this);
    tiuWatcher->addPath(GPIO5_PATH);
    connect(tiuWatcher, &QFileSystemWatcher::fileChanged, this, &Home::TabIndexUp);

    auto tidWatcher = new QFileSystemWatcher(this);
    tidWatcher->addPath(GPIO6_PATH);
    connect(tidWatcher, &QFileSystemWatcher::fileChanged, this, &Home::TabIndexDown);

    auto emsWatcher = new QFileSystemWatcher(this);
    emsWatcher->addPath(GPIO26_PATH);
    connect(emsWatcher, &QFileSystemWatcher::fileChanged, this, &Home::EmergencyStop);
}

void Home::DrivingModeUp(const QString &path)
{
    QFile GPIO13(path);

    if (!GPIO13.open(QIODevice::ReadOnly))
    {
    }

    auto gpio13 = GPIO13.readAll();
    if (!gpio13.isEmpty())
    {
        dmCount++;
        if (dmCount > 2)
        {
            dmCount == 2;
        }
    }

    switch(dmCount)
    {
    case 0:
        user_settings.driving_mode = DRIVE_MODE_ECO;
        ui->modeBox->setFont(fontBold);
        ui->modeBox_2->setFont(fontBold);
        ui->modeBox->setText("ECO");
        ui->modeBox_2->setText("ECO");
        break;
    case 1:
        user_settings.driving_mode = DRIVE_MODE_NORMAL;
        ui->modeBox->setFont(fontBold);
        ui->modeBox_2->setFont(fontBold);
        ui->modeBox->setText("NORMAL");
        ui->modeBox_2->setText("NORMAL");
        break;
    case 2:
        user_settings.driving_mode = DRIVE_MODE_RACE;
        ui->modeBox->setFont(fontBold);
        ui->modeBox_2->setFont(fontBold);
        ui->modeBox->setText("RACE");
        ui->modeBox_2->setText("RACE");
        break;
    }
}

void Home::DrivingModeDown(const QString &path)
{
    QFile GPIO19(path);

    if (!GPIO19.open(QIODevice::ReadOnly))
    {
    }

    auto gpio19 = GPIO19.readAll();
    if (!gpio19.isEmpty())
    {
        dmCount--;
        if (dmCount < 0)
            dmCount = 0;
    }

    switch(dmCount)
    {
    case 0:
        user_settings.driving_mode = DRIVE_MODE_ECO;
        ui->modeBox->setFont(fontBold);
        ui->modeBox_2->setFont(fontBold);
        ui->modeBox->setText("ECO");
        ui->modeBox_2->setText("ECO");
        break;
    case 1:
        user_settings.driving_mode = DRIVE_MODE_NORMAL;
        ui->modeBox->setFont(fontBold);
        ui->modeBox_2->setFont(fontBold);
        ui->modeBox->setText("NORMAL");
        ui->modeBox_2->setText("NORMAL");
        break;
    case 2:
        user_settings.driving_mode = DRIVE_MODE_RACE;
        ui->modeBox->setFont(fontBold);
        ui->modeBox_2->setFont(fontBold);
        ui->modeBox->setText("RACE");
        ui->modeBox_2->setText("RACE");
        break;
    }
}


void Home::TabIndexUp(const QString &path)
{
    QFile GPIO5(path);

    if (!GPIO5.open(QIODevice::ReadOnly))
    {

    }
    auto gpio5 = GPIO5.readAll();

    if (!gpio5.isEmpty())
    {
        currentTabIndex++;
        if (currentTabIndex > MAX_TAB_INDEX)
            currentTabIndex = MAX_TAB_INDEX;
    }

    ui->tab->setCurrentIndex(currentTabIndex);
}

void Home::TabIndexDown(const QString &path)
{
    QFile GPIO6(path);

    if (!GPIO6.open(QIODevice::ReadOnly))
    {
    }

    auto gpio6 = GPIO6.readAll();

    if (!gpio6.isEmpty())
    {
        currentTabIndex--;
        if (currentTabIndex < 0)
            currentTabIndex == 0;
    }

    ui->tab->setCurrentIndex(currentTabIndex);
}

void Home::EmergencyStop(const QString &path)
{
    QFile GPIO26(path);
    if(!GPIO26.open(QIODevice::ReadOnly))
        return;
    QDataStream in(&GPIO26);
    qint8 x;
    in >> x;

    if (x == 48){
        QString msg = QString("Emergency Stop: Driver fell off");
        ui->AlarmTextBox->setText(msg);

        // Should set P to 0 or global flag for enabling/ disabling PID or gas
    }

    else if(x == 49){
        QString msg = QString("Emergency Stop: Driver is back");
        ui->AlarmTextBox->setText(msg);

        //Should set gokart back to normal
    }

  }

/*!
 * \brief Home::on_AlarmTextBox_textChanged
 */

void Home::on_AlarmTextBox_textChanged()
{
        QFile gpio12(GPIO12_PATH);
        gpio12.open(QIODevice::WriteOnly);

        QElapsedTimer timer;

        timer.start();

        gpio12.write(&on,1);
        gpio12.close();

        while(timer.hasExpired(400) != true);
        gpio12.open(QIODevice::WriteOnly);
        gpio12.write(&off,1);
        gpio12.close();
        timer.restart();

        while(timer.hasExpired(400) != true);
        gpio12.open(QIODevice::WriteOnly);
        gpio12.write(&on,1);
        gpio12.close();
        timer.restart();

        while(timer.hasExpired(400) != true);
        gpio12.open(QIODevice::WriteOnly);
        gpio12.write(&off,1);
        gpio12.close();
    }


