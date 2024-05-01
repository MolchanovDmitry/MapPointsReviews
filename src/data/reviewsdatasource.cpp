#include "reviewsdatasource.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QException>
#include <QSqlRecord>

ReviewsDataSource::ReviewsDataSource(QSqlDatabase db, QObject *parent)
    : QObject(parent),
      db(db) {
}

void ReviewsDataSource::createTable() {
    if (!db.transaction()) {
        qCritical() << "Ошибка при начале транзакции: " << db.lastError().text();
        return;
    }

    QSqlQuery query;
    QString createTable = "CREATE TABLE IF NOT EXISTS "
                          "Comments("
                          "mapPointId INTEGER, "
                          "starCount INTEGER, "
                          "comment TEXT"
                          ");";

    if(!query.exec(createTable)) {
        qCritical() << "Ошибка при создании таблицы Comments: " << query.lastError().text();
        db.rollback();
    } else {
        qDebug() << "Успешный запрос на создание Comments";
        db.commit();
    }
}

void ReviewsDataSource::fetchReviewsBy(int mapPointId) {
    qDebug()<<"mapPointId: "<<mapPointId;
    tableModel->setTable("Comments");
    tableModel->setFilter(QString("mapPointId == %1").arg(mapPointId));
    tableModel->select();

    if (tableModel->lastError().isValid()) {
        qCritical() << "Не удалось загрузить комментарии: " << tableModel->lastError().text();
    }
}

void ReviewsDataSource::addReview(int mapPointId, Review review) {
    qDebug() << "Добавляем в базу mapPointId = " << mapPointId << " с комментарием " << review.comment;

    QSqlQuery query;

    query.prepare("INSERT INTO Comments (mapPointId, starCount, comment)"
                  "VALUES (:mapPointId, :starCount, :comment)");
    query.bindValue(":mapPointId", mapPointId);
    query.bindValue(":starCount", review.starCount);
    query.bindValue(":comment", review.comment);

    if (!query.exec()) {
        qCritical() << "Ошибка при добавлении комментария: " << query.lastError().text();
        return;
    }

    qDebug() << "Комментарий отправлен в tableModel";

    tableModel->select();
}

ReviewsTableModel *ReviewsDataSource::getTableModel() {
    return tableModel;
}
