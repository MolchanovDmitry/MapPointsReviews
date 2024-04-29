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
    tableModel->setTable("Comments");
    tableModel->setFilter(QString("mapPointId == %1").arg(mapPointId));
    tableModel->select();

    if (tableModel->lastError().isValid()) {
        qCritical() << "Не удалось загрузить комментарии: " << tableModel->lastError().text();
    }
}

void CommentsDataSource::addComment(int mapPointId, QString comment)
{
    qDebug()<<"CommentsDataSource::addComment mapPointId = "<<mapPointId<<" comment = "<<comment;

    tableModel->setTable("Comments");
    tableModel->select();

    QSqlRecord record = tableModel->record();
    record.setValue("mapPointId", mapPointId);
    record.setValue("comment", comment);
    if (!tableModel->insertRecord(-1, record)) {
        qCritical() << "Ошибка при добавлении комментария: " << tableModel->lastError().text();
        return;
    }
    if (!tableModel->submitAll()) {
        qCritical() << "Не удалось отправить изменения в базу данных: " << tableModel->lastError().text();
        return;
    } else{
        qDebug()<<"Комментарий отправлен в tableModel";
    }
    tableModel->select();
}

CommentsTableModel *CommentsDataSource::getTableModel(){
    return tableModel;
}
