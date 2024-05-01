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

/**
 *  Собирает все необходимые зависимости для `MapViewModel`
 */
MapViewModel *DependenciesProvider::provideMapViewModel(QGuiApplication *app) {
    auto db = getDatabase();
    auto stringProvidet = new StringProvider(app);
    auto reviewsDataSource = new ReviewsDataSource(db, app);
    auto mapPointsDbDataSource = new MapPointsDbDataSource(db, app);
    auto notificationSender = new NotificationSender(stringProvidet, app);

    auto repository = new RepositoryImpl(mapPointsDbDataSource,
                                         reviewsDataSource,
                                         notificationSender,
                                         stringProvidet,
                                         app);

    auto addMapPointUseCase = new AddMapPointUseCase(repository);
    auto getMapPointModelUseCase = new GetMapPointModelUseCase(repository);
    auto fetchAllMapPointsUseCase = new FetchAllMapPointsUseCase(repository);

    auto addCommentUseCase = new AddReviewUseCase(repository);
    auto getCommentsByIdUseCase = new GetReviewsByIdUseCase(repository);
    auto fetchCommentsUseCase = new FetchReviewsByMapIdUseCase(repository);

    return new MapViewModel(fetchAllMapPointsUseCase,
                            getMapPointModelUseCase,
                            addMapPointUseCase,
                            addCommentUseCase,
                            fetchCommentsUseCase,
                            getCommentsByIdUseCase);
}

