#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtPositioning/QGeoPositionInfo>
#include <QQmlEngine> // TODO
#include <auroraapp.h>
#include <QDebug>
#include <QQmlContext>
#include <QObject>

#include "presentation/handlers/fetchcommentshandler.h"
#include "presentation/handlers/addmappointhandler.h"
#include "presentation/handlers/addcommenthandler.h"
#include "presentation/mapviewmodel.h"
#include "dependencyprovider.h"

int main(int argc, char *argv[]) {
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("PointsMapReviews"));

    // Инициализация провайдера зависимостей
    auto depProvider = new DependenciesProvider();
    // Используем провайдер зависимостей для получения объектов ViewModel.
    auto mapViewModel = depProvider->provideMapViewModel(application.data());
    auto mapPointsUiModel = mapViewModel->getMapPointsUiModel();
    auto commentsModel = mapViewModel->getReviewsUiModel();

    // Создаем обработчики, которые будут реагировать на действия пользователя в интерфейсе
    auto addCommentHandler = new AddReviewHandler();
    auto addMapPointHandler = new AddMapPointHandler();
    auto fetchCommentsHandler = new FetchCommentsHandler();

    // Устанавливаем связи между обработчиками и ViewModel
    // Это позволяет ViewModel отреагировать на действия пользователя, которые были зафиксированы обработчиками.
    QObject::connect(addMapPointHandler, &AddMapPointHandler::onMapPointPretentderFetched,
                     mapViewModel, &MapViewModel::onMapPointPretentderFetched);
    QObject::connect(addCommentHandler, &AddReviewHandler::onAddReviewRequest,
                     mapViewModel, &MapViewModel::addReview);
    QObject::connect(fetchCommentsHandler, &FetchCommentsHandler::fetchComments,
                     mapViewModel, &MapViewModel::fetchReviews);

    QScopedPointer<QQuickView> view(Aurora::Application::createView());

    // Добавляем в контекст QML наши модели и обработчики, чтобы они были доступны из QML кода.
    view->rootContext()->setContextProperty("commentsModel", commentsModel);
    view->rootContext()->setContextProperty("mapPointsUiModel", mapPointsUiModel);
    view->rootContext()->setContextProperty("addCommentHandler", addCommentHandler);
    view->rootContext()->setContextProperty("addMapPointHandler", addMapPointHandler);
    view->rootContext()->setContextProperty("fetchCommentsHandler", fetchCommentsHandler);

    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/PointsMapReviews.qml")));
    view->show();

    return application->exec();
}
