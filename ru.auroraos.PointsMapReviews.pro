TARGET = ru.auroraos.PointsMapReviews

QT += network \
    sensors \
    positioning \
    location \
    sql

CONFIG += \
    auroraapp \
    auroraapp_i18n \

PKGCONFIG += \

HEADERS += \
    src/data/mappointsdbdatasource.h \
    src/data/mappointsqlmodel.h \
    src/data/repository.h \
    src/domain/mappoint.h \
    src/gpsinfoprovider/gpsinfoprovider.h \
    src/presentation/addmappointlistener.h \
    src/satelliteinfo/satelliteinfo.h \

SOURCES += \
    src/data/mappointsdbdatasource.cpp \
    src/data/mappointsqlmodel.cpp \
    src/data/repository.cpp \
    src/gpsinfoprovider/gpsinfoprovider.cpp \
    src/presentation/addmappointlistener.cpp \
    src/satelliteinfo/satelliteinfo.cpp \
    src/main.cpp \

DISTFILES += \
    rpm/ru.auroraos.PointsMapReviews.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.PointsMapReviews.ts \
    translations/ru.auroraos.PointsMapReviews-ru.ts \
