#ifndef DEPENDENCYPROVIDER_H
#define DEPENDENCYPROVIDER_H

#include <QObject>
#include <QtGui/QGuiApplication>
#include "presentation/mapviewmodel.h"
#include "data/commentsdatasource.h"
#include "data/repositoryimpl.h"

class DependenciesProvider : public QObject {
    Q_OBJECT
  public:
    explicit DependenciesProvider(QObject *parent = nullptr);

    MapViewModel *provideMapViewModel(QGuiApplication *app);

  signals:

};

#endif // DEPENDENCYPROVIDER_H
