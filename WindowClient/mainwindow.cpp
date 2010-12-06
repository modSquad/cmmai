#include <QDateTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Socket *connection, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connection(connection)
{
    ui->setupUi(this);

    /* Connection/Disconnection notification
     */
    connect(connection, SIGNAL(connected()), this, SLOT(connectionNotify()));
    connect(connection, SIGNAL(disconnected()), this, SLOT(disconnectionNotify()));

    /* Received logLine
     */
    connect(connection, SIGNAL(gotLog(QString)), this, SLOT(appendLog(QString)));

    /* Connection button
     */
    connect(ui->ConnectionButton, SIGNAL(clicked()), this, SLOT(connectToHost()));

    /* Send configuration data button
     */
    connect(ui->sendConfigButton, SIGNAL(clicked()), this, SLOT(sendConfig()));

    /* Actions button : Lauch / Resume / Stop
     */
    connect(ui->launchButton, SIGNAL(clicked()), connection, SLOT(Launch()));
    connect(ui->resumeButton, SIGNAL(clicked()), connection, SLOT(Resume()));
    connect(ui->stopButton, SIGNAL(clicked()), connection, SLOT(Stop()));
}


/** addAccepted(int number)
  * Called when a pieces is boxed to make changes to the interface
  */
void MainWindow::addAccepted(int number)
{
    ui->AcceptedNumber->setText( QString::number(ui->AcceptedNumber->text().toInt() + number));
}


/** addRejected(int number)
  * Called when a pieces is rejected to make changes to the interface
  */
void MainWindow::addRejected(int number)
{
    ui->RejectedNumber->setText( QString::number(ui->RejectedNumber->text().toInt() + number));
    ui->RejectedBar->setValue(ui->RejectedBar->value()+number);
}


/** appendLog(QString logLine)
  * Called to apped a line to the log.
  */
void MainWindow::appendLog(QString logLine)
{
    logLine.replace(QString("\n"), QString(""));
    QDateTime time(QDateTime::currentDateTime());
    new QListWidgetItem(time.toString(QString("hh:mm:ss.zzz : ")) + logLine, ui->LogView);
}


/** sendConfig()
  * Called by interface to send configuration data to the server
  */
void MainWindow::sendConfig()
{
    //TODO make control on ui values
    connection->SendConfig(ui->operatorCode->text().toInt(),
                           ui->threshold->text().toInt(),
                           ui->bundleReference->text().toInt(),
                           ui->numberOfBox->text().toInt(),
                           ui->piecesBox->text().toInt());
}


/** connectToHost()
  * Called by interface to connect to the server specified in the address text line.
  */
void MainWindow::connectToHost()
{
    qDebug() << connection->state();

    if(connection->state() == QAbstractSocket::ConnectedState)
    {
        connection->disconnectFromHost();
    }
    else
    {
        QList<QString> addressList = ui->AddressLine->text().split(":");
        if(addressList.count() > 0)
        {
           connection->connectToHost(addressList[0],addressList[1].toInt());
        }
    }
}


/** connectionNotify()
  * Called to notify when the socket is connected
  */
void MainWindow::connectionNotify()
{
    ui->ConnectionButton->setText(QString("Disconnect"));
}


/** disconnectionNotify()
  * Called to notify when the socket is disconnected
  */
void MainWindow::disconnectionNotify()
{
    ui->ConnectionButton->setText(QString("Connect"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
