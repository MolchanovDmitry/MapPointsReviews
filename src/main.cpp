#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtPositioning/QGeoPositionInfo>
#include <auroraapp.h>

#include "gpsinfoprovider/gpsinfoprovider.h"

int main(int argc, char *argv[])
{

    qmlRegisterType<GpsInfoProvider>("ru.auroraos.PointsMapReviews", 1, 0, "GpsInfoProvider");
    qRegisterMetaType<QGeoPositionInfo>("QGeoPositionInfo");

    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("PointsMapReviews"));

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/PointsMapReviews.qml")));
    view->show();

    return application->exec();
}
