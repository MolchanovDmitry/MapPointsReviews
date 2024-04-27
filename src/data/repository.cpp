#include "repository.h"

#include <QSqlDatabase>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>
#include <random>

int getRandomSign()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);

    return (distribution(gen) == 0) ? -1 : 1;
}

QList<MapPoint*>* getMockData(QString placeName, int generateCount, double placeLatitude, double placeLongitude, double thresholdLatitude, double thresholdLongitude){
    qDebug()<<"Добавляем "<<generateCount<<" мокнутых точек для "<<placeName;

    QList<MapPoint*> *result = new QList<MapPoint*>();
    for (int i = 0; i < generateCount; ++i) {
        auto mapPoint = new MapPoint();
        mapPoint->title = QString("%1 %2").arg(placeName).arg(i + 1);
        mapPoint->description = QString("Описание %1 для %2").arg(i + 1).arg(placeName);
        mapPoint->latitude = (placeLatitude + (qrand() % 1000) * thresholdLatitude * getRandomSign()); // 56.8486 + "шум" в пределах 0...0.06
        mapPoint->longitude = (placeLongitude + (qrand() % 1000) * thresholdLongitude * getRandomSign()); // 35.8507 + "шум" в пределах 0...0.13
        result->append(mapPoint);
    }
    return result;
}

Repository::Repository(QObject *parent) : QObject(parent)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug()<<"Путь до базы данных: "<<path;
    QDir dir(path);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    db.setDatabaseName(path + "/PointsMapReviews.db");

    this->dataSource = new MapPointsDbDataSource(db, parent);
    this->dataSource->createTable();

    int rowCount = dataSource->getRowCount();
    if(rowCount == 0){
        auto tverMapPoints = getMockData("Тверь", 50, 56.8486, 35.8507, 0.00006, 0.00013);
        auto moscowMapPoints = getMockData("Москва", 500, 55.751244, 37.618423, 0.00012, 0.0002);
        this->dataSource->addRows(tverMapPoints);
        this->dataSource->addRows(moscowMapPoints);
    }

    connect(this->dataSource->mapPointSqlModel,&MapPointSqlModel::mapPointsFromDataUpdated,
            this->mapPointModel, &MapPointModel::updateMapPoints);
}

void Repository::fetchAllMapPoints()
{
    dataSource->getAll();
}


