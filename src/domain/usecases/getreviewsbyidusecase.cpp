#include "getreviewsbyidusecase.h"

GetReviewsByIdModelUseCase::GetReviewsByIdModelUseCase(Repository *repository, QObject *parent)
    : QObject(parent),
      repository(repository) {

}

ReviewsByIdModel *GetReviewsByIdModelUseCase::run() {
    return repository->getReviewsByIdModel();
}

