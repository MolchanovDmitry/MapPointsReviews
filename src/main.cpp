#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtPositioning/QGeoPositionInfo>
#include <QQmlEngine> // TODO
#include <auroraapp.h>
#include <QDebug>
#include <QQmlContext>
#include <QObject>

#include "presentation/addmappointhandler.h"
#include "presentation/addcommenthandler.h"
#include "presentation/mapviewmodel.h"
#include "dependencyprovider.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("PointsMapReviews"));

    auto depProvider = new DependenciesProvider();
    auto mapViewModel = depProvider->provideMapViewModel();
    auto mapPointsUiModel = mapViewModel->getMapPointsUiModel();

    auto addMapPointHandler = new AddMapPointHandler();
    auto addCommentHandler = new AddCommentHandler();

    QObject::connect(addMapPointHandler, &AddMapPointHandler::onMapPointPretentderFetched,
                     mapViewModel, &MapViewModel::onMapPointPretentderFetched);
    QObject::connect(addCommentHandler, &AddCommentHandler::addComment,
                     mapViewModel, &MapViewModel::addComment);

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->rootContext()->setContextProperty("mapPointsUiModel", mapPointsUiModel);
    view->rootContext()->setContextProperty("addCommentHandler", addCommentHandler);
    view->rootContext()->setContextProperty("addMapPointHandler", addMapPointHandler);
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/PointsMapReviews.qml")));
    view->show();

    return application->exec();
}
