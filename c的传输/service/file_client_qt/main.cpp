#include "file_client_qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    file_client_qt w;
    w.show();
    return a.exec();
}
