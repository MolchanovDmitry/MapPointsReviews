#ifndef REPOSITORYIMPL_H
#define REPOSITORYIMPL_H

#include <QObject>
#include <QMutex>

#include "mappointsdbdatasource.h"
#include "commentsdatasource.h"
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
        CommentsDataSource *commentsDataSource,
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

    /** Добавить комментарий к точке. */
    void addComment(int mapPointId, QString comment) override;

    /** Получить комментарии к точке. */
    void fetchCommentsBy(int mapPointId) override;

    /** Возвращает бизнес модель точек на карте. */
    MapPointModel *getMapPointModel() override;

    /** Возвращает бизнес модель комментариев к точке на карте. */
    CommentsByIdModel *getCommentsByIdModel() override;

  private:

    CommentsDataSource *commentsDataSource;

    MapPointsDbDataSource *mapPointsDataSource;

    NotificationSender *notificationSender;

    StringProvider *stringProvider;

    MapPointModel *mapPointModel = new MapPointModel(this);

    CommentsByIdModel *commentsByIdModel = new CommentsByIdModel(this);

    QMutex commentsDataSourceMutex;

    QMutex mapPointsDataSourceMutex;

    void addFakeData();

};

#endif // REPOSITORYIMPL_H
