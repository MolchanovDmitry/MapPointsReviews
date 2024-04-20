// SPDX-FileCopyrightText: 2021-2023 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoSatelliteInfoSource>

#include "gpsinfoprovider.h"

GpsInfoProvider::GpsInfoProvider(QObject *parent)
    : QObject(parent),
      m_positionSource(QGeoPositionInfoSource::createDefaultSource(this)),
      m_satelliteSource(QGeoSatelliteInfoSource::createDefaultSource(this)),
      m_active(false)
{
    if (m_positionSource)
        connect(m_positionSource, &QGeoPositionInfoSource::positionUpdated,
                this, &GpsInfoProvider::_updatePositionInfo);

    if (m_satelliteSource) {
        connect(m_satelliteSource, &QGeoSatelliteInfoSource::satellitesInUseUpdated,
                this, &GpsInfoProvider::_updateSatellitesInUse);
        connect(m_satelliteSource, &QGeoSatelliteInfoSource::satellitesInViewUpdated,
                this, &GpsInfoProvider::_updateSatellitesInView);
    }

    if (m_positionSource && m_positionSource->lastKnownPosition().isValid()) {
        m_positionInfo = m_positionSource->lastKnownPosition();
    }
}

bool GpsInfoProvider::active() const
{
    return m_active;
}

QVariantList GpsInfoProvider::satellites() const
{
    QVariantList result;
    QList<SatelliteInfo> satellitesInfo = m_satellites.values();
    for (const auto &satellite : satellitesInfo)
        result << QVariant::fromValue(satellite);

    return result;
}

qint32 GpsInfoProvider::satellitesInViewCount() const
{
    return m_satellites.count();
}

qint32 GpsInfoProvider::satellitesInUseCount() const
{
    auto result = 0;
    QList<SatelliteInfo> satellitesInfo = m_satellites.values();
    for (const auto &satellite : satellitesInfo) {
        if (satellite.inUse)
            result++;
    }

    return result;
}

QGeoCoordinate GpsInfoProvider::coordinate() const
{
    return m_positionInfo.coordinate();
}

QDateTime GpsInfoProvider::timestamp() const
{
    return m_positionInfo.timestamp();
}

qreal GpsInfoProvider::horizontalAccuracy() const
{
    return _geoPositionAttribute(QGeoPositionInfo::HorizontalAccuracy);
}

qreal GpsInfoProvider::verticalAccuracy() const
{
    return _geoPositionAttribute(QGeoPositionInfo::VerticalAccuracy);
}

QString GpsInfoProvider::direction() const
{
    qreal directionDegrees = _geoPositionAttribute(QGeoPositionInfo::Direction);
    if (directionDegrees < 0.0f)
        return QStringLiteral("");
    else if (directionDegrees <= 22.0f || directionDegrees >= 338.0f)
        return tr("North");
    else if (directionDegrees <= 67.0f)
        return tr("Northeast");
    else if (directionDegrees <= 112.0f)
        return tr("East");
    else if (directionDegrees <= 157.0f)
        return tr("Southeast");
    else if (directionDegrees <= 202.0f)
        return tr("South");
    else if (directionDegrees <= 247.0f)
        return tr("Southwest");
    else if (directionDegrees <= 292.0f)
        return tr("West");
    else if (directionDegrees <= 337.0f)
        return tr("Northwest");
    return QStringLiteral("");
}

qreal GpsInfoProvider::speed() const
{
    return _geoPositionAttribute(QGeoPositionInfo::GroundSpeed);
}

bool GpsInfoProvider::gpsEnabled() const
{
    if (!m_positionSource) {
        return false;
    }
    return m_positionSource->supportedPositioningMethods() != QGeoPositionInfoSource::NoPositioningMethods;
}

QString GpsInfoProvider::positioningMethod() const
{
    if (!m_positionSource) {
        return QStringLiteral("");
    }
    switch (m_positionSource->supportedPositioningMethods()) {
    case QGeoPositionInfoSource::NoPositioningMethods:
        return QStringLiteral("");
    case QGeoPositionInfoSource::AllPositioningMethods:
        return tr("Satellite and network");
    case QGeoPositionInfoSource::NonSatellitePositioningMethods:
        return tr("Network");
    case QGeoPositionInfoSource::SatellitePositioningMethods:
        return tr("Satellite");
    default:
        return QStringLiteral("");
    }
}

void GpsInfoProvider::setActive(bool active)
{
    if (m_active == active || !m_positionSource || !m_satelliteSource)
        return;

    if (active) {
        m_positionSource->startUpdates();
        m_satelliteSource->startUpdates();
    } else {
        m_positionSource->stopUpdates();
        m_satelliteSource->stopUpdates();
    }
    m_active = active;
    emit activeChanged();
}

void GpsInfoProvider::_updatePositionInfo(const QGeoPositionInfo &info)
{
    m_positionInfo = info;
    emit positionInfoChanged();
}

void GpsInfoProvider::_updateSatellitesInUse(const QList<QGeoSatelliteInfo> &satellitesInfo)
{
    for (const auto &satellite : satellitesInfo) {
        qint32 satId = satellite.satelliteIdentifier();
        if (m_satellites.contains(satId)) {
            m_satellites[satId].inUse = true;
        } else {
            _appendSatellite(satellite, true);
        }
    }
    emit satellitesChanged();
}

void GpsInfoProvider::_updateSatellitesInView(const QList<QGeoSatelliteInfo> &satellitesInfo)
{
    m_satellites.clear();
    for (const auto &satellite : satellitesInfo)
        _appendSatellite(satellite, false);
    emit satellitesChanged();
}

void GpsInfoProvider::_appendSatellite(const QGeoSatelliteInfo &satellite, bool inUse)
{
    m_satellites[satellite.satelliteIdentifier()] = SatelliteInfo(satellite.attribute(QGeoSatelliteInfo::Azimuth),
                                                                  satellite.attribute(QGeoSatelliteInfo::Elevation),
                                                                  satellite.satelliteIdentifier(),
                                                                  satellite.signalStrength(),
                                                                  inUse);
}

qreal GpsInfoProvider::_geoPositionAttribute(QGeoPositionInfo::Attribute attribute) const
{
    if (!m_positionInfo.hasAttribute(attribute))
        return -1;

    return m_positionInfo.attribute(attribute);
}
