#include "getreviewsbyidusecase.h"

GetReviewsByIdUseCase::GetReviewsByIdUseCase(Repository *repository, QObject *parent)
    : QObject(parent),
      repository(repository) {

}

ReviewsByIdModel *GetReviewsByIdUseCase::run() {
    return repository->getReviewsByIdModel();
}

