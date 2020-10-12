#pragma once
#include<qthread.h>
#include<string>
#include<qlabel>
#include <winsock2.h>
#include<thread>
using namespace std;

class workthread :
    public QThread
{
    Q_OBJECT
public:
    workthread(int port_temp, string path_temp, QLabel *label);
protected:
    void run();
private:
    QLabel *led;
    SOCKET m_Client;
    int port;//¶Ë¿Ú
    string path;//Â·¾¶
    void RecvFile();
    void RecvStr();
};

