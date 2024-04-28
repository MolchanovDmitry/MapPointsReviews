#include "addmappointusecase.h"

AddMapPointUseCase::AddMapPointUseCase(Repository *repository, QObject *parent)
    : QObject(parent),
      repository(repository)
{

}

void AddMapPointUseCase::run(MapPoint mapPoint)
{
    repository->addMapPoint(mapPoint);

}
