#ifndef DEPENDENCYPROVIDER_H
#define DEPENDENCYPROVIDER_H

#include <QObject>
#include "presentation/mapviewmodel.h"

class DependenciesProvider : public QObject
{
    Q_OBJECT
public:
    explicit DependenciesProvider(QObject *parent = nullptr);

    MapViewModel *provideMapViewModel();

signals:

};

#endif // DEPENDENCYPROVIDER_H
