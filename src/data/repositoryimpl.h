#ifndef REPOSITORYIMPL_H
#define REPOSITORYIMPL_H

#include <QObject>
#include <QMutex>

#include "mappointsdbdatasource.h"
#include "reviewsdatasource.h"
#include "notificationsender.h"
#include "../domain/repository.h"
#include "../stringprovider.h"

/**
 * Реализация контракта репозитория.
 */
class RepositoryImpl : public Repository {
    Q_OBJECT
  public:
    explicit RepositoryImpl(
        MapPointsDbDataSource *mapPointsDbDataSource,
        ReviewsDataSource *reviewsDataSource,
        NotificationSender *notificationSender,
        StringProvider *stringProvider,
        QObject *parent = nullptr
    );

    /**
     *  Получить все точки на карте.
     *  Сами данные вернутся в модели из метода [getMapPointModel].
     */
    void fetchAllMapPoints() override;

    /** Добавить точку на карте. */
    void addMapPoint(MapPoint mapPoint) override;

    /** Добавить отзыв к точке. */
    void addReview(int mapPointId, Review review) override;

    /** Получить отзывы к точке. */
    void fetchReviewsBy(int mapPointId) override;

    /** Возвращает бизнес модель точек на карте. */
    MapPointModel *getMapPointModel() override;

    /** Возвращает бизнес модель комментариев к точке на карте. */
    ReviewsByIdModel *getReviewsByIdModel() override;

  private:

    ReviewsDataSource *reviewsDataSource;

    MapPointsDbDataSource *mapPointsDataSource;

    NotificationSender *notificationSender;

    StringProvider *stringProvider;

    MapPointModel *mapPointModel = new MapPointModel(this);

    ReviewsByIdModel *reviewsByIdModel = new ReviewsByIdModel(this);

    QMutex reviewsDataSourceMutex;

    QMutex mapPointsDataSourceMutex;

    void addFakeData();

};

#endif // REPOSITORYIMPL_H
