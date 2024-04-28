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
    mapPointSqlModel->setTable("MapPoints");

    QSqlRecord newRecord = mapPointSqlModel->record();
    newRecord.setValue("title", mapPoint.title);
    newRecord.setValue("description", mapPoint.description);
    newRecord.setValue("latitude", mapPoint.latitude);
    newRecord.setValue("longitude", mapPoint.longitude);
    newRecord.setValue("confirm_status", mapPoint.isConfirmed ? 1 : 0);
    newRecord.setValue("image_urls", mapPoint.imageUrls.join("|"));

    if (!mapPointSqlModel->insertRecord(-1, newRecord)) {
        qCritical() << "Ошибка при добавлении точки в базу: " << mapPointSqlModel->lastError().text();
    } else {
        qDebug() << "Точка " << mapPoint.title << " успешно добавлена";
        mapPointSqlModel->submitAll();  // Отправляем изменения в базу данных
    }
    mapPointSqlModel->select();  // Обновляем модель
}

void MapPointsDbDataSource::addRows(QList<MapPoint*> *mapPoints)
{
    mapPointSqlModel->setTable("MapPoints");
    for (MapPoint* mapPoint : *mapPoints) {
        QSqlRecord newRecord = mapPointSqlModel->record();
        newRecord.setValue("title", mapPoint->title);
        newRecord.setValue("description", mapPoint->description);
        newRecord.setValue("latitude", mapPoint->latitude);
        newRecord.setValue("longitude", mapPoint->longitude);
        newRecord.setValue("confirm_status", mapPoint->isConfirmed ? 1 : 0);
        newRecord.setValue("image_urls", mapPoint->imageUrls.join("|"));

        if (!mapPointSqlModel->insertRecord(-1, newRecord)) {
            qCritical() << "Ошибка при добавлении точки в базу: " << mapPointSqlModel->lastError().text();
        }
    }
    // Submit all changes to the database and update the model
    if (!mapPointSqlModel->submitAll()) {
        qCritical() << "Ошибка при обновлении данных в базе: " << mapPointSqlModel->lastError().text();
    } else {
        qDebug() << "Успешное добавление новых записей. Новое количество строк в модели: " << mapPointSqlModel->rowCount();
    }
    //mapPointSqlModel->select();
}

int MapPointsDbDataSource::getRowCount()
{
    QSqlTableModel model;
    model.setTable("MapPoints");
    model.select();

    if (model.lastError().isValid()) {
        qCritical() << "Ошибка при получении количества записей точек: " << model.lastError().text();
        return 0;
    }

    auto rowCount = model.rowCount();

    qDebug() << "Количество записей: " << rowCount;
    return rowCount;
}

// TODO
void MapPointsDbDataSource::getAll()
{
    mapPointSqlModel->setTable("MapPoints");
    mapPointSqlModel->select();

    if (mapPointSqlModel->lastError().isValid()) {
        qCritical() << "Ошибка при получении всех точек: " << mapPointSqlModel->lastError().text();
    } else {
        int rowCount = mapPointSqlModel->rowCount();
        qDebug() << "Успешный запрос на получение всех точек. Количество точек: " << rowCount;
    }
}

