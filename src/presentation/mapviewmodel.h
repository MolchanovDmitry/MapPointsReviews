#ifndef MAPVIEWMODEL_H
#define MAPVIEWMODEL_H

#include <QObject>
#include "mappointsuimodel.h"
#include "../domain/fetchallmappointsusecase.h"
#include "../domain/getmappointmodelusecase.h"
#include "../domain/addmappointusecase.h"
#include "../domain/addcommentusecase.h"
#include "../domain/fetchcommentbymapidusecase.h"

class MapViewModel : public QObject
{
    Q_OBJECT
public:

    explicit MapViewModel(
            FetchAllMapPointsUseCase *fetchAppMapPointsUseCase,
            GetMapPointModelUseCase *getMapPointModelUseCase,
            AddMapPointUseCase *addMapPointUseCase,
            AddCommentUseCase *addCommentUseCase,
            FetchCommentByMapIdUseCase *fetchCommentsUseCase,
            QObject *parent = nullptr
            );

    MapPointsUiModel* getMapPointsUiModel();

public slots:

    void onMapPointPretentderFetched(MapPoint mapPoint);

    void addComment(int mapPointId, QString comments);

private:

    AddMapPointUseCase *addMapPointUseCase;

    AddCommentUseCase *addCommentUseCase;

    FetchCommentByMapIdUseCase *fetchCommentsUseCase;

    MapPointsUiModel *mapPointsUiModel = new MapPointsUiModel();

    void mapMapPointAndUpdate(QList<MapPoint*> mapPoints);
};

#endif // MAPVIEWMODEL_H
