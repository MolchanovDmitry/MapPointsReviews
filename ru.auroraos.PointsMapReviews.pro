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
    src/data/commentsdatasource.h \
    src/data/commentstablemodel.h \
    src/data/mappointsdbdatasource.h \
    src/data/mappointsqlmodel.h \
    src/data/repository.h \
    src/dependencyprovider.h \
    src/domain/addcommentusecase.h \
    src/domain/commentbyidmodel.h \
    src/domain/comments.h \
    src/domain/fetchcommentbymapidusecase.h \
    src/domain/getcommentsbyidusecase.h \
    src/domain/mappoint.h \
    src/domain/addmappointusecase.h \
    src/domain/fetchallmappointsusecase.h \
    src/domain/getmappointmodelusecase.h \
    src/domain/mappointmodel.h \
    src/presentation/addcommenthandler.h \
    src/presentation/addmappointhandler.h \
    src/presentation/commentsuimodel.h \
    src/presentation/fetchcommentshandler.h \
    src/presentation/mappointsuimodel.h \
    src/presentation/mappointui.h \
    src/presentation/mapviewmodel.h \

SOURCES += \
    src/data/commentsdatasource.cpp \
    src/data/commentstablemodel.cpp \
    src/data/mappointsdbdatasource.cpp \
    src/data/mappointsqlmodel.cpp \
    src/data/repext.cpp \
    src/data/repository.cpp \
    src/dependencyprovider.cpp \
    src/domain/addcommentusecase.cpp \
    src/domain/addmappointusecase.cpp \
    src/domain/commentbyidmodel.cpp \
    src/domain/fetchallmappointsusecase.cpp \
    src/domain/fetchcommentbymapidusecase.cpp \
    src/domain/getcommentsbyidusecase.cpp \
    src/domain/getmappointmodelusecase.cpp \
    src/domain/mappointmodel.cpp \
    src/presentation/addcommenthandler.cpp \
    src/presentation/addmappointhandler.cpp \
    src/presentation/commentsuimodel.cpp \
    src/presentation/fetchcommentshandler.cpp \
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
