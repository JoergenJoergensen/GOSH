/********************************************************************************
** Form generated from reading UI file 'shutdowndialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHUTDOWNDIALOG_H
#define UI_SHUTDOWNDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ShutdownDialog
{
public:
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *sureLabel;

    void setupUi(QDialog *ShutdownDialog)
    {
        if (ShutdownDialog->objectName().isEmpty())
            ShutdownDialog->setObjectName(QString::fromUtf8("ShutdownDialog"));
        ShutdownDialog->resize(383, 209);
        okButton = new QPushButton(ShutdownDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(240, 130, 101, 71));
        QFont font;
        font.setPointSize(18);
        okButton->setFont(font);
        cancelButton = new QPushButton(ShutdownDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(40, 130, 101, 71));
        cancelButton->setFont(font);
        sureLabel = new QLabel(ShutdownDialog);
        sureLabel->setObjectName(QString::fromUtf8("sureLabel"));
        sureLabel->setGeometry(QRect(90, 40, 201, 41));

        retranslateUi(ShutdownDialog);

        QMetaObject::connectSlotsByName(ShutdownDialog);
    } // setupUi

    void retranslateUi(QDialog *ShutdownDialog)
    {
        ShutdownDialog->setWindowTitle(QApplication::translate("ShutdownDialog", "Dialog", nullptr));
        okButton->setText(QApplication::translate("ShutdownDialog", "OK", nullptr));
        cancelButton->setText(QApplication::translate("ShutdownDialog", "CANCEL", nullptr));
        sureLabel->setText(QApplication::translate("ShutdownDialog", "<html><head/><body><p><span style=\" font-size:24pt;\">Are you sure?</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShutdownDialog: public Ui_ShutdownDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHUTDOWNDIALOG_H
