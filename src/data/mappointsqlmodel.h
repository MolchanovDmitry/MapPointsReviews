#ifndef MAPPOINTSQLMODEL_H
#define MAPPOINTSQLMODEL_H

#include <QAbstractItemModel>
#include <QSqlQueryModel>

class MapPointSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit MapPointSqlModel(QObject *parent = nullptr);

private:
};

#endif // MAPPOINTSQLMODEL_H
