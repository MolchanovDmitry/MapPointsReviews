#include "dependencyprovider.h"

DependenciesProvider::DependenciesProvider(QObject *parent) : QObject(parent)
{

}

MapViewModel *DependenciesProvider::provideMapViewModel()
{
    auto repository = new Repository();
    auto addMapPointUseCase = new AddMapPointUseCase(repository);
    auto getMapPointModelUseCase = new GetMapPointModelUseCase(repository);
    auto fetchAllMapPointsUseCase = new FetchAllMapPointsUseCase(repository);
    return new MapViewModel(fetchAllMapPointsUseCase, getMapPointModelUseCase, addMapPointUseCase);
}
