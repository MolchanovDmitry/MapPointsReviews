#ifndef MAPPOINTUI_H
#define MAPPOINTUI_H

#include <QObject>

// TODO убрать сет
class MapPointUi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong getId READ getId)
    Q_PROPERTY(QString getTitle READ getTitle)
    Q_PROPERTY(QString getDescription READ getDescription)
    Q_PROPERTY(double getLatitude READ getLatitude)
    Q_PROPERTY(double getLongitude READ getLongitude)
    Q_PROPERTY(bool getIsConfirmed READ getIsConfirmed)

   public:
       explicit MapPointUi(QObject* parent = nullptr);
       MapPointUi(qlonglong id, QString title, QString description, double latitude, double longitude, bool isConfirmed, QObject *parent = nullptr);

       qlonglong getId() const;
       QString getTitle() const;
       QString getDescription() const;
       double getLatitude() const;
       double getLongitude() const;
       bool getIsConfirmed() const;

   private:
       qlonglong id;
       QString title;
       QString description;
       double latitude;
       double longitude;
       bool isConfirmed;
};

#endif // MAPPOINTUI_H
