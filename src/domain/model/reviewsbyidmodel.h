#ifndef REVIEWSBYIDMODEL_H
#define REVIEWSBYIDMODEL_H

#include <QObject>
#include "reviews.h"

/**
 * Бизнесовая модель отзывов.
 * В текущей реализации - прокся между слоем источника данных и слоем представления.
 */
class ReviewsByIdModel : public QObject {
    Q_OBJECT
  public:
    explicit ReviewsByIdModel(QObject *parent = nullptr);

  public slots:
    void updateReviews(Reviews *reviews);

  signals:
    void reviewsUpdated(Reviews *reviews);

};

#endif // REVIEWSBYIDMODEL_H
