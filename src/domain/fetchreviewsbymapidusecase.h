#ifndef FETCHREVIEWSBYMAPIDUSECASE_H
#define FETCHREVIEWSBYMAPIDUSECASE_H

#include <QObject>
#include "repository.h"

/**
 * Сценарий намерения получить отзывы к точке.
 */
class FetchReviewsByMapIdUseCase : public QObject {
    Q_OBJECT
  public:
    explicit FetchReviewsByMapIdUseCase(Repository *rep, QObject *parent = nullptr);

    void run(int mapPointId);

  private:
    Repository *rep;
};

#endif // FETCHREVIEWSBYMAPIDUSECASE_H
