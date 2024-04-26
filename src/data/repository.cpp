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
    this->dataSource->getRowCount();//TODO удалить

    qDebug()<<"check 1";
    connect(this->dataSource->mapPointSqlModel, &MapPointSqlModel::dataChanged, this->dataSource->mapPointSqlModel, &MapPointSqlModel::onDataChanged);

    connect(this->dataSource->mapPointSqlModel, &MapPointSqlModel::modelReset, [this]() {
        qDebug() << "Model was reset";
    });

    connect(this->dataSource->mapPointSqlModel, &QSqlQueryModel::modelReset, this->dataSource->mapPointSqlModel, &MapPointSqlModel::onDataChanged);

    connect(this->dataSource->mapPointSqlModel,&MapPointSqlModel::mapPointsFromDataUpdated,
            this->mapPointModel, &MapPointModel::onMapPointsUpdated);
    qDebug()<<"check 2";
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

    for(int i = 0; i < dataSource->mapPointSqlModel->rowCount(); ++i) {
        QSqlRecord record = dataSource->mapPointSqlModel->record(i);

        // Доступ к данным ваших полей
        //int id = record.value("id").toInt();
        QString title = record.value("title").toString();
        QString description = record.value("description").toString();
        double latitude = record.value("latitude").toDouble();
        double longitude = record.value("longitude").toDouble();

        // Здесь вы можете сделать что-то с этими данными
        qDebug()<<"Тестовая печать: 1 " << title << description << latitude << longitude;
    }
    return mapPointModel;
}


