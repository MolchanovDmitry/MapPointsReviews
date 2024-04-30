#ifndef COMMENTSTABLEMODEL_H
#define COMMENTSTABLEMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include "../domain/comments.h"

/**
 * Sql модель комментариев
 */
class CommentsTableModel : public QSqlTableModel {
    Q_OBJECT
  public:
    explicit CommentsTableModel(QObject *parent = nullptr);

  public slots:
    /**
     *  При изменении произойдет мапинг данных в бизнес модель
     *  с последующим вызовом [commentsFetched]
     */
    void onDataChanged();

  signals:

    /** Уведомляем подпищиков об изменении модели в формате бизнес модели */
    void commentsFetched(Comments *comments);

};

#endif // COMMENTSTABLEMODEL_H
