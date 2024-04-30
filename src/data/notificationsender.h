#ifndef NOTIFICATIONSENDER_H
#define NOTIFICATIONSENDER_H

#include <QObject>
#include "../stringprovider.h"

/**
 * Менеджер уведомлений.
 */
class NotificationSender : public QObject {
    Q_OBJECT
  public:
    explicit NotificationSender(StringProvider *stringProvider, QObject *parent = nullptr);

    /** Отправить уведомление с текстом [text] */
    void notify(const QString text);

  private:
    StringProvider *stringProvider;
};

#endif // NOTIFICATIONSENDER_H
