#include "shutdown.h"
#include "shutdowndialog.h"

ShutdownDialog *shutDialog;
char whatPressed;

void Home::on_shutdownButton_clicked()
{
    whatPressed = 'S';
    shutDialog = new ShutdownDialog(this);
    shutDialog->show();
}

void Home::on_rebootButton_clicked()
{
    whatPressed = 'R';
    shutDialog = new ShutdownDialog(this);
    shutDialog->show();
}

// for debugging
void Home::on_testKillAllButton_clicked()
{
    whatPressed = 'K';
    shutDialog = new ShutdownDialog(this);
    shutDialog->show();
}
