#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include "model/mappoint.h"
#include "model/mappointmodel.h"
#include "model/reviewsbyidmodel.h"

/**
 * Контракт репозитория, который служит ориентиром для реализации для слоя источника данных
 */
class Repository : public QObject {
    Q_OBJECT
  public:
    Repository(QObject *parent = nullptr) : QObject(parent) {};

    /**
     *  Намерение получить все точки на карте.
     *  Сами данные вернутся в модели из метода [getMapPointModel].
     */
    virtual void fetchAllMapPoints() = 0;

    /** Намерение добавить точку на карте. */
    virtual void addMapPoint(MapPoint mapPoint) = 0;

    /** Намерение добавить отзыв к точке. */
    virtual void addReview(int mapPointId, Review review) = 0;

    /** Намерение получить отзыв к точке. */
    virtual void fetchReviewsBy(int mapPointId) = 0;

    /** Возвращает бизнес модель точек на карте. */
    virtual MapPointModel *getMapPointModel() = 0;

    /** Возвращает бизнес модель отзывов к точке на карте. */
    virtual ReviewsByIdModel *getReviewsByIdModel() = 0;

};

#endif // REPOSITORY_H
