#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_file_service_qt.h"

class file_service_qt : public QMainWindow
{
    Q_OBJECT

public:
    file_service_qt(QWidget *parent = Q_NULLPTR);

private slots:
    int on_pushButton_clicked();

private:
    Ui::file_service_qtClass ui;
};
