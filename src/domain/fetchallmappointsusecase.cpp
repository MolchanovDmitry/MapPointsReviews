#include "fetchallmappointsusecase.h"

FetchAllMapPointsUseCase::FetchAllMapPointsUseCase(Repository *repository, QObject *parent) : QObject(parent), repository(repository)
{

}

void FetchAllMapPointsUseCase::run()
{
    repository->fetchAllMapPoints();

}
