#ifndef MAPPOINTMODEL_H
#define MAPPOINTMODEL_H

#include <QObject>
#include <QDebug>
#include "mappoint.h"

class MapPointModel : public QObject
{
    Q_OBJECT
public:
    explicit MapPointModel(QObject *parent = nullptr);

    QList<MapPoint*> getMapPoints();

public slots:
    void updateMapPoints(QList<MapPoint*> mapPoints);

signals:
    void mapPointsUpdated(QList<MapPoint*> mapPoints);

private:
    QList<MapPoint*> mapPoints = QList<MapPoint*>();

};

#endif // MAPPOINTMODEL_H
