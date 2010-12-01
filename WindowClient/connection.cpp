#include <QDebug>

#include "connection.h"

Connection::Connection():
    socket(new QTcpSocket(this))
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(Receive()));
}

void Connection::connectToHost(QString address, int port)
{
    socket->connectToHost(address, port);
}

void Connection::connectToHost(QString addressLine)
{
    QList<QString> addressList = addressLine.split(":");
    if(addressList.count())
    {
        connectToHost(addressList[0],addressList[1].toInt());
    }
}

void Connection::Receive()
{
    QString message = socket->readAll();

    //qDebug() << message;

    QList<QString> messages = message.split("]");

    if(messages[0].compare("[Log") == 0)
    {
        emit gotLog(messages[1]);
        //qDebug() << "emit gotLog(" << messages[1] <<")";
    }

    else if(messages[0].compare("[Acc") == 0)
    {
        emit gotAccepted(messages[1].toInt());
        //qDebug() << "emit gotAccepted(" << messages[1] <<")";
    }

    else if(messages[0].compare("[Rej") == 0)
    {
        emit gotRejected(messages[1].toInt());
        //qDebug() << "emit gotRejected(" << messages[1] <<")";
    }
    else
    {
        emit gotLog(QString("Unknown message received : ") + message);
    }
}
