#include "file_service_qt.h"
#include"workthread.h"
#include<string>
#include <qlabel>

using namespace std;

file_service_qt::file_service_qt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}


int file_service_qt::on_pushButton_clicked()
{
    string path = "D:\\data\\out\\xjpic.jpg";
    QLabel* led = ui.showifo;
    workthread* temp = new workthread(8888, path,led);
    temp->start();
    return 0;
}

