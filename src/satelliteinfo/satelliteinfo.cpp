// SPDX-FileCopyrightText: 2021-2023 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include "satelliteinfo.h"

SatelliteInfo::SatelliteInfo(const SatelliteInfo &other)
    : azimuth(other.azimuth), elevation(other.elevation), identifier(other.identifier),
      signalStrength(other.signalStrength), inUse(other.inUse)
{
}

SatelliteInfo::SatelliteInfo(qreal azimuth, qreal elevation, qint32 identifier, qint32 signalStrength, bool inUse)
    : azimuth(azimuth), elevation(elevation), identifier(identifier),
      signalStrength(signalStrength), inUse(inUse)
{
}
