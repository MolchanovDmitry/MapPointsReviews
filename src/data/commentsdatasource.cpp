#include "commentsdatasource.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QException>
#include <QSqlRecord>

CommentsDataSource::CommentsDataSource(QSqlDatabase db, QObject *parent)
    : QObject(parent),
      db(db)
{

}

void CommentsDataSource::createTable()
{
    if (!db.transaction()) {
        qCritical() << "Ошибка при начале транзакции: " << db.lastError().text();
        return;
    }

    QSqlQuery query;
    QString createTable = "CREATE TABLE IF NOT EXISTS "
                            "Comments("
                            "mapPointId INTEGER, "
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

void CommentsDataSource::fetchCommentsBy(int mapPointId)
{
    qDebug()<<"mapPointId: "<<mapPointId;
    tableModel->setTable("Comments");
    tableModel->setFilter(QString("mapPointId == %1").arg(mapPointId));
    tableModel->select();

    if (tableModel->lastError().isValid()) {
        qCritical() << "Не удалось загрузить комментарии: " << tableModel->lastError().text();
    }
}

void CommentsDataSource::addComment(int mapPointId, QString comment) {
    qDebug() << "Добавляем в базу mapPointId = " << mapPointId << " с комментарием " << comment;

    QSqlQuery query;

    query.prepare("INSERT INTO Comments (mapPointId, comment)"
                  "VALUES (:mapPointId, :comment)");
    query.bindValue(":mapPointId", mapPointId);
    query.bindValue(":comment", comment);

    if (!query.exec()) {
        qCritical() << "Ошибка при добавлении комментария: " << query.lastError().text();
        return;
    }

    qDebug() << "Комментарий отправлен в tableModel";

    tableModel->select();
}

CommentsTableModel *CommentsDataSource::getTableModel(){
    return tableModel;
}
