#include "ddDetails.h"

void Home::TopSpeed()
{
    if (topSpeed < currentSpeed)
        topSpeed = currentSpeed;

    topSpeedString = QString("%1  km/h").arg(topSpeed);

    ui->topSpeedBox->setFont(fontNonBold);
    ui->topSpeedBox->setText(topSpeedString);
}

void Home::CurrentDistance()
{
    // calculate current distance
    tempDist = currentSpeed * distFactor;
    currentDist += tempDist;

    currentDistString = QString("%1  km").arg(currentDistString.setNum(currentDist, 'g', 3));
    ui->rangeBox->setFont(fontNonBold);
    ui->rangeBox_2->setFont(fontNonBold);
    ui->rangeBox->setText(currentDistString);
    ui->rangeBox_2->setText(currentDistString);
}

void Home::CurrentPosition()
{
    // read longitude and latitude
    currentLongitude = g_longitude;
    currentLatitude = g_latitude;

    //currentLongitudeString = QString("%1").arg(currentLongitude);
    //currentLatitudeString = QString("%1").arg(currentLatitude);
    ui->longitudeBox->setFont(fontNonBold);
    ui->latitudeBox->setFont(fontNonBold);
    ui->longitudeBox->setText(currentLongitudeString.setNum(currentLongitude, 'g', 4));
    ui->latitudeBox->setText(currentLatitudeString.setNum(currentLatitude, 'g', 4));

}
