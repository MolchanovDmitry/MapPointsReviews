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
    src/data/notificationsender.h \
    src/data/repositoryimpl.h \
    src/data/datasource/reviewsdatasource.h \
    src/data/datasource/mappointsdbdatasource.h \
    src/data/model/mappointsqlmodel.h \
    src/data/model/reviewststablemodel.h \
    src/domain/usecases/addreviewusecase.h \
    src/domain/usecases/fetchreviewsbymapidusecase.h \
    src/domain/usecases/getreviewsbyidusecase.h \
    src/domain/usecases/addmappointusecase.h \
    src/domain/usecases/fetchallmappointsusecase.h \
    src/domain/usecases/getmappointmodelusecase.h \
    src/domain/repository.h \
    src/domain/model/reviews.h \
    src/domain/model/mappoint.h \
    src/domain/model/mappointmodel.h \
    src/domain/model/reviewsbyidmodel.h \
    src/presentation/handlers/addcommenthandler.h \
    src/presentation/handlers/addmappointhandler.h \
    src/presentation/handlers/fetchcommentshandler.h \
    src/presentation/model/mappointsuimodel.h \
    src/presentation/model/mappointui.h \
    src/presentation/model/reviewsuimodel.h \
    src/presentation/mapviewmodel.h \
    src/stringprovider.h \
    src/dependencyprovider.h

SOURCES += \
    src/data/notificationsender.cpp \
    src/data/repext.cpp \
    src/data/repositoryimpl.cpp \
    src/data/datasource/reviewsdatasource.cpp \
    src/data/datasource/mappointsdbdatasource.cpp \
    src/data/model/mappointsqlmodel.cpp \
    src/data/model/reviewststablemodel.cpp \
    src/domain/usecases/addmappointusecase.cpp \
    src/domain/usecases/addreviewusecase.cpp \
    src/domain/usecases/fetchallmappointsusecase.cpp \
    src/domain/usecases/fetchreviewsbymapidusecase.cpp \
    src/domain/usecases/getmappointmodelusecase.cpp \
    src/domain/usecases/getreviewsbyidusecase.cpp \
    src/domain/model/mappointmodel.cpp \
    src/domain/model/reviewsbyidmodel.cpp \
    src/presentation/handlers/addcommenthandler.cpp \
    src/presentation/handlers/addmappointhandler.cpp \
    src/presentation/handlers/fetchcommentshandler.cpp \
    src/presentation/model/mappointsuimodel.cpp \
    src/presentation/model/mappointui.cpp \
    src/presentation/model/reviewsuimodel.cpp \
    src/presentation/mapviewmodel.cpp \
    src/main.cpp \
    src/stringprovider.cpp \
    src/dependencyprovider.cpp



DISTFILES += \
    qml/pages/MapPointPage.qml \
    rpm/ru.auroraos.PointsMapReviews.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.PointsMapReviews.ts \
    translations/ru.auroraos.PointsMapReviews-ru.ts \
