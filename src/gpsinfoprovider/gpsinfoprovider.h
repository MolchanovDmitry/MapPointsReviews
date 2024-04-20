// SPDX-FileCopyrightText: 2021-2023 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#ifndef GPSINFOPROVIDER_H
#define GPSINFOPROVIDER_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtPositioning/QGeoCoordinate>
#include <QtPositioning/QGeoPositionInfo>
#include <QtPositioning/QGeoSatelliteInfo>

#include "../satelliteinfo/satelliteinfo.h"

class QGeoPositionInfoSource;
class QGeoSatelliteInfoSource;

class GpsInfoProvider : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QVariantList satellites READ satellites NOTIFY satellitesChanged)
    Q_PROPERTY(qint32 satellitesInViewCount READ satellitesInViewCount NOTIFY satellitesChanged)
    Q_PROPERTY(qint32 satellitesInUseCount READ satellitesInUseCount NOTIFY satellitesChanged)
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate NOTIFY positionInfoChanged)
    Q_PROPERTY(QDateTime timestamp READ timestamp NOTIFY positionInfoChanged)
    Q_PROPERTY(qreal horizontalAccuracy READ horizontalAccuracy NOTIFY positionInfoChanged)
    Q_PROPERTY(qreal verticalAccuracy READ verticalAccuracy NOTIFY positionInfoChanged)
    Q_PROPERTY(QString direction READ direction NOTIFY positionInfoChanged)
    Q_PROPERTY(qreal speed READ speed NOTIFY positionInfoChanged)
    Q_PROPERTY(bool gpsEnabled READ gpsEnabled NOTIFY positionInfoChanged)
    Q_PROPERTY(QString positioningMethod READ positioningMethod NOTIFY positionInfoChanged)

public:
    explicit GpsInfoProvider(QObject *parent = nullptr);

    bool active() const;
    QVariantList satellites() const;
    qint32 satellitesInViewCount() const;
    qint32 satellitesInUseCount() const;
    QGeoCoordinate coordinate() const;
    QDateTime timestamp() const;
    qreal horizontalAccuracy() const;
    qreal verticalAccuracy() const;
    QString direction() const;
    qreal speed() const;
    bool gpsEnabled() const;
    QString positioningMethod() const;

    void setActive(bool active);

signals:
    void activeChanged();
    void positionInfoChanged();
    void satellitesChanged();

private slots:
    void _updatePositionInfo(const QGeoPositionInfo &info);
    void _updateSatellitesInUse(const QList<QGeoSatelliteInfo> &satellitesInfo);
    void _updateSatellitesInView(const QList<QGeoSatelliteInfo> &satellitesInfo);

private:
    void _appendSatellite(const QGeoSatelliteInfo &info, bool inUse);
    qreal _geoPositionAttribute(QGeoPositionInfo::Attribute attribute) const;

private:
    QGeoPositionInfoSource *m_positionSource { nullptr };
    QGeoSatelliteInfoSource *m_satelliteSource { nullptr };
    QGeoPositionInfo m_positionInfo {  };
    QMap<qint32, SatelliteInfo> m_satellites {  };
    bool m_active { false };
};

#endif // GPSINFOPROVIDER_H
