#include <QDateTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Socket *connection, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connection(connection)
{
    ui->setupUi(this);
    // TODO set header data
    //ui->LogView->setHorizontalHeaderItem(0, );
    //ui->LogView->setHorizontalHeaderItem(1, );

    //ui->LogView->set

    connect(connection, SIGNAL(gotLog(QString)), this, SLOT(appendLog(QString)));

    connect(ui->sendConfigButton, SIGNAL(clicked()), this, SLOT(sendConfig()));

    connect(ui->ConnectionButton, SIGNAL(clicked()), this, SLOT(connectToHost()));

    connect(connection, SIGNAL(connected()), this, SLOT(connectionNotify()));
    connect(connection, SIGNAL(disconnected()), this, SLOT(disconnectionNotify()));
}

void MainWindow::addAccepted(int number)
{
    ui->AcceptedNumber->setText( QString::number(ui->AcceptedNumber->text().toInt() + number));
}

void MainWindow::addRejected(int number)
{
    ui->RejectedNumber->setText( QString::number(ui->RejectedNumber->text().toInt() + number));
    ui->RejectedBar->setValue(ui->RejectedBar->value()+number);
}

void MainWindow::appendLog(QString logLine)
{
    logLine.replace(QString("\n"), QString(""));
    QDateTime time(QDateTime::currentDateTime());
    new QListWidgetItem(time.toString(QString("hh:mm:ss.zzz : ")) + logLine, ui->LogView);
}

void MainWindow::sendConfig()
{
    //TODO make control on ui values
    connection->SendConfig(ui->operatorCode->text().toInt(),
                           ui->threshold->text().toInt(),
                           ui->bundleReference->text().toInt(),
                           ui->numberOfBox->text().toInt(),
                           ui->piecesBox->text().toInt());
}

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

void MainWindow::connectionNotify()
{
    ui->ConnectionButton->setText(QString("Disconnect"));
}

void MainWindow::disconnectionNotify()
{
    ui->ConnectionButton->setText(QString("Connect"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
