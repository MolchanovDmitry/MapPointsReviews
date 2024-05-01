#ifndef GETREVIEWSBYIDUSECASE_H
#define GETREVIEWSBYIDUSECASE_H

#include <QObject>
#include "repository.h"
#include "reviewsbyidmodel.h"

/**
 * Сценарий получения модели отзывов к точке.
 */
class GetReviewsByIdUseCase : public QObject {
    Q_OBJECT
  public:
    explicit GetReviewsByIdUseCase(Repository *repository, QObject *parent = nullptr);

    ReviewsByIdModel* run();

  private:
    Repository *repository;

};

#endif // GETREVIEWSBYIDUSECASE_H
