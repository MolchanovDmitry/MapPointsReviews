#ifndef STRINGPROVIDER_H
#define STRINGPROVIDER_H

#include <QObject>
#include <QtGui/QGuiApplication>

/**
 * Перечисление возможных строк, которые могут понадобиться вне UI слоя.
 */
enum AppString {
    PointSentNotification,
    AppName,
};

/**
 * Провайдер строк для не UI слоя. Например, в менеджере уведомлений.
 */
class StringProvider : public QObject {
    Q_OBJECT
  public:
    explicit StringProvider(QGuiApplication *app, QObject *parent = nullptr);

    /** Предоставить строку по ее ключу. */
    QString provide(AppString str);

  private:
    QHash<AppString, QString> strHash;
};

#endif // STRINGPROVIDER_H
