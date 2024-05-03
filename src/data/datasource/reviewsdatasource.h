#ifndef REVIEWSDATASOURCE_H
#define REVIEWSDATASOURCE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "../model/reviewststablemodel.h"

/**
 * Источник данных отзывов
 */
class ReviewsDataSource : public QObject {
    Q_OBJECT
  public:
    explicit ReviewsDataSource(QSqlDatabase db, QObject *parent = nullptr);

    /** Создать таблицу, если нужно. */
    void createTable();

    /** Получить отзывы по точке [mapPointId]. */
    void fetchReviewsBy(int mapPointId);

    /** Добавить отзыв [review] к точке [mapPointId]. */
    void addReview(int mapPointId, Review review);

    /** Вернуть модель отзывов. */
    ReviewsTableModel* getTableModel();

  private:
    QSqlDatabase db;
    ReviewsTableModel *tableModel = new ReviewsTableModel(this);
};

#endif // REVIEWSDATASOURCE_H
