#include <QDateTime>

#include "logmodel.h"

LogModel::LogModel()
{
    model.setHeaderData(0, Qt::Horizontal, QObject::tr("Date"));
    model.setHeaderData(1, Qt::Horizontal, QObject::tr("Message"));
}

QStandardItemModel *LogModel::getModel()
{
    return &model;
}

void LogModel::appendLog(QString logLine)
{
    /*
    QStandardItem *dateItem = new QStandardItem();
    QStandardItem *logItem = new QStandardItem();

    dateItem->setText(QDateTime::currentDateTime().toString());
    logItem->setText(QString(logLine));

    QList<QStandardItem*> listItem;
    listItem.append(logItem);
    listItem.append(dateItem);

    model.appendRow(listItem);
    */

    model.insertRow(0);
    model.setData(model.index(0, 0), QDateTime::currentDateTime().toString());
    model.setData(model.index(0, 1), logLine);
}
