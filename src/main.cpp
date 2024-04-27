#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtPositioning/QGeoPositionInfo>
#include <QQmlEngine> // TODO
#include <auroraapp.h>
#include <QDebug>

#include "presentation/addmappointlistener.h"
#include "gpsinfoprovider/gpsinfoprovider.h"
#include "presentation/mapviewmodel.h"
#include "dependencyprovider.h"

int main(int argc, char *argv[])
{

    qmlRegisterType<GpsInfoProvider>("ru.auroraos.PointsMapReviews", 1, 0, "GpsInfoProvider");
    qRegisterMetaType<QGeoPositionInfo>("QGeoPositionInfo");
    qmlRegisterType<AddMapPointListener>("com.current.project", 1, 0, "AddMapPointListener");

    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("PointsMapReviews"));

    auto depProvider = DependenciesProvider();
    auto mapViewModel = depProvider.provideMapViewModel();
    auto mapPointsUiModel = mapViewModel->getMapPointsUiModel();

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->rootContext()->setContextProperty("mapPointsUiModel", QVariant::fromValue(mapPointsUiModel));
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/PointsMapReviews.qml")));
    view->show();

    return application->exec();
}
