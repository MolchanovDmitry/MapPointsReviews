#ifndef MAPPOINTSQLMODEL_H
#define MAPPOINTSQLMODEL_H

#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlTableModel>
#include "../domain/mappoint.h"

class MapPointTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit MapPointTableModel(QObject *parent = nullptr);

public slots:
    void onDataChanged();

signals:
    void mapPointsFromDataUpdated(QList<MapPoint*> mapPoints);
};

#endif // MAPPOINTSQLMODEL_H
