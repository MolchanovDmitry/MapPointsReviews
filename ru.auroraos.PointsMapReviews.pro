TARGET = ru.auroraos.PointsMapReviews

QT += network \
    sensors \
    positioning \
    location \
    sql \
    dbus

CONFIG += \
    auroraapp \
    auroraapp_i18n \

PKGCONFIG += \

HEADERS += \
    src/data/mappointsdbdatasource.h \
    src/data/mappointsqlmodel.h \
    src/data/notificationsender.h \
    src/data/repositoryimpl.h \
    src/data/reviewsdatasource.h \
    src/data/reviewststablemodel.h \
    src/dependencyprovider.h \
    src/domain/addreviewusecase.h \
    src/domain/fetchreviewsbymapidusecase.h \
    src/domain/getreviewsbyidusecase.h \
    src/domain/mappoint.h \
    src/domain/addmappointusecase.h \
    src/domain/fetchallmappointsusecase.h \
    src/domain/getmappointmodelusecase.h \
    src/domain/mappointmodel.h \
    src/domain/repository.h \
    src/domain/reviews.h \
    src/domain/reviewsbyidmodel.h \
    src/presentation/handlers/addcommenthandler.h \
    src/presentation/handlers/addmappointhandler.h \
    src/presentation/handlers/fetchcommentshandler.h \
    src/presentation/model/mappointsuimodel.h \
    src/presentation/model/mappointui.h \
    src/presentation/model/reviewsuimodel.h \
    src/presentation/mapviewmodel.h \
    src/stringprovider.h

SOURCES += \
    src/data/mappointsdbdatasource.cpp \
    src/data/mappointsqlmodel.cpp \
    src/data/notificationsender.cpp \
    src/data/repext.cpp \
    src/data/repositoryimpl.cpp \
    src/data/reviewsdatasource.cpp \
    src/data/reviewststablemodel.cpp \
    src/dependencyprovider.cpp \
    src/domain/addmappointusecase.cpp \
    src/domain/addreviewusecase.cpp \
    src/domain/fetchallmappointsusecase.cpp \
    src/domain/fetchreviewsbymapidusecase.cpp \
    src/domain/getmappointmodelusecase.cpp \
    src/domain/getreviewsbyidusecase.cpp \
    src/domain/mappointmodel.cpp \
    src/domain/reviewsbyidmodel.cpp \
    src/presentation/handlers/addcommenthandler.cpp \
    src/presentation/handlers/addmappointhandler.cpp \
    src/presentation/handlers/fetchcommentshandler.cpp \
    src/presentation/model/mappointsuimodel.cpp \
    src/presentation/model/mappointui.cpp \
    src/presentation/model/reviewsuimodel.cpp \
    src/presentation/mapviewmodel.cpp \
    src/stringprovider.cpp\
    src/main.cpp \



DISTFILES += \
    qml/pages/MapPointPage.qml \
    rpm/ru.auroraos.PointsMapReviews.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.PointsMapReviews.ts \
    translations/ru.auroraos.PointsMapReviews-ru.ts \
