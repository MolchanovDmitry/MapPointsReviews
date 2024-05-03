#include "addmappointusecase.h"
#include <QtConcurrent/QtConcurrent>

AddMapPointUseCase::AddMapPointUseCase(Repository *repository, QObject *parent)
    : QObject(parent),
      repository(repository) {

}

void AddMapPointUseCase::run(MapPoint mapPoint) {
    QtConcurrent::run([=]() {
        repository->addMapPoint(mapPoint);
    });

}
