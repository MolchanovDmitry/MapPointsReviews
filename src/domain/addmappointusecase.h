#ifndef ADDMAPPOINTUSECASE_H
#define ADDMAPPOINTUSECASE_H

#include <QObject>
#include "../data/repository.h"

class AddMapPointUseCase : public QObject
{
    Q_OBJECT
public:
    explicit AddMapPointUseCase(Repository *repository, QObject *parent = nullptr);

    void run(MapPoint mapPoint);

private:
    Repository *repository;

};

#endif // ADDMAPPOINTUSECASE_H
