#include "repository.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlRecord> // TODO

Repository::Repository(QObject *parent) : QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("PointsMapReviews.db");

    this->dataSource = new MapPointsDbDataSource(db, parent);
    this->dataSource->createTable();
    addFakeData();

    connect(this->dataSource->mapPointSqlModel,&MapPointSqlModel::mapPointsFromDataUpdated,
            this->mapPointModel, &MapPointModel::onMapPointsUpdated);
}

void Repository::addFakeData()
{
    int rowCount = dataSource->getRowCount();
    if(rowCount == 0){
        for (int i = 0; i < 10; ++i) {
            auto mapPoint = MapPoint();
            mapPoint.title = QString("Title %1").arg(i + 1);
            mapPoint.description = QString("Description %1").arg(i + 1);
            mapPoint.latitude = (56.8486 + (qrand() % 1000) * 0.00006); // 56.8486 + "шум" в пределах 0...0.06
            mapPoint.longitude = (35.8507 + (qrand() % 1000) * 0.00013); // 35.8507 + "шум" в пределах 0...0.13
            qDebug()<<"Записываем фейковую строку: "<<mapPoint.title<<" "<<mapPoint.description<<" "<<mapPoint.latitude<<" "<<mapPoint.longitude;
            dataSource->addRow(mapPoint);
        }
    }
}

MapPointModel* Repository::getAllMapPoints()
{
    dataSource->getAll();
    return mapPointModel;
}


