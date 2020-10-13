#pragma once

#include "workthread.h"
#include <QtWidgets/QMainWindow>
#include "ui_file_service_qt.h"

class file_service_qt : public QMainWindow
{
    Q_OBJECT

public:
    file_service_qt(QWidget *parent = Q_NULLPTR);

private slots:
    int on_pushButton_clicked();
    int on_pushButton_2_clicked();

private:
    Ui::file_service_qtClass ui;
    int ishow,isthread;
    workthread* thread;
    string path;
};
