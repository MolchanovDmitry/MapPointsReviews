#include "dependencyprovider.h"
#include <QStandardPaths>
#include <QDir>

DependenciesProvider::DependenciesProvider(QObject *parent) : QObject(parent)
{

}

QSqlDatabase getDatabase(){
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug()<<"Путь до базы данных: "<<path;
    QDir dir(path);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    db.setDatabaseName(path + "/PointsMapReviews.db");
    return db;
}

MapViewModel *DependenciesProvider::provideMapViewModel()
{
    auto db = getDatabase();
    auto commentDataSource = new CommentsDataSource(db);
    auto mapPointsDbDataSource = new MapPointsDbDataSource(db);
    auto repository = new Repository(mapPointsDbDataSource, commentDataSource);
    auto addMapPointUseCase = new AddMapPointUseCase(repository);
    auto getMapPointModelUseCase = new GetMapPointModelUseCase(repository);
    auto fetchAllMapPointsUseCase = new FetchAllMapPointsUseCase(repository);
    auto addCommentUseCase = new AddCommentUseCase(repository);
    auto fetchCommentsUseCase = new FetchCommentByMapIdUseCase(repository);
    auto getCommentsByIdUseCase = new GetCommentsByIdUseCase(repository);
    return new MapViewModel(fetchAllMapPointsUseCase,
                            getMapPointModelUseCase,
                            addMapPointUseCase,
                            addCommentUseCase,
                            fetchCommentsUseCase,
                            getCommentsByIdUseCase);
}

