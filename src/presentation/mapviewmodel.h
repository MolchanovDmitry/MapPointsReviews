#ifndef MAPVIEWMODEL_H
#define MAPVIEWMODEL_H

#include <QObject>
#include "mappointsuimodel.h"
#include "../domain/fetchallmappointsusecase.h"
#include "../domain/getmappointmodelusecase.h"
#include "../domain/addmappointusecase.h"
#include "../domain/addcommentusecase.h"
#include "../domain/fetchcommentbymapidusecase.h"
#include "../domain/getcommentsbyidusecase.h"
#include "commentsuimodel.h"

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
        AddCommentUseCase *addCommentUseCase,
        FetchCommentByMapIdUseCase *fetchCommentsUseCase,
        GetCommentsByIdUseCase *getCommentsByIdUseCase,
        QObject *parent = nullptr
    );

    /** Возвращает UI модель точек на карте */
    MapPointsUiModel* getMapPointsUiModel();

    /** Возвращает UI модель комментариев к точке */
    CommentsUiModel* getCommentsUiModel();

  public slots:

    /** Получен претендент на новую точку. (Добавлена точка на карте) */
    void onMapPointPretentderFetched(MapPoint mapPoint);

    /** Добавить новый комментарий к точке */
    void addComment(int mapPointId, QString comments);

    /** Получить комментарии к точке. */
    void fetchComments(int mapPointId);

  private:

    AddMapPointUseCase *addMapPointUseCase;

    AddCommentUseCase *addCommentUseCase;

    FetchCommentByMapIdUseCase *fetchCommentsUseCase;

    GetCommentsByIdUseCase *getCommentsByIdUseCase;

    MapPointsUiModel *mapPointsUiModel = new MapPointsUiModel(this);

    CommentsUiModel *commentsUiModel = new CommentsUiModel(this);

    void mapMapPointAndUpdate(QList<MapPoint*> mapPoints);
};

#endif // MAPVIEWMODEL_H
