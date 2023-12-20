/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *imgLabel;
    QLabel *label_2;
    QLineEdit *accountEdit;
    QLineEdit *codeEdit;
    QPushButton *loginButton;
    QPushButton *cancelButton;
    QLabel *label_3;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(1073, 687);
        imgLabel = new QLabel(LoginDialog);
        imgLabel->setObjectName(QStringLiteral("imgLabel"));
        imgLabel->setGeometry(QRect(0, 0, 791, 511));
        imgLabel->setPixmap(QPixmap(QString::fromUtf8(":/login.png")));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(150, 300, 72, 15));
        accountEdit = new QLineEdit(LoginDialog);
        accountEdit->setObjectName(QStringLiteral("accountEdit"));
        accountEdit->setGeometry(QRect(230, 250, 201, 31));
        codeEdit = new QLineEdit(LoginDialog);
        codeEdit->setObjectName(QStringLiteral("codeEdit"));
        codeEdit->setGeometry(QRect(230, 300, 201, 31));
        codeEdit->setEchoMode(QLineEdit::Password);
        loginButton = new QPushButton(LoginDialog);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(60, 360, 111, 28));
        cancelButton = new QPushButton(LoginDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(450, 360, 111, 28));
        label_3 = new QLabel(LoginDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 260, 51, 21));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "LoginDialog", Q_NULLPTR));
        imgLabel->setText(QString());
        label_2->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", Q_NULLPTR));
        loginButton->setText(QApplication::translate("LoginDialog", "\347\231\273\345\275\225", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("LoginDialog", "\345\217\226\346\266\210", Q_NULLPTR));
        label_3->setText(QApplication::translate("LoginDialog", "\350\264\246\345\217\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
