#ifndef DEPENDENCYPROVIDER_H
#define DEPENDENCYPROVIDER_H

#include <QObject>
#include <QtGui/QGuiApplication>
#include "presentation/mapviewmodel.h"
#include "data/datasource/reviewsdatasource.h"
#include "data/repositoryimpl.h"

/**
 * Провайдер зависимостей для скрытия деталей инициализации
 */
class DependenciesProvider : public QObject {
    Q_OBJECT
  public:
    explicit DependenciesProvider(QObject *parent = nullptr);

    MapViewModel *provideMapViewModel(QGuiApplication *app);

  signals:

};

#endif // DEPENDENCYPROVIDER_H
