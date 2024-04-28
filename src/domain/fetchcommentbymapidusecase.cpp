#include "fetchcommentbymapidusecase.h"

FetchCommentByMapIdUseCase::FetchCommentByMapIdUseCase(Repository *rep, QObject *parent)
    : QObject(parent),
      rep(rep)
{

}

void FetchCommentByMapIdUseCase::run(int mapPointId){
    rep->fetchCommentsBy(mapPointId);
}
