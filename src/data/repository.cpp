#include "repository.h"

#include <QSqlDatabase>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>
#include <random>

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
    addFakeData();

    connect(this->dataSource->mapPointSqlModel,&MapPointSqlModel::mapPointsFromDataUpdated,
            this->mapPointModel, &MapPointModel::updateMapPoints);
}

int getRandomSign()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);

    return (distribution(gen) == 0) ? -1 : 1;
}

void Repository::addFakeData()
{
    qDebug()<<"Добавляем фейковые данные";
    int rowCount = dataSource->getRowCount();
    if(rowCount == 0){
        for (int i = 0; i < 100; ++i) {
            auto mapPoint = MapPoint();
            mapPoint.title = QString("Title %1").arg(i + 1);
            mapPoint.description = QString("Description %1").arg(i + 1);
            mapPoint.latitude = (56.8486 + (qrand() % 1000) * 0.00006 * getRandomSign()); // 56.8486 + "шум" в пределах 0...0.06
            mapPoint.longitude = (35.8507 + (qrand() % 1000) * 0.00013 * getRandomSign()); // 35.8507 + "шум" в пределах 0...0.13
            qDebug()<<"Записываем фейковую строку: "<<mapPoint.title<<" "<<mapPoint.description<<" "<<mapPoint.latitude<<" "<<mapPoint.longitude;
            dataSource->addRow(mapPoint);
        }
    }
}

void Repository::fetchAllMapPoints()
{
    dataSource->getAll();
}


