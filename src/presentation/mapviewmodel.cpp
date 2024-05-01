#include "mapviewmodel.h"

MapViewModel::MapViewModel(
    FetchAllMapPointsUseCase *fetchAppMapPointsUseCase,
    GetMapPointModelUseCase *getMapPointModelUseCase,
    AddMapPointUseCase *addMapPointUseCase,
    AddReviewUseCase *addCommentUseCase,
    FetchReviewsByMapIdUseCase *fetchCommentsUseCase,
    GetReviewsByIdUseCase *getCommentsByIdUseCase,
    QObject *parent)
    : QObject(parent)
    , addMapPointUseCase(addMapPointUseCase)
    , addReviewUseCase(addCommentUseCase)
    , fetchReviewsUseCase(fetchCommentsUseCase)
    , getReviewsByIdUseCase(getCommentsByIdUseCase) {
    connect(getMapPointModelUseCase->run(), &MapPointModel::mapPointsUpdated,
            this, &MapViewModel::mapMapPointAndUpdate);
    connect(getCommentsByIdUseCase->run(), &ReviewsByIdModel::reviewsUpdated,
            reviewsUiModel, &ReviewsUiModel::updateReviews);

    fetchAppMapPointsUseCase->run();
}

void MapViewModel::mapMapPointAndUpdate(QList<MapPoint*> mapPoints) {
    QList<MapPointUi*> uiMapPoints = QList<MapPointUi*>();
    foreach(MapPoint *mapPoint, mapPoints) {
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

MapPointsUiModel* MapViewModel::getMapPointsUiModel() {
    return mapPointsUiModel;
}

ReviewsUiModel *MapViewModel::getReviewsUiModel() {
    return reviewsUiModel;
}

void MapViewModel::onMapPointPretentderFetched(MapPoint mapPoint) {
    printMapPoint(&mapPoint, "onMapPointPretentderFetched");
    addMapPointUseCase->run(mapPoint);
}

void MapViewModel::addReview(int mapPointId, Review review) {
    qDebug()<<"mapPointId = "<<mapPointId<<" comments = "<<review.comment;
    addReviewUseCase->run(mapPointId, review);
}

void MapViewModel::fetchReviews(int mapPointId) {
    reviewsUiModel->clear();
    fetchReviewsUseCase->run(mapPointId);
}
