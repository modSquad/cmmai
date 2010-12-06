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
    /** addAccepted(int number)
      * Called when a pieces is boxed to make changes to the interface
      */
    void addAccepted(int number);

    /** addRejected(int number)
      * Called when a pieces is rejected to make changes to the interface
      */
    void addRejected(int number);

    /** appendLog(QString logLine)
      * Called to apped a line to the log.
      */
    void appendLog(QString logLine);


    /** sendConfig()
      * Called by interface to send configuration data to the server
      */
    void sendConfig();


    /** connectToHost()
      * Called by interface to connect to the server specified in the address text line.
      */
    void connectToHost();

    /** connectionNotify()
      * Called to notify when the socket is connected
      */
    void connectionNotify();

    /** disconnectionNotify()
      * Called to notify when the socket is disconnected
      */
    void disconnectionNotify();

private:
    Ui::MainWindow *ui;
    Socket *connection;
};

#endif // MAINWINDOW_H
