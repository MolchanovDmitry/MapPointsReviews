#ifndef ADDMAPPOINTLISTENER_H
#define ADDMAPPOINTLISTENER_H

#include <QObject>
#include <QDebug>

class AddMapPointHandler : public QObject
{
    Q_OBJECT
public:
    explicit AddMapPointHandler(QObject *parent = nullptr);

signals:
    void onMapPointAddRequest1(
            const QString title,
            const QString description,
            const QVariant imageUrls,
            const long latitude,
            const long longitude);
};

#endif // ADDMAPPOINTLISTENER_H
