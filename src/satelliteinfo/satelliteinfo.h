// SPDX-FileCopyrightText: 2021-2023 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#ifndef SATELLITEINFO_H
#define SATELLITEINFO_H

#include <QtCore/QObject>

class SatelliteInfo
{
    Q_GADGET

    Q_PROPERTY(qreal azimuth MEMBER azimuth)
    Q_PROPERTY(qreal elevation MEMBER elevation)
    Q_PROPERTY(qint32 identifier MEMBER identifier)
    Q_PROPERTY(qint32 signalStrength MEMBER signalStrength)
    Q_PROPERTY(bool inUse MEMBER inUse)

public:
    SatelliteInfo() = default;
    SatelliteInfo(const SatelliteInfo &other);
    SatelliteInfo(qreal azimuth, qreal elevation, qint32 identifier, qint32 signalStrength, bool inUse);
public:

    qreal azimuth;
    qreal elevation;
    qint32 identifier;
    qint32 signalStrength;
    bool inUse;
};

#endif // SATELLITEINFO_H
