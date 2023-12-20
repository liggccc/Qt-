#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;//不是我们定义的类
}

class LoginDialog : public QDialog
{
    Q_OBJECT//当前的类支持信号与槽

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_loginButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
