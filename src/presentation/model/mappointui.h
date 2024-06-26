#ifndef MAPPOINTUI_H
#define MAPPOINTUI_H

#include <QObject>

/**
 * UI элемент модели точки на карте для отрисовки
 */
class MapPointUi : public QObject {
    Q_OBJECT
    Q_PROPERTY(qint64 getId READ getId)
    Q_PROPERTY(QString getTitle READ getTitle)
    Q_PROPERTY(QString getDescription READ getDescription)
    Q_PROPERTY(double getLatitude READ getLatitude)
    Q_PROPERTY(double getLongitude READ getLongitude)
    Q_PROPERTY(bool getIsConfirmed READ getIsConfirmed)
    Q_PROPERTY(QList<QString> getImageUrsl READ getImageUrsl)

  public:
    explicit MapPointUi(QObject* parent = nullptr);
    MapPointUi(qint64 id,
               QString title,
               QString description,
               double latitude,
               double longitude,
               bool isConfirmed,
               QList<QString> imageUrls,
               QObject *parent = nullptr);

    /** ID точки на карте. */
    qint64 getId() const;

    /** Название точки на карте. */
    QString getTitle() const;

    /** Описание точки на карте. */
    QString getDescription() const;

    /** Географическая широта точки на карте. */
    double getLatitude() const;

    /** Географическая долгота точки на карте. */
    double getLongitude() const;

    /** Подтверждена ли точка модератором */
    bool getIsConfirmed() const;

    /** Список ссылок изображений точки на карте. */
    QList<QString> getImageUrsl() const;

  private:
    qint64 id;
    QString title;
    QString description;
    double latitude;
    double longitude;
    bool isConfirmed;
    QList<QString> imageUrls;
};

#endif // MAPPOINTUI_H
