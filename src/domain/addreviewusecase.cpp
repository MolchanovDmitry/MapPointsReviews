#include "addreviewusecase.h"
#include <QtConcurrent/QtConcurrent>

AddReviewUseCase::AddReviewUseCase(Repository *rep, QObject *parent)
    : QObject(parent),
      rep(rep) {

}

void AddReviewUseCase::run(int mapPointId, Review review) {
    QtConcurrent::run([=]() {
        rep->addReview(mapPointId, review);
    });
}
