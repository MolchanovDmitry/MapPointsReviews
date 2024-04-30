#ifndef GETCOMMENTSBYIDUSECASE_H
#define GETCOMMENTSBYIDUSECASE_H

#include <QObject>
#include "repository.h"
#include "commentbyidmodel.h"

class GetCommentsByIdUseCase : public QObject
{
    Q_OBJECT
public:
    explicit GetCommentsByIdUseCase(Repository *repository, QObject *parent = nullptr);

    CommentsByIdModel* run();

private:
    Repository *repository;

};

#endif // GETCOMMENTSBYIDUSECASE_H
