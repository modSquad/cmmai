#include <QtGui/QApplication>

#include "mainwindow.h"
#include "socket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Socket connection;

    MainWindow w(&connection);
    w.show();

    return a.exec();
}
