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
        QList<QString> list = message.split("/n", QString::SkipEmptyParts);

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
            list[1].replace("[","error number ");
            list[1].replace("]","");
            emit gotLog(list[1]);
        }
        else
        {
            emit gotLog(QString("Unknown message received : ") + message);
        }
    }

    /*
    L1: ACCEPTED\n
    L2: \n

    L1: CONFIG\n
    L2: [Code opérateur]\n
    L3: [Seuil]\n
    L4: [Référence du lot]\n
    L5: [Nombre de cartons]\n
    L6: [Nombre de pièces/carton]\n
    L8: \n

    L1: ERROR\n
    L2: [Code]\n
    L3: \n

    L1: LAUNCH\n
    L2: \n

    L1: LOG\n
    L2: [Message]\n
    L3: \n

    L1: REJECTED\n
    L2: \n

    L1: RESUME\n
    L2: \n
*/

}
