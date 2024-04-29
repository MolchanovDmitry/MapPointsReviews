#include "fetchallmappointsusecase.h"
#include <QtConcurrent/QtConcurrent>

FetchAllMapPointsUseCase::FetchAllMapPointsUseCase(Repository *repository, QObject *parent) : QObject(parent), repository(repository)
{

}

void FetchAllMapPointsUseCase::run()
{
    QtConcurrent::run(repository, &Repository::fetchAllMapPoints);
}
