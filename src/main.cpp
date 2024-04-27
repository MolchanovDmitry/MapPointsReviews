#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtPositioning/QGeoPositionInfo>
#include <QQmlEngine> // TODO
#include <auroraapp.h>
#include <QDebug>

#include "presentation/addmappointlistener.h"
#include "gpsinfoprovider/gpsinfoprovider.h"
#include "presentation/mapviewmodel.h"
#include "domain/mappoint.h" //TODO
#include "presentation/mappointsuimodel.h" //TODO
#include "domain/getmappointmodelusecase.h"
#include "domain/fetchallmappointsusecase.h"

int main(int argc, char *argv[])
{

    qmlRegisterType<GpsInfoProvider>("ru.auroraos.PointsMapReviews", 1, 0, "GpsInfoProvider");
    qRegisterMetaType<QGeoPositionInfo>("QGeoPositionInfo");

    qmlRegisterType<AddMapPointListener>("com.current.project", 1, 0, "AddMapPointListener");
    //qmlRegisterType<MapPoint>("com.current.project", 1, 0, "MapPoint");
    //qmlRegisterType<MapPointsUiModel>("com.current.project", 1, 0, "MapPointsUiModel");

    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("PointsMapReviews"));

    Repository *repository = new Repository();
    GetMapPointModelUseCase *getMapPointModelUseCase = new GetMapPointModelUseCase(repository);
    FetchAllMapPointsUseCase *fetchAllMapPointsUseCase = new FetchAllMapPointsUseCase(repository);
    MapViewModel mapViewModel(fetchAllMapPointsUseCase, getMapPointModelUseCase);
    MapPointsUiModel *mapPointsUiModel = mapViewModel.getMapPointsUiModel();

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->rootContext()->setContextProperty("mapPointsUiModel", QVariant::fromValue(mapPointsUiModel));
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/PointsMapReviews.qml")));
    view->show();




//    auto model = repository->getAllMapPoints();

//    auto result = model->getMapPoints();

//    //QList<MapPoint> mapPoints = repository->getAllMapPoints();

//    qDebug()<<"количество результатов: "<<result.count();
//    foreach(MapPoint mapPoint, result){
//        qDebug()<<"результат: "<<mapPoint.title;
//    }

//    qDebug()<<"количество результатов: "<<mapPointsUiModel.getMapPoints().count();
//    foreach(MapPoint mapPoint, mapPointsUiModel.getMapPoints()){
//        qDebug()<<"результат: "<<mapPoint.title;
//    }

    return application->exec();
}
