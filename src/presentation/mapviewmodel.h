#ifndef MAPVIEWMODEL_H
#define MAPVIEWMODEL_H

#include <QObject>
#include "mappointsuimodel.h"
#include "../domain/fetchallmappointsusecase.h"
#include "../domain/getmappointmodelusecase.h"
#include "../domain/addmappointusecase.h"

class MapViewModel : public QObject
{
    Q_OBJECT
public:

    explicit MapViewModel(
            FetchAllMapPointsUseCase *fetchAppMapPointsUseCase,
            GetMapPointModelUseCase *getMapPointModelUseCase,
            AddMapPointUseCase *addMapPointUseCase,
            QObject *parent = nullptr
            );

    MapPointsUiModel* getMapPointsUiModel();

public slots:
    void onMapPointPretentderFetched(MapPoint mapPoint);

private:

    AddMapPointUseCase *addMapPointUseCase;
    MapPointsUiModel *mapPointsUiModel = new MapPointsUiModel();

    void mapMapPointAndUpdate(QList<MapPoint*> mapPoints);
};

#endif // MAPVIEWMODEL_H
