#ifndef ADDCOMMENTUSECASE_H
#define ADDCOMMENTUSECASE_H

#include <QObject>
#include "../data/repository.h"

class AddCommentUseCase : public QObject
{
    Q_OBJECT
public:
    explicit AddCommentUseCase(Repository *rep, QObject *parent = nullptr);

    void run(int mapPointId, QString comment);

private:
    Repository *rep;

};

#endif // ADDCOMMENTUSECASE_H
