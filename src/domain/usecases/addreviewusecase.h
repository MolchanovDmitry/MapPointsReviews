#ifndef ADDREVIEWUSECASE_H
#define ADDREVIEWUSECASE_H

#include <QObject>
#include "../repository.h"

/**
 * Сценарий добавления отзыва к точке.
 */
class AddReviewUseCase : public QObject {
    Q_OBJECT
  public:
    explicit AddReviewUseCase(Repository *rep, QObject *parent = nullptr);

    void run(int mapPointId, Review review);

  private:
    Repository *rep;

};

#endif // ADDREVIEWUSECASE_H
