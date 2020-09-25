#include "test_qt.h"
#include <qdebug.h>
#include "workthread.h"

test_qt::test_qt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}
int test_qt::on_pushButton_clicked()
{
    workthread* temp = new workthread();
    temp->start();
	return 0;
}