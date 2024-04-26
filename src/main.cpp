#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtPositioning/QGeoPositionInfo>
#include <auroraapp.h>
#include <QDebug>

#include "presentation/addmappointlistener.h"
#include "gpsinfoprovider/gpsinfoprovider.h"
#include "data/repository.h"

int main(int argc, char *argv[])
{

    qmlRegisterType<GpsInfoProvider>("ru.auroraos.PointsMapReviews", 1, 0, "GpsInfoProvider");
    qRegisterMetaType<QGeoPositionInfo>("QGeoPositionInfo");

    qmlRegisterType<AddMapPointListener>("com.current.project", 1, 0, "AddMapPointListener");

    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("PointsMapReviews"));

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/PointsMapReviews.qml")));
    view->show();

    Repository *repository = new Repository();
    QList<MapPoint> mapPoints = repository->getAllMapPoints();

    foreach(MapPoint mapPoint, mapPoints){
        qDebug()<<"результат: "<<mapPoint.title;
    }

    return application->exec();
}
