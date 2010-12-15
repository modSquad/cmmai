#include <QStringList>

#include "socket.h"

Socket::Socket(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(Receive()));
}


/** Receive()
  * Called when data is received by the socket
  */
void Socket::Receive()
{
    static QString message;
    message += readAll();

    qDebug() << message;

    QList<QString> messages = message.split("\n\n", QString::SkipEmptyParts);
    foreach(QString line, messages)
    {
        QList<QString> list = line.split("\n", QString::SkipEmptyParts);

        if(list[0].compare("LOG") == 0)
        {
            emit gotLog(list[1]);
        }
        else if(list[0].compare("ACCEPTED") == 0)
        {
            emit gotAccepted(list[1].toInt());
        }
        else if(list[0].compare("REJECTED") == 0)
        {
            emit gotRejected(list[1].toInt());
        }
        else if(list[0].compare("ERROR") == 0)
        {
            emit gotError(list[1].toInt());
        }
        else if(list[0].compare("WARNINGS") == 0)
        {
            emit gotWarning(list[1].toInt());
        }
        else
        {
            emit gotLog(QString("Unknown message received : ") + message);
        }
    }
    message.clear();
}


/** SendConfig(int operatorCode, int threshold, int bundleReference, int boxCount, int piecesPerBox)
  * Called to send the config data to the server
  */
void Socket::SendConfig(int operatorCode, int threshold, int bundleReference, int boxCount, int piecesPerBox)
{
    QString config( "CONFIG\n" + QString::number(operatorCode) + "\n"
                                + QString::number(threshold) + "\n"
                                + QString::number(bundleReference) + "\n"
                                + QString::number(boxCount) + "\n"
                                + QString::number(piecesPerBox) + "\n\n"
                                );

    write(QByteArray(config.toStdString().c_str(), config.length()));
}


/** Launch()
  * Send a Launch order to the server
  */
void Socket::Launch()
{
    write("LAUNCH\n\n");
}


/** Stop()
  * Send a Stop order to the server
  */
void Socket::Stop()
{
    write("STOP\n\n");
}


/** Resume()
  * Send a Resume order to the server
  */
void Socket::Resume()
{
    write("RESUME\n\n");
}
