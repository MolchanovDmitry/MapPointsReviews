#ifndef ADDMAPPOINTLISTENER_H
#define ADDMAPPOINTLISTENER_H

#include <QObject>
#include <QDebug>

class AddMapPointListener : public QObject
{
    Q_OBJECT
public:
    explicit AddMapPointListener(QObject *parent = nullptr);

public slots:

    void onMapPointAddRequest(
            const QString title,
            const QString description,
            const QVariant imageUrls,
            const long latitude,
            const long longitude){
        qDebug()<<"title "<<title;
        qDebug()<<"description "<<description;
        qDebug()<<"imageUrls "<<imageUrls.toStringList();

        for(const QString& str : imageUrls.toStringList()) {
                    qDebug() << str;
                }
    }
};

#endif // ADDMAPPOINTLISTENER_H
