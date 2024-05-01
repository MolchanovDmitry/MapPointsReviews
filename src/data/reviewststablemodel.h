#ifndef REVIEWSTSTABLEMODEL_H
#define REVIEWSTSTABLEMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include "../domain/reviews.h"

/**
 * Sql модель отзывов
 */
class ReviewsTableModel : public QSqlTableModel {
    Q_OBJECT
  public:
    explicit ReviewsTableModel(QObject *parent = nullptr);

  public slots:
    /**
     *  При изменении произойдет мапинг данных в бизнес модель
     *  с последующим вызовом [reviewsFetched]
     */
    void onDataChanged();

  signals:

    /** Уведомляем подпищиков об изменении модели в формате бизнес модели */
    void reviewsFetched(Reviews *reviews);

};

#endif // REVIEWSTSTABLEMODEL_H
