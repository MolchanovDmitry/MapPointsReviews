#ifndef MAPVIEWMODEL_H
#define MAPVIEWMODEL_H

#include <QObject>
#include "mappointsuimodel.h"
#include "../data/repository.h" //TODO

class MapViewModel : public QObject
{
    Q_OBJECT
public:

    explicit MapViewModel(Repository* repository, QObject *parent = nullptr);

    MapPointsUiModel* getMapPointsUiModel();

signals:

private:
    MapPointsUiModel *mapPointsUiModel = new MapPointsUiModel();
    Repository *repository;

    void mapMapPointAndUpdate(QList<MapPoint*> mapPoints);
};

#endif // MAPVIEWMODEL_H
