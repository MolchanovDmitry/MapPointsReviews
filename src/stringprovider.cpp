#include "stringprovider.h"

/**
 * Наполняем в конструкторе мапу энум - строка.
 * Чтобы lupdate не удалил наши строки, обязательно нужно оставлять полный вызов
 * app->translate("Application"...
 *
 * @param app указатель на контекст приложения для получения строк
 */
StringProvider::StringProvider(QGuiApplication *app, QObject *parent)
    : QObject(parent) {
    strHash.insert(PointSentNotification, app->translate("Application", "map_point_added"));
    strHash.insert(AppName, app->translate("Application", "app_name"));
}

QString StringProvider::provide(AppString str) {
    return strHash.value(str);
}
