#ifndef GETMAPPOINTMODELUSECASE_H
#define GETMAPPOINTMODELUSECASE_H

#include <QObject>
#include "../data/repository.h"

class GetMapPointModelUseCase : public QObject
{
    Q_OBJECT
public:
    explicit GetMapPointModelUseCase(Repository *repository, QObject *parent = nullptr);

    MapPointModel *run();

private:

    Repository *repository;

};

#endif // GETMAPPOINTMODELUSECASE_H
