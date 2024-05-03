#include "fetchreviewsbymapidusecase.h"

FetchReviewsByMapIdUseCase::FetchReviewsByMapIdUseCase(Repository *rep, QObject *parent)
    : QObject(parent),
      rep(rep) {

}

void FetchReviewsByMapIdUseCase::run(int mapPointId) {
    rep->fetchReviewsBy(mapPointId);
}
