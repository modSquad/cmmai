#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>

class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = 0);

signals:
    /** gotLog(QString logLine)
      * signal emitted when a logLine is receive from the server
      */
    void gotLog(QString logLine);

public slots:
    /** Receive()
      * Called when data is received by the socket
      */
    void Receive();

    /** SendConfig(int operatorCode, int threshold, int bundleReference, int boxCount, int piecesPerBox)
      * Called to send the config data to the server
      */
    void SendConfig(int operatorCode, int threshold, int bundleReference, int boxCount, int piecesPerBox);

    /** Launch()
      * Send a Launch order to the server
      */
    void Launch();

    /** Stop()
      * Send a Stop order to the server
      */
    void Stop();

    /** Resume()
      * Send a Resume order to the server
      */
    void Resume();

private:

};

#endif // SOCKET_H
