#ifndef MAPVIEWMODEL_H
#define MAPVIEWMODEL_H

#include <QObject>
#include "mappointsuimodel.h"
#include "../domain/fetchallmappointsusecase.h"
#include "../domain/getmappointmodelusecase.h"

class MapViewModel : public QObject
{
    Q_OBJECT
public:

    explicit MapViewModel(
            FetchAllMapPointsUseCase *fetchAppMapPointsUseCase,
            GetMapPointModelUseCase *getMapPointModelUseCase,
            QObject *parent = nullptr
            );

    MapPointsUiModel* getMapPointsUiModel();

    void onMapPointAddRequest(
            const QString title,
            const QString description,
            const QVariant imageUrls,
            const long latitude,
            const long longitude){
        qDebug()<<"title 1 "<<title;
        qDebug()<<"description 1 "<<description;
        qDebug()<<"imageUrls 1 "<<imageUrls.toStringList();

        for(const QString& str : imageUrls.toStringList()) {
            qDebug() << str;
        }
    }

public slots:
    void handleButtonClicked(QString str){
        qDebug()<<"поймади "<<str;
    }



signals:

private:
    MapPointsUiModel *mapPointsUiModel = new MapPointsUiModel();

    void mapMapPointAndUpdate(QList<MapPoint*> mapPoints);
};

#endif // MAPVIEWMODEL_H
