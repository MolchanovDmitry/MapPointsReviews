#include "dependencyprovider.h"
#include <QStandardPaths>
#include <QDir>
#include <QtGui/QGuiApplication>
#include <QDebug>
#include <QObject>
#include "stringprovider.h"
#include "data/notificationsender.h"

DependenciesProvider::DependenciesProvider(QObject *parent) : QObject(parent) {

}

QSqlDatabase getDatabase() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug()<<"Путь до базы данных: "<<path;
    QDir dir(path);
    if(!dir.exists()) {
        dir.mkpath(".");
    }
    db.setDatabaseName(path + "/PointsMapReviews.db");
    return db;
}

MapViewModel *DependenciesProvider::provideMapViewModel(QGuiApplication *app) {
    auto db = getDatabase();
    auto stringProvidet = new StringProvider(app);
    auto commentDataSource = new CommentsDataSource(db, app);
    auto mapPointsDbDataSource = new MapPointsDbDataSource(db, app);
    auto notificationSender = new NotificationSender(stringProvidet, app);

    auto repository = new RepositoryImpl(mapPointsDbDataSource,
                                         commentDataSource,
                                         notificationSender,
                                         stringProvidet,
                                         app);

    auto addMapPointUseCase = new AddMapPointUseCase(repository);
    auto getMapPointModelUseCase = new GetMapPointModelUseCase(repository);
    auto fetchAllMapPointsUseCase = new FetchAllMapPointsUseCase(repository);

    auto addCommentUseCase = new AddCommentUseCase(repository);
    auto getCommentsByIdUseCase = new GetCommentsByIdUseCase(repository);
    auto fetchCommentsUseCase = new FetchCommentByMapIdUseCase(repository);

    return new MapViewModel(fetchAllMapPointsUseCase,
                            getMapPointModelUseCase,
                            addMapPointUseCase,
                            addCommentUseCase,
                            fetchCommentsUseCase,
                            getCommentsByIdUseCase);
}

