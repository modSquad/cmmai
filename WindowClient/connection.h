#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QtNetwork>

class Connection : public QObject
{
    Q_OBJECT

public:
    Connection();
    void connectToHost(QString address, int port);

public slots:
    void connectToHost(QString addressLine);

signals:
    void gotLog(QString message);
    void gotAccepted(int number);
    void gotRejected(int number);

private:
    QTcpSocket *socket;

private slots:
    void Receive();

};

#endif // CONNECTION_H
