#ifndef ADDCOMMENTHANDLER_H
#define ADDCOMMENTHANDLER_H

#include <QObject>
#include <QDateTime>
#include "../domain/reviews.h"

/**
 * Обработчик намерения добавить отзыв к точке
 */
class AddReviewHandler : public QObject {
    Q_OBJECT
  public:
    explicit AddReviewHandler(QObject *parent = nullptr);

  public slots:

    void addReview(int mapPointId, int starCount, QString comment) {
        Review review;
        review.comment = comment;
        review.starCount = starCount;
        review.date = QDateTime::currentMSecsSinceEpoch();

        emit onAddReviewRequest(mapPointId, review);
    }


  signals:
    void onAddReviewRequest(int mapPointId, Review review);

};

#endif // ADDCOMMENTHANDLER_H
