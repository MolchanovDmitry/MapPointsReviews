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
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "title TEXT, "
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

void MapPointsDbDataSource::addRows(QList<MapPoint*> *mapPoints)
{
    if (!db.transaction())
        {
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
                << QString("%1").arg(point->longitude);

            rows << QString("(%1)").arg(row.join(", "));
        }

        QSqlQuery query;
        query.prepare(QString(
            "INSERT INTO MapPoints (title, description, latitude, longitude) "
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

// TODO
void MapPointsDbDataSource::getAll()
{
    db.transaction();
    try {
        QSqlQuery query;
        QString selectAll = "SELECT id, title, description, latitude, longitude FROM MapPoints;";
        if(!query.exec(selectAll)){
            qCritical() << "Ошибка получении всех точек 1: " << query.lastError().text();
        }

        mapPointSqlModel->setQuery(query);
    }  catch (const QException& e) {
        qCritical()<<"Ошибка получении всех точек: "<<e.what();
    }
    db.commit();
}
