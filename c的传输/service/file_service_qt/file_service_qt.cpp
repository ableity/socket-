#include "file_service_qt.h"
#include"workthread.h"
#include<string>
#include <qlabel>
#include <QDebug>

using namespace std;

file_service_qt::file_service_qt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lineEdit->hide();
    ui.label->hide();
    ishow = 0;
    isthread = 0;
    path = "D:\\data\\out\\";
    ui.lineEdit->setText("D:\\data\\out\\");
}


int file_service_qt::on_pushButton_clicked()
{
    QLabel* led = ui.showifo;
    int isexit = 0;
    if (isthread == 0)
    {
        thread = new workthread(18895, path, led);
        thread->start();
        isthread = 1;
        ui.pushButton->setText("end");
    }
    else if (isthread == 1)
    {
        //if (isexit == 0)
        //{
        //    thread->exit(0);

        //}
        //ui.showifo->setText("please restart");
    }
    
    return 0;
}
int file_service_qt::on_pushButton_2_clicked()
{
    if (ishow == 0)
    {
        ui.lineEdit->show();
        ui.label->show();
        ui.pushButton_2->setText("confirm");
        ishow = 1;
    }
    else if (ishow == 1)
    {
        ui.lineEdit->hide();
        ui.label->hide();
        QString temp = ui.lineEdit->text();
        path = temp.toStdString();
        ui.showifo->setText(temp);

        ui.pushButton_2->setText("edit path");
        ishow = 0;
    }
    return 0;
}
