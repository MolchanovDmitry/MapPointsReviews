#ifndef GETREVIEWSBYIDUSECASE_H
#define GETREVIEWSBYIDUSECASE_H

#include <QObject>
#include "../repository.h"
#include "../model/reviewsbyidmodel.h"

/**
 * Сценарий получения модели отзывов к точке.
 */
class GetReviewsByIdModelUseCase : public QObject {
    Q_OBJECT
  public:
    explicit GetReviewsByIdModelUseCase(Repository *repository, QObject *parent = nullptr);

    ReviewsByIdModel* run();

  private:
    Repository *repository;

};

#endif // GETREVIEWSBYIDUSECASE_H
