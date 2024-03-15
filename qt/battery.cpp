#include "battery.h"

void Home::EstTotalCapacity()
{
    totalCapString = QString("%1  Wh").arg(totalCap);

    ui->battEstTotCapBox->setFont(fontNonBold);
    ui->battEstTotCapBox->setText(totalCapString);
}

void Home::EstCapacityLeft()
{
    capLeft = g_battery_capacity;
    capLeftString = QString("%1  Wh").arg(capLeft);

    ui->battEstCapLeftBox->setFont(fontNonBold);
    ui->battEstCapLeftBox->setText(capLeftString);
}

void Home::BatteryProgress()
{
    battPercent1 = (capLeft/totalCap)*100;
    battPercent2 = (capLeft/totalCap)*100;

    ui->battProgBar->setFont(fontNonBold);
    ui->battProgBar->setValue(battPercent1);
    ui->battProgBar_2->setValue(battPercent2);
}

void Home::CurrentBatteryTemp()
{
    currentBattTemp = g_battery_temp;
    currentBattTempString = QString("%1  C").arg(currentBattTemp);

    ui->currentBattTempBox->setFont(fontNonBold);
    ui->currentBattTempBox->setText(currentBattTempString);
}

void Home::PeakBatteryTemp()
{
    if (peakBattTemp < currentBattTemp)
        peakBattTemp = currentBattTemp;

    peakBattTempString = QString("%1  C").arg(peakBattTemp);

    ui->peakBattTempBox->setFont(fontNonBold);
    ui->peakBattTempBox->setText(peakBattTempString);
}
