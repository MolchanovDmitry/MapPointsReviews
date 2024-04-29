#include "mapviewmodel.h"


MapViewModel::MapViewModel(
        FetchAllMapPointsUseCase *fetchAppMapPointsUseCase,
        GetMapPointModelUseCase *getMapPointModelUseCase,
        AddMapPointUseCase *addMapPointUseCase,
        AddCommentUseCase *addCommentUseCase,
        FetchCommentByMapIdUseCase *fetchCommentsUseCase,
        GetCommentsByIdUseCase *getCommentsByIdUseCase,
        QObject *parent)
    : QObject(parent)
    , addMapPointUseCase(addMapPointUseCase)
    , addCommentUseCase(addCommentUseCase)
    , fetchCommentsUseCase(fetchCommentsUseCase)
    , getCommentsByIdUseCase(getCommentsByIdUseCase)
{
    connect(getMapPointModelUseCase->run(), &MapPointModel::mapPointsUpdated,
            this, &MapViewModel::mapMapPointAndUpdate);
    connect(getCommentsByIdUseCase->run(), &CommentsByIdModel::commentsUpdated,
            commentsUiModel, &CommentsUiModel::updateComments);

    fetchAppMapPointsUseCase->run();
}

void MapViewModel::mapMapPointAndUpdate(QList<MapPoint*> mapPoints)
{
    qDebug()<<"MapViewModel::mapMapPointAndUpdate count"<<mapPoints.count();
    QList<MapPointUi*> uiMapPoints = QList<MapPointUi*>();
    foreach(MapPoint *mapPoint, mapPoints){
        uiMapPoints << new MapPointUi(mapPoint->id,
                                      mapPoint->title,
                                      mapPoint->description,
                                      mapPoint->latitude,
                                      mapPoint->longitude,
                                      mapPoint->isConfirmed,
                                      mapPoint->imageUrls);
    }
    mapPointsUiModel->updateMapPoints(uiMapPoints);
}

MapPointsUiModel* MapViewModel::getMapPointsUiModel()
{
    return mapPointsUiModel;
}

CommentsUiModel *MapViewModel::getCommentsUiModel(){
    return commentsUiModel;
}

void MapViewModel::onMapPointPretentderFetched(MapPoint mapPoint){
    printMapPoint(&mapPoint, "onMapPointPretentderFetched");
    addMapPointUseCase->run(mapPoint);
}

void MapViewModel::addComment(int mapPointId, QString comments)
{
    qDebug()<<"MapViewModel::addComment mapPointId = "<<mapPointId<<" comments = "<<comments;
    addCommentUseCase->run(mapPointId, comments);
}

void MapViewModel::fetchComment(int mapPointId)
{
    fetchCommentsUseCase->run(mapPointId);
}
