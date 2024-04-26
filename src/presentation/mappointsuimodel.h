#ifndef MAPPOINTSUIMODEL_H
#define MAPPOINTSUIMODEL_H

#include <QObject>
#include "../domain/mappoint.h"

class MapPointsUiModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<MapPoint> mapPoints READ getMapPoints WRITE updateMapPoints NOTIFY onMapPointsUpdated)
public:
    explicit MapPointsUiModel(QObject *parent = nullptr);

    QList<MapPoint> getMapPoints() {
        return mapPoints;
    }

public slots:
    void updateMapPoints(QList<MapPoint> mapPoints){
        this->mapPoints = mapPoints;
    }

signals:
    void onMapPointsUpdated(QString text);


private:
    QList<MapPoint> mapPoints = QList<MapPoint>();

};

#endif // MAPPOINTSUIMODEL_H
