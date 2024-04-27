#include "dependencyprovider.h"

DependenciesProvider::DependenciesProvider(QObject *parent) : QObject(parent)
{

}

MapViewModel *DependenciesProvider::provideMapViewModel()
{
    Repository *repository = new Repository();
    GetMapPointModelUseCase *getMapPointModelUseCase = new GetMapPointModelUseCase(repository);
    FetchAllMapPointsUseCase *fetchAllMapPointsUseCase = new FetchAllMapPointsUseCase(repository);
    return new MapViewModel(fetchAllMapPointsUseCase, getMapPointModelUseCase);
}
