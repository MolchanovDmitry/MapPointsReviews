#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include "mappoint.h"
#include "mappointmodel.h"
#include "commentbyidmodel.h"

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

    /** Намерение добавить комментарий к точке. */
    virtual void addComment(int mapPointId, QString comment) = 0;

    /** Намерение получить комментарии к точке. */
    virtual void fetchCommentsBy(int mapPointId) = 0;

    /** Возвращает бизнес модель точек на карте. */
    virtual MapPointModel *getMapPointModel() = 0;

    /** Возвращает бизнес модель комментариев к точке на карте. */
    virtual CommentsByIdModel *getCommentsByIdModel() = 0;

};

#endif // REPOSITORY_H
