#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "socket.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Socket *connection, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addAccepted(int number);
    void addRejected(int number);
    void appendLog(QString logLine);

    void sendConfig();

    void connectToHost();
    void connectionNotify();
    void disconnectionNotify();

private:
    Ui::MainWindow *ui;
    Socket *connection;
};

#endif // MAINWINDOW_H
