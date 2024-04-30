#ifndef NOTIFICATIONSENDER_H
#define NOTIFICATIONSENDER_H

#include <QObject>

class NotificationSender : public QObject
{
    Q_OBJECT
public:
    explicit NotificationSender(QObject *parent = nullptr);

    void notify(const QString text);

};

#endif // NOTIFICATIONSENDER_H
