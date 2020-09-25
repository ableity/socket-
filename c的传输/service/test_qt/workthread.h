#pragma once
#include<qthread.h>
class workthread :
    public QThread
{
    Q_OBJECT
public:
    workthread();
protected:
    void run();
};

