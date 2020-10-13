#include "mainwindow.h"
#include "loginwidnow.h"
#include <QApplication>

MainWindow *pMain;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    pMain = &w;
    w.show();

    return a.exec();
}
