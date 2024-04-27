#ifndef MAPVIEWMODEL_H
#define MAPVIEWMODEL_H

#include <QObject>
#include "mappointsuimodel.h"
#include "../domain/fetchallmappointsusecase.h"
#include "../domain/getmappointmodelusecase.h"

class MapViewModel : public QObject
{
    Q_OBJECT
public:

    explicit MapViewModel(
            FetchAllMapPointsUseCase *fetchAppMapPointsUseCase,
            GetMapPointModelUseCase *getMapPointModelUseCase,
            QObject *parent = nullptr
            );

    MapPointsUiModel* getMapPointsUiModel();

signals:

private:
    MapPointsUiModel *mapPointsUiModel = new MapPointsUiModel();

    void mapMapPointAndUpdate(QList<MapPoint*> mapPoints);
};

#endif // MAPVIEWMODEL_H
