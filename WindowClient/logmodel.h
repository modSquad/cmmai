#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QStandardItemModel>

class LogModel : public QObject
{
    Q_OBJECT

public:
    LogModel();
    QStandardItemModel *getModel();

public slots:
    void appendLog(QString logItem);

private:
    QStandardItemModel model;
};

#endif // LOGMODEL_H
