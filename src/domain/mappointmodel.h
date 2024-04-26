#ifndef MAPPOINTMODEL_H
#define MAPPOINTMODEL_H

#include <QObject>
#include "mappoint.h"

class MapPointModel : public QObject
{
    Q_OBJECT
public:
    explicit MapPointModel(QObject *parent = nullptr);

    QList<MapPoint> getMapPoints() {
        return mapPoints;
    }

public slots:
    void onMapPointsUpdated(QList<MapPoint> mapPoints){
        this->mapPoints = mapPoints;
    }


private:
    QList<MapPoint> mapPoints = QList<MapPoint>();

};

#endif // MAPPOINTMODEL_H
