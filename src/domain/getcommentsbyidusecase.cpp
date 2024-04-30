#include "getcommentsbyidusecase.h"

GetCommentsByIdUseCase::GetCommentsByIdUseCase(Repository *repository, QObject *parent)
    : QObject(parent),
      repository(repository) {

}

CommentsByIdModel *GetCommentsByIdUseCase::run() {
    return repository->getCommentsByIdModel();
}

