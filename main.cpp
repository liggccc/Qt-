#include "logindialog.h"
#include <QApplication>
#include <examdialog.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog logDialog;
    int res = logDialog.exec();
    if (res == QDialog::Accepted){
        ExamDialog *examDialog;
        examDialog = new ExamDialog;
    }else{
        return 0;
    }
//    ExamDialog w;
//    w.show();

    return a.exec();
}
