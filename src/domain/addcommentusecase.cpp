#include "addcommentusecase.h"
#include <QtConcurrent/QtConcurrent>

AddCommentUseCase::AddCommentUseCase(Repository *rep, QObject *parent)
    : QObject(parent),
      rep(rep)
{

}

void AddCommentUseCase::run(int mapPointId, QString comment){
    QtConcurrent::run([=]() {
        rep->addComment(mapPointId,comment);
    });
}
