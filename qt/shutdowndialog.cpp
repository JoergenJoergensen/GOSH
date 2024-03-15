#include "shutdowndialog.h"
#include "ui_shutdowndialog.h"

ShutdownDialog::ShutdownDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShutdownDialog)
{
    ui->setupUi(this);
}

ShutdownDialog::~ShutdownDialog()
{
    delete ui;
}

void ShutdownDialog::on_okButton_clicked()
{
    switch(whatPressed)
    {
    case 'S':
        system("sudo shutdown -h now");
        break;
    case 'R':
        system("sudo reboot");
        break;
    case 'K':
        system("sudo killall gokart_prototype_1");
        break;
    default:
        break;
    }
}

void ShutdownDialog::on_cancelButton_clicked()
{
    destroy();
}
