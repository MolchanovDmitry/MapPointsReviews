#ifndef COMMENTSDATASOURCE_H
#define COMMENTSDATASOURCE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "commentstablemodel.h"

/**
 * Источник данных комментариев
 */
class CommentsDataSource : public QObject {
    Q_OBJECT
  public:
    explicit CommentsDataSource(QSqlDatabase db, QObject *parent = nullptr);

    /** Создать таблицу, если нужно. */
    void createTable();

    /** Получить комментарии по точке [mapPointId]. */
    void fetchCommentsBy(int mapPointId);

    /** Добавить комментарий [comment] к точке [mapPointId]. */
    void addComment(int mapPointId, QString comment);

    /** Вернуть модель комментариев. */
    CommentsTableModel* getTableModel();

  private:
    QSqlDatabase db;
    CommentsTableModel *tableModel = new CommentsTableModel();
};

#endif // COMMENTSDATASOURCE_H
