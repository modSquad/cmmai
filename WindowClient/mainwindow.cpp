#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(LogModel *logModel, Connection *connection, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logModel(logModel),
    connection(connection)
{
    ui->setupUi(this);

    ui->LogView->setModel(logModel->getModel());

    connect(connection, SIGNAL(gotLog(QString)), logModel, SLOT(appendLog(QString)));
    connect(connection, SIGNAL(gotAccepted(int)), this, SLOT(addAccepted(int)));
    connect(connection, SIGNAL(gotRejected(int)), this, SLOT(addRejected(int)));

    connect(ui->ConnectionButton, SIGNAL(clicked()), this, SLOT(connectToHost()));
    connect()
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

void MainWindow::connectToHost()
{
    connection->connectToHost(ui->AddressLine->text());
}

void MainWindow::connectionNotify()
{
    ui->ConnectionLabel->setText(QString("Connected"));
}

void MainWindow::disconnectionNotify()
{
    ui->ConnectionLabel->setText(QString("Disconnected"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
