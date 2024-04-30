#include "notificationsender.h"
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusInterface>
#include <QVariantMap>
#include <QException>
#include <QDebug>
#include <QDBusMessage>


NotificationSender::NotificationSender(QObject *parent) : QObject(parent)
{

}

void NotificationSender::notify(const QString text)
{
        QDBusInterface interface("org.freedesktop.Notifications",
                                 "/org/freedesktop/Notifications",
                                 "org.freedesktop.Notifications",
                                 QDBusConnection::sessionBus());

        if (!interface.isValid()) {
            return;
        }

        QDBusMessage reply = interface.call("Notify",
                                            QString(),
                                            uint(0),
                                            QString(),
                                            QString(),
                                            text,
                                            QStringList(),
                                            QVariantMap(),
                                            int(-1));
        if (reply.type() == QDBusMessage::ErrorMessage) {
            qDebug() << "Error:" << reply.errorMessage();
        } else {
            qDebug() << "Notification sent successfully";
        }
}
