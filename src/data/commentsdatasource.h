#ifndef COMMENTSDATASOURCE_H
#define COMMENTSDATASOURCE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "commentstablemodel.h"

class CommentsDataSource : public QObject
{
    Q_OBJECT
public:
    explicit CommentsDataSource(QSqlDatabase db, QObject *parent = nullptr);

    void createTable();

    void fetchCommentsBy(int mapPointId);

    void addComment(int mapPointId, QString comment);

    CommentsTableModel* getTableModel();

private:
    QSqlDatabase db;
    CommentsTableModel *tableModel = new CommentsTableModel();
};

#endif // COMMENTSDATASOURCE_H
