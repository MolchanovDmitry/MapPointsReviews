TARGET = ru.auroraos.PointsMapReviews

QT += network sensors positioning location

CONFIG += \
    auroraapp \
    auroraapp_i18n \

PKGCONFIG += \

HEADERS += \
    src/gpsinfoprovider/gpsinfoprovider.h \
    src/satelliteinfo/satelliteinfo.h \

SOURCES += \
    src/gpsinfoprovider/gpsinfoprovider.cpp \
    src/satelliteinfo/satelliteinfo.cpp \
    src/main.cpp \

DISTFILES += \
    rpm/ru.auroraos.PointsMapReviews.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.PointsMapReviews.ts \
    translations/ru.auroraos.PointsMapReviews-ru.ts \
