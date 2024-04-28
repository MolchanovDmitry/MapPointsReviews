#include "addcommentusecase.h"

AddCommentUseCase::AddCommentUseCase(Repository *rep, QObject *parent)
    : QObject(parent),
      rep(rep)
{

}

void AddCommentUseCase::run(int mapPointId, QString comment){
    rep->addComment(mapPointId,comment);
}
