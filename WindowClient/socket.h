#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>

class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = 0);

signals:
    void gotLog(QString logLine);

public slots:
    void Receive();

private:

};

#endif // SOCKET_H
