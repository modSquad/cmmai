#include <QDateTime>
#include <QMessageBox>
#include <QErrorMessage>
#include <QPushButton>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Socket *connection, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connection(connection)
{
    ui->setupUi(this);

    /* Disable unavailable offline control
     */
    ui->configurationWidget->setDisabled(true);
    ui->controlWidget->setDisabled(true);
    ui->PiecesDock->setDisabled(true);
    ui->stopButton->setDisabled(true);
    ui->resumeButton->setDisabled(true);

    /* Connection/Disconnection notification
     */
    connect(connection, SIGNAL(connected()), this, SLOT(connectionNotify()));
    connect(connection, SIGNAL(disconnected()), this, SLOT(disconnectionNotify()));

    /* Received logLine
     */
    connect(connection, SIGNAL(gotLog(QString)), this, SLOT(appendLog(QString)));

    /* Received Boxed info
     */
    connect(connection, SIGNAL(gotAccepted(int)), this, SLOT(addAccepted(int)));
    connect(connection, SIGNAL(gotRejected(int)), this, SLOT(addRejected(int)));

    /* Received Error / Warning
     */
    connect(connection, SIGNAL(gotError(int)), this, SLOT(errorNotify(int)));
    //connect(connection, SIGNAL(gotWarning(int)), this, SLOT(warningNotify(int)));

    /* Connection button
     */
    connect(ui->ConnectionButton, SIGNAL(clicked()), this, SLOT(connectToHost()));

    /* Send configuration data button
     */
    connect(ui->sendConfigButton, SIGNAL(clicked()), this, SLOT(sendConfig()));

    /* Actions button : Lauch / Resume / Stop
     */
    connect(ui->launchButton, SIGNAL(clicked()), this, SLOT(launch()));
    connect(ui->resumeButton, SIGNAL(clicked()), this, SLOT(resume()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop()));
}


/** addAccepted(int number)
  * Called when a pieces is boxed to make changes to the interface
  */
void MainWindow::addAccepted(int number)
{
    ui->AcceptedNumber->setText( QString::number(ui->AcceptedNumber->text().toInt() + number));

    qreal acc = ui->AcceptedNumber->text().toInt();
    qreal rej = ui->RejectedNumber->text().toInt();

    ui->ratio->setText(QString::number(acc/(acc+rej), 'f', 2));
}


/** addRejected(int number)
  * Called when a pieces is rejected to make changes to the interface
  */
void MainWindow::addRejected(int number)
{
    ui->RejectedNumber->setText( QString::number(ui->RejectedNumber->text().toInt() + number));
    ui->RejectedBar->setValue(ui->RejectedBar->value()+number);

    qreal acc = ui->AcceptedNumber->text().toInt();
    qreal rej = ui->RejectedNumber->text().toInt();

    ui->ratio->setText(QString::number(acc/(acc+rej), 'f', 2));
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

    ui->RejectedBar->setMaximum(ui->threshold->text().toInt());

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
    ui->configurationWidget->setEnabled(true);
    ui->controlWidget->setEnabled(true);
    ui->PiecesDock->setEnabled(true);
}


/** disconnectionNotify()
  * Called to notify when the socket is disconnected
  */
void MainWindow::disconnectionNotify()
{
    ui->ConnectionButton->setText(QString("Connect"));
    ui->configurationWidget->setDisabled(true);
    ui->controlWidget->setDisabled(true);
    ui->PiecesDock->setDisabled(true);
}


/** errorNotify()
  * display prompt to get user choice
  */
void MainWindow::errorNotify(int errCode)
{

    QMessageBox msgBox;
    msgBox.setText(QString("Error ") + QString::number(errCode) + QString("."));

    switch(errCode)
    {
    case 101 : // EVT_ERR_DEFECTIVE_TRESHOLD_REACHED
        msgBox.setInformativeText("The treshold of defective products is reached.");
        break;
    case 102 : // EVT_ERR_FULL_QUEUE
        msgBox.setInformativeText("The queue containing the boxes to be printed is full.");
        break;
    case 103 : // EVT_ERR_BOX_STARVATION
        msgBox.setInformativeText("No box is present");
        break;
    case 104 : // EVT_ERR_PRODUCT_STARVATION
        msgBox.setInformativeText("Product famine");
        break;
    }

    msgBox.addButton(QString("Stop"), QMessageBox::AcceptRole);
    msgBox.addButton(QString("Resume"), QMessageBox::RejectRole);

    switch(msgBox.exec())
    {
    case QMessageBox::AcceptRole :
        stop();
        break;
    case QMessageBox::RejectRole :
        resume();
        break;
    }
}

/** warningNotify()
  */
void MainWindow::warningNotify(int errCode)
{
    QMessageBox msgBox;
    switch(errCode)
    {
    case 201 : // EVT_ANOMALY_PRINTER1
        msgBox.setText(QString("Warning ") + QString::number(errCode) + QString("\nThe printer 1 presents anomaly."));
        break;
    case 202 : // EVT_ANOMALY_PRINTER2
        msgBox.setText(QString("Warning ") + QString::number(errCode) + QString("\nThe printer 2 presents anomaly."));
        break;
    }
    msgBox.exec();
}

/** launch()
  * Send a resume command to the server.
  */
void MainWindow::launch()
{
    connection->Launch();
    ui->launchButton->setDisabled(true);
    ui->resumeButton->setDisabled(true);
    ui->stopButton->setEnabled(true);
}

/** resume()
  * Send a resume command to the server.
  */
void MainWindow::resume()
{
    connection->Resume();
    ui->launchButton->setDisabled(true);
    ui->resumeButton->setDisabled(true);
    ui->stopButton->setEnabled(true);
}

/** stop()
  * Send a stop command to the server.
  */
void MainWindow::stop()
{
    connection->Stop();
    ui->launchButton->setEnabled(true);
    ui->resumeButton->setEnabled(true);
    ui->stopButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
