#include <QtGui/QApplication>
#include "mainwindow.h"
#include "logmodel.h"
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogModel logModel;
    Connection connection;

    //connection.connectToHost(QString("127.0.0.1"),42424);

    MainWindow w(&logModel, &connection);
    w.show();

    return a.exec();
}
