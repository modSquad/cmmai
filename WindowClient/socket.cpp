#include <QStringList>

#include "socket.h"

Socket::Socket(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(Receive()));


}

void Socket::Receive()
{
    static QString message;
    message += readLine();

    if(message.endsWith("\n\n"))
    {
        QList<QString> list = message.split("\n", QString::SkipEmptyParts);

        if(list[0].compare("LOG") == 0)
        {
            list[1].replace("[","");
            list[1].replace("]","");
            emit gotLog(list[1]);
        }
        /* This is actualy not implemented in the server
        else if(list[0].compare("ACCEPTED") == 0)
        {

        }
        else if(list[0].compare("REJECTED") == 0)
        {

        }*/
        else if(list[0].compare("ERROR") == 0)
        {
            list[1].replace("[","Error ");
            list[1].replace("]","");
            emit gotLog(list[1]);
        }
        else if(list[0].compare("WARNINGS") == 0)
        {
            list[1].replace("[","Warnings ");
            list[1].replace("]","");
            emit gotLog(list[1]);
        }
        else
        {
            emit gotLog(QString("Unknown message received : ") + message);
        }
        message.clear();
    }
}

void Socket::SendConfig(int operatorCode, int threshold, int bundleReference, int boxCount, int piecesPerBox)
{
    QString config( "CONFIG\n[" + QString::number(operatorCode) + "]\n["
                                + QString::number(threshold) + "]\n["
                                + QString::number(bundleReference) + "]\n["
                                + QString::number(boxCount) + "]\n["
                                + QString::number(piecesPerBox) + "]\n\n"
                                );

    //TODO check if there's no other way to send QString over socket.
    write(config.toUtf8());
}

void Socket::Launch()
{
    write("LAUNCH\n\n");
}

void Socket::Resume()
{
    write("RESUME\n\n");
}

void Socket::Stop()
{
    write("STOP\n\n");
}
