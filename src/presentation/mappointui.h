#ifndef MAPPOINTUI_H
#define MAPPOINTUI_H

#include <QObject>

class MapPointUi : public QObject
{
    Q_OBJECT
       Q_PROPERTY(QString getTitle READ getTitle WRITE setTitle NOTIFY titleChanged)
       Q_PROPERTY(QString getDescription READ getDescription WRITE setDescription NOTIFY descriptionChanged)
       Q_PROPERTY(double getLatitude READ getLatitude WRITE setLatitude NOTIFY latitudeChanged)
       Q_PROPERTY(double getLongitude READ getLongitude WRITE setLongitude NOTIFY longitudeChanged)

   public:
       explicit MapPointUi(QObject* parent = nullptr);
       MapPointUi(QString title, QString description, double latitude, double longitude, QObject *parent = nullptr);

       QString getTitle() const;
       QString getDescription() const;
       double getLatitude() const;
       double getLongitude() const;

       void setTitle(const QString &title);
       void setDescription(const QString &description);
       void setLatitude(double latitude);
       void setLongitude(double longitude);

   signals:
       void titleChanged();
       void descriptionChanged();
       void latitudeChanged();
       void longitudeChanged();

   private:
       QString title;
       QString description;
       double latitude;
       double longitude;
};

#endif // MAPPOINTUI_H
