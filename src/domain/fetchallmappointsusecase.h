#ifndef FETCHALLMAPPOINTSUSECASE_H
#define FETCHALLMAPPOINTSUSECASE_H

#include <QObject>
#include "repository.h"

class FetchAllMapPointsUseCase : public QObject {
    Q_OBJECT
  public:
    explicit FetchAllMapPointsUseCase(Repository *repository, QObject *parent = nullptr);

    void run();

  private:
    Repository *repository;

};

#endif // FETCHALLMAPPOINTSUSECASE_H
