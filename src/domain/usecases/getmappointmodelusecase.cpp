#include "getmappointmodelusecase.h"

GetMapPointModelUseCase::GetMapPointModelUseCase(Repository *repository, QObject *parent)
    : QObject(parent),
      repository(repository) {

}

MapPointModel *GetMapPointModelUseCase::run() {
    return repository->getMapPointModel();
}
