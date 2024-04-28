#ifndef COMMENTSDATASOURCE_H
#define COMMENTSDATASOURCE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>

class CommentsDataSource : public QObject
{
    Q_OBJECT
public:
    explicit CommentsDataSource(QSqlDatabase db, QObject *parent = nullptr);

    void createTable();

    void fetchCommentsBy(int mapPointId);

    void addComment(int mapPointId, QString comment);

    QSqlTableModel* getTableModel();

private:
    QSqlDatabase db;
    QSqlTableModel *tableModel = new QSqlTableModel();
};

#endif // COMMENTSDATASOURCE_H
