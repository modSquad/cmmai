#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "logmodel.h"
#include "connection.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(LogModel *logModel, Connection *connection, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addAccepted(int number);
    void addRejected(int number);
    void connectToHost();

    void connectionNotify();
    void disconnectionNotify();

private:
    Ui::MainWindow *ui;
    LogModel *logModel;
    Connection *connection;
};

#endif // MAINWINDOW_H
