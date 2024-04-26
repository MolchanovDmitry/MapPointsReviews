#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QException>

#include "mappointsdbdatasource.h"

MapPointsDbDataSource::MapPointsDbDataSource(QSqlDatabase db, QObject *parent) : QObject(parent)
{
    this->db = db;

}

void MapPointsDbDataSource::createTable()
{

    if(db.open()) {
        QSqlQuery query;

        QString createTable = "CREATE TABLE IF NOT EXISTS "
                                "MapPoints("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "title TEXT, "
                                "description TEXT, "
                                "latitude REAL, "
                                "longitude REAL"
                                ")";

        if(!query.exec(createTable)) {
            qCritical() << "Ошибка при создании таблицы: " << query.lastError().text();
        }
    } else {
        qCritical() << "Ошибка при открытии базы данных: " << db.lastError().text();
    }

    db.close();
}

void MapPointsDbDataSource::addRow(const MapPoint mapPoint)
{
    try {
        QSqlQuery query;
        QString insertTableTemplate = "INSERT INTO MapPoints (title, description, latitude, longitude) "
                                "VALUES(%1, %2, %3, %4)";
        QString totalQuerry = insertTableTemplate
                .arg(mapPoint.title)
                .arg(mapPoint.description)
                .arg(mapPoint.latitude)
                .arg(mapPoint.longitude);
        query.exec(totalQuerry);
    } catch(const QException& e){
        qCritical()<<"Ошибка при добавлении в базу: "<<e.what();
    }

}

void MapPointsDbDataSource::addRows(const QList<MapPoint> mapPoints)
{

}

int MapPointsDbDataSource::getRowCount()
{
    int result = 0;
    try {
        QSqlQuery query;
        QString countQuery = "SELECT count(*) FROM MapPoints";
        query.exec(countQuery);
        query.next();
        result = query.value(0).toInt();
    }  catch (const QException& e) {
        qCritical()<<"Ошибка получении количества строк: "<<e.what();
    }
    return result;
}

const QList<MapPoint> MapPointsDbDataSource::getAll()
{
    QList result = QList<MapPoint>();
    try {
        QSqlQuery query;
        QString selectAll = "SELECT id, title, description, latitude, longitude FROM MapPoints";
        query.exec(selectAll);
        query.next();

        auto mapPoint = MapPoint();
        mapPoint.id = query.value(0).toLongLong();
        mapPoint.title = query.value(1).toString();
        mapPoint.description = query.value(2).toString();
        mapPoint.latitude = query.value(3).toDouble();
        mapPoint.longitude = query.value(4).toDouble();

        result.append(mapPoint);
    }  catch (const QException& e) {
        qCritical()<<"Ошибка получении всех точек: "<<e.what();
    }
    return result;
}
