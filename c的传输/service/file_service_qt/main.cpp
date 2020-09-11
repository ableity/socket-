#include "file_service_qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    file_service_qt w;
    w.show();
    return a.exec();
}
