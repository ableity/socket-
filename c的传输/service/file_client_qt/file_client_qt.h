#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_file_client_qt.h"

class file_client_qt : public QMainWindow
{
    Q_OBJECT

public:
    file_client_qt(QWidget *parent = Q_NULLPTR);

private slots:
    int on_pushButton_clicked();

private:
    Ui::file_client_qtClass ui;
};
