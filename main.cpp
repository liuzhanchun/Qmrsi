#include "mainwindow.h"
#include <QApplication>
#include "NetWork.h"
#include "utils.h"
#include "MeasDesktop.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // w.ShowWindow(SW_MAXIMIZE); ModifyStyle(WS_MAXIMIZEBOX,0);
    w.setWindowFlags(w.windowFlags());
    w.show();
   // CNetWork connect;
    //connect.show();
 //  qApp->setStyleSheet(Utils::getQssContent(":/qss/default.qss"));
    return a.exec();
}
