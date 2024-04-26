#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QException>
#include <QSqlRecord>

#include "mappointsdbdatasource.h"

MapPointsDbDataSource::MapPointsDbDataSource(QSqlDatabase db, QObject *parent) : QObject(parent)
{
    this->db = db;

}

void MapPointsDbDataSource::createTable()
{
    db.transaction();
    if(db.open()) {
        qDebug() << "База данных открыта.";

        QSqlQuery query;

        QString createTable = "CREATE TABLE IF NOT EXISTS "
                                "MapPoints("
                                "title TEXT PRIMARY KEY, "
                                "description TEXT, "
                                "latitude REAL, "
                                "longitude REAL"
                                ");";

        if(!query.exec(createTable)) {
            qCritical() << "Ошибка при создании таблицы: " << query.lastError().text();
        } else{
            qDebug() << "Успешный запрос на создание MapPoints";
        }
    } else {
        qCritical() << "Ошибка при открытии базы данных: " << db.lastError().text();
    }
    db.commit();
}

void MapPointsDbDataSource::addRow(const MapPoint mapPoint)
{
    db.transaction();
    try {
        QSqlQuery query;
        query.prepare("INSERT INTO MapPoints (title, description, latitude, longitude) "
                                "VALUES(?, ?, ?, ?);");
                query.addBindValue(mapPoint.title);
                query.addBindValue(mapPoint.description);
                query.addBindValue(mapPoint.latitude);
                query.addBindValue(mapPoint.longitude);
        if(!query.exec()){
             qCritical() << "Ошибка при добавлении точки в базу: " << query.lastError().text();
        } else {
            qDebug()<<"Точка "<<mapPoint.title<<" успешно добавлена";
        }
    } catch(const QException& e){
        qCritical()<<"Ошибка при добавлении в базу: "<<e.what();
    }
    db.commit();
}

void MapPointsDbDataSource::addRows(const QList<MapPoint> mapPoints)
{

}

int MapPointsDbDataSource::getRowCount()
{
    db.transaction();
    int result = 0;
    try {
        QSqlQuery query;
        QString countQuery = "SELECT COUNT(*) FROM MapPoints;";
        if(!query.exec(countQuery)){
             qCritical() << "Ошибка получении количества записей точек 1: " << query.lastError().text();
        }
        if(query.next()){
             qDebug()<<"check 1: "<<query.value(0);
            result = query.value(0).toInt();
        } else {
            qCritical() << "Ошибка получении количества записей точек 2: " << query.lastError().text();
        }

    }  catch (const QException& e) {
        qCritical()<<"Ошибка получении количества строк: "<<e.what();
    }
    qDebug()<<"Возвращем количество записей: "<<result;

    db.commit();
    return result;
}

const QList<MapPoint> MapPointsDbDataSource::getAll()
{
    db.transaction();
    QList result = QList<MapPoint>();
    try {
        QSqlQuery query;
        QString selectAll = "SELECT title, description, latitude, longitude FROM MapPoints;";
        if(!query.exec(selectAll)){
            qCritical() << "Ошибка получении всех точек 1: " << query.lastError().text();
        }

        mapPointSqlModel->setQuery(query);
//        auto mapPoint = MapPoint();
//        //mapPoint.id = query.value(0).toLongLong();
//        mapPoint.title = query.value(0).toString();
//        mapPoint.description = query.value(1).toString();
//        mapPoint.latitude = query.value(2).toDouble();
//        mapPoint.longitude = query.value(3).toDouble();

//        result.append(mapPoint);
    }  catch (const QException& e) {
        qCritical()<<"Ошибка получении всех точек: "<<e.what();
    }
    db.commit();

    qDebug()<<"Тестовая печать: "<<mapPointSqlModel->rowCount();

    for(int i = 0; i < mapPointSqlModel->rowCount(); ++i) {
        QSqlRecord record = mapPointSqlModel->record(i);

        // Доступ к данным ваших полей
        //int id = record.value("id").toInt();
        QString title = record.value("title").toString();
        QString description = record.value("description").toString();
        double latitude = record.value("latitude").toDouble();
        double longitude = record.value("longitude").toDouble();

        // Здесь вы можете сделать что-то с этими данными
        qDebug()<<"Тестовая печать: " << title << description << latitude << longitude;
    }



    return result;
}
