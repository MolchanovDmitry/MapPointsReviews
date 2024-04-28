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

void MapPointsDbDataSource::createTables()
{
    if(!db.open()) {
        qCritical() << "Ошибка при открытии базы данных: " << db.lastError().text();
        return;
    }
    createMapPointTable();
}

void MapPointsDbDataSource::createMapPointTable()
{
    if (!db.transaction()) {
        qCritical() << "Ошибка при начале транзакции: " << db.lastError().text();
        return;
    }

    QSqlQuery query;
    QString createTable = "CREATE TABLE IF NOT EXISTS "
                            "MapPoints("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "title TEXT, "
                            "description TEXT, "
                            "latitude REAL, "
                            "longitude REAL, "
                            "confirm_status INTEGER, "
                            "image_urls TEXT"
                            ");";

    if(!query.exec(createTable)) {
        qCritical() << "Ошибка при создании таблицы: " << query.lastError().text();
        db.rollback();
    } else {
        qDebug() << "Успешный запрос на создание MapPoints";
        db.commit();
    }
}

void MapPointsDbDataSource::addRow(const MapPoint mapPoint)
{
    if (!db.transaction()) {
        qCritical() << "Ошибка при начале транзакции: " << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO MapPoints (title, description, latitude, longitude, confirm_status, image_urls) "
                            "VALUES(?, ?, ?, ?, ?);");
            query.addBindValue(mapPoint.title);
            query.addBindValue(mapPoint.description);
            query.addBindValue(mapPoint.latitude);
            query.addBindValue(mapPoint.longitude);
            query.addBindValue(mapPoint.isConfirmed ? 1 : 0);
            query.addBindValue(mapPoint.imageUrls.join("|"));
    if(!query.exec()) {
         qCritical() << "Ошибка при добавлении точки в базу: " << query.lastError().text();
         db.rollback();
    } else {
        qDebug()<<"Точка "<<mapPoint.title<<" успешно добавлена";
        db.commit();
    }
}

void MapPointsDbDataSource::addRows(QList<MapPoint*> *mapPoints)
{
    if (!db.transaction()) {
        qCritical() << "Ошибка при начале транзакции: " << db.lastError().text();
        return;
    }

    // Строим запрос, добавляя каждую точку в "values"
    QStringList rows;
    for (const MapPoint* point : *mapPoints)
    {
        QStringList row;
        row << QString("'%1'").arg(point->title)
            << QString("'%1'").arg(point->description)
            << QString("%1").arg(point->latitude)
            << QString("%1").arg(point->longitude)
            << QString("%1").arg(point->isConfirmed ? 1 : 0)
            << QString("'%1'").arg(point->imageUrls.join("|"));;

        rows << QString("(%1)").arg(row.join(","));
    }

    QSqlQuery query;

    query.prepare(QString(
        "INSERT INTO MapPoints (title, description, latitude, longitude, confirm_status, image_urls) "
        "VALUES %1").arg(rows.join(", ")));

    if(!query.exec()) {
        qCritical() << "Ошибка при добавлении точек в базу данных: " << db.lastError().text();
        db.rollback();
    } else {
        qDebug() << "Точки успешно добавлены в базу данных.";
        db.commit();
    }
}

int MapPointsDbDataSource::getRowCount()
{
    if (!db.transaction()) {
        qCritical() << "Ошибка при начале транзакции: " << db.lastError().text();
        return 0;
    }
    int result = 0;
    QSqlQuery query;
    QString countQuery = "SELECT COUNT(*) FROM MapPoints;";
    if(!query.exec(countQuery)){
         qCritical() << "Ошибка получении количества записей точек 1: " << query.lastError().text();
    }
    if(query.next()){
         qDebug()<<"check 1: "<<query.value(0);
        result = query.value(0).toInt();
        db.commit();
    } else {
        qCritical() << "Ошибка получении количества записей точек 2: " << query.lastError().text();
        db.rollback();
    }

    return result;
}

// TODO
void MapPointsDbDataSource::getAll()
{
    if (!db.transaction()) {
        qCritical() << "Ошибка при начале транзакции: " << db.lastError().text();
        return;
    }
    QSqlQuery query;
    QString selectAll = "SELECT id, title, description, latitude, longitude, confirm_status, image_urls FROM MapPoints;";
    if(!query.exec(selectAll)) {
        qCritical() << "Ошибка получении всех точек 1: " << query.lastError().text();
        db.rollback();
    } else {
        db.commit();
    }
    mapPointSqlModel->setQuery(query);
}

