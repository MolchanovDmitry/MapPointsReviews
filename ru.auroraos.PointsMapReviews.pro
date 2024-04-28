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
    src/dependencyprovider.h \
    src/domain/fetchallmappointsusecase.h \
    src/domain/getmappointmodelusecase.h \
    src/domain/mappointmodel.h \
    src/presentation/addmappointlistener.h \
    src/presentation/mappointsuimodel.h \
    src/presentation/mappointui.h \
    src/presentation/mapviewmodel.h \

SOURCES += \
    src/data/mappointsdbdatasource.cpp \
    src/data/mappointsqlmodel.cpp \
    src/data/repext.cpp \
    src/data/repository.cpp \
    src/dependencyprovider.cpp \
    src/domain/fetchallmappointsusecase.cpp \
    src/domain/getmappointmodelusecase.cpp \
    src/domain/mappointmodel.cpp \
    src/presentation/addmappointlistener.cpp \
    src/presentation/mappointsuimodel.cpp \
    src/presentation/mappointui.cpp \
    src/presentation/mapviewmodel.cpp \
    src/main.cpp \

DISTFILES += \
    qml/pages/MapPointPage.qml \
    rpm/ru.auroraos.PointsMapReviews.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.PointsMapReviews.ts \
    translations/ru.auroraos.PointsMapReviews-ru.ts \
