#ifndef GETMAPPOINTMODELUSECASE_H
#define GETMAPPOINTMODELUSECASE_H

#include <QObject>
#include "repository.h"

/**
 * Сценарий получения модели всех точек на карте.
 */
class GetMapPointModelUseCase : public QObject {
    Q_OBJECT
  public:
    explicit GetMapPointModelUseCase(Repository *repository, QObject *parent = nullptr);

    MapPointModel *run();

  private:

    Repository *repository;

};

#endif // GETMAPPOINTMODELUSECASE_H
