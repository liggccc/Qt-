#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->imgLabel->setScaledContents(true);
    this->resize(ui->imgLabel->width(), ui->imgLabel->height());//设置的当前窗体
    setFixedSize(width(), height());
    this->setWindowTitle("驾校科目一考试登录");
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{
    //正则验证邮箱地址 用户名@域名
    //元字符解释:^表示字符串的开始 $表示规则字符串的结束
    //+表示匹配次数>=1次 *表示可以匹配任意次数(可以0) {n, m}表示匹配次数至少n次,至多m次
    QRegExp rx("^[A-Za-z0-9]+([_\.][A-Za-z0-9]+)*@([A-Za-z0-9\-]+\.)+[A-Za-z]{2,6}$");
    bool res = rx.exactMatch(ui->accountEdit->text());
    if(!res) {//匹配不成功
        QMessageBox::information(this, "提示", "非法的邮箱地址, 请你重新输入!");
        ui->accountEdit->clear();//清空输入框
        ui->codeEdit->clear();
        ui->accountEdit->setFocus();//聚焦
    }else{
        QString filename;  //账号密码数据文件地址
        QString strAccInput; //获取到的账户
        QString strCode; //获取到的密码
        QString strLine; //读取的每一行数据
        QStringList strList; //字符串链表,保存分割读取的一行数据

        filename = "account.txt";
        strAccInput = ui->accountEdit->text();
        strCode = ui->codeEdit->text();

        QFile file(filename);
        QTextStream stream(&file);
        if( file.open(QIODevice::ReadOnly | QIODevice::Text )){//只选择只读属性，是一个纯文本文件
            while (!stream.atEnd()){
                strLine = stream.readLine();
                strList = strLine.split(",");
                if(strAccInput == strList.at(0))
                    if (strCode == strList.at(1)){
                        QMessageBox::information(this, "提示", "欢迎进入科目一的考试系统！");
                        file.close();
                        done(Accepted);
                        return;
                    }else{
                        QMessageBox::information(this, "提示", "密码错误，请重新输入");
                        ui->codeEdit->clear();
                        ui->codeEdit->setFocus();
                        file.close();
                        return;
                 }
            }
            QMessageBox::information(this, "提示", "账号错误，请重新输入");
            ui->codeEdit->clear();
            ui->accountEdit->clear();
            ui->accountEdit->setFocus();
            file.close();
            return;
        }else{
            QMessageBox::information(this, "提示", "读取账号数据失败");
            return;
        }
    }
}

void LoginDialog::on_cancelButton_clicked()
{
    done(Rejected);
}
