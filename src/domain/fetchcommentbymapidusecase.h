#ifndef FETCHCOMMENTBYMAPIDUSECASE_H
#define FETCHCOMMENTBYMAPIDUSECASE_H

#include <QObject>
#include "repository.h"

class FetchCommentByMapIdUseCase : public QObject {
    Q_OBJECT
  public:
    explicit FetchCommentByMapIdUseCase(Repository *rep, QObject *parent = nullptr);

    void run(int mapPointId);

  private:
    Repository *rep;
};

#endif // FETCHCOMMENTBYMAPIDUSECASE_H
