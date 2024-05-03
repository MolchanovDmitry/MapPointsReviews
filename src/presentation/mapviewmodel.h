#ifndef MAPVIEWMODEL_H
#define MAPVIEWMODEL_H

#include <QObject>
#include "model/mappointsuimodel.h"
#include "../domain/usecases/fetchallmappointsusecase.h"
#include "../domain/usecases/getmappointmodelusecase.h"
#include "../domain/usecases/addmappointusecase.h"
#include "../domain/usecases/addreviewusecase.h"
#include "../domain/usecases/fetchreviewsbymapidusecase.h"
#include "../domain/usecases/getreviewsbyidusecase.h"
#include "model/reviewsuimodel.h"

/**
 * Класс MapViewModel представляет собой ViewModel в архитектуре MVVM (Model-View-ViewModel),
 * которая управляет взаимодействием между UI и бизнес-логикой приложения.
 * Он получает ввод данных от пользователя, передает его в подходящие
 * UseCase (сценарии использования).
 */
class MapViewModel : public QObject {
    Q_OBJECT
  public:

    explicit MapViewModel(
        FetchAllMapPointsUseCase *fetchAppMapPointsUseCase,
        GetMapPointModelUseCase *getMapPointModelUseCase,
        AddMapPointUseCase *addMapPointUseCase,
        AddReviewUseCase *addReviewUseCase,
        FetchReviewsByMapIdUseCase *fetchReviewsUseCase,
        GetReviewsByIdModelUseCase *getReviewsByIdUseCase,
        QObject *parent = nullptr
    );

    /** Возвращает UI модель точек на карте */
    MapPointsUiModel* getMapPointsUiModel();

    /** Возвращает UI модель отзывов к точке */
    ReviewsUiModel* getReviewsUiModel();

  public slots:

    /** Получен претендент на новую точку. (Добавлена точка на карте) */
    void onMapPointPretentderFetched(MapPoint mapPoint);

    /** Добавить новый отзыв к точке */
    void addReview(int mapPointId, Review review);

    /** Получить отзывы к точке. */
    void fetchReviews(int mapPointId);

  private:

    AddMapPointUseCase *addMapPointUseCase;

    AddReviewUseCase *addReviewUseCase;

    FetchReviewsByMapIdUseCase *fetchReviewsUseCase;

    GetReviewsByIdModelUseCase *getReviewsByIdUseCase;

    MapPointsUiModel *mapPointsUiModel = new MapPointsUiModel(this);

    ReviewsUiModel *reviewsUiModel = new ReviewsUiModel(this);

    void mapMapPointAndUpdate(QList<MapPoint*> mapPoints);
};

#endif // MAPVIEWMODEL_H
