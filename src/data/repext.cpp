#include <random>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QDir>
#include "../domain/mappoint.h"
#include "mappointsdbdatasource.h"

int getRandomSign() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);

    return (distribution(gen) == 0) ? -1 : 1;
}

QList<MapPoint*>* getMockData(QString placeName, int generateCount, double placeLatitude, double placeLongitude, double thresholdLatitude, double thresholdLongitude) {
    qDebug()<<"Добавляем "<<generateCount<<" мокнутых точек для "<<placeName;

    auto urls = QList<QString>();
    urls<<"https://samplelib.com/lib/preview/jpeg/sample-city-park-400x300.jpg";
    urls<<"https://samplelib.com/lib/preview/jpeg/sample-birch-400x300.jpg";

    QList<MapPoint*> *result = new QList<MapPoint*>();
    for (int i = 0; i < generateCount; ++i) {
        auto mapPoint = new MapPoint();
        mapPoint->title = QString("%1 %2").arg(placeName).arg(i + 1);
        mapPoint->description = QString("Описание %1 для %2").arg(i + 1).arg(placeName);
        mapPoint->latitude = (placeLatitude + (qrand() % 1000) * thresholdLatitude * getRandomSign()); // 56.8486 + "шум" в пределах 0...0.06
        mapPoint->longitude = (placeLongitude + (qrand() % 1000) * thresholdLongitude * getRandomSign()); // 35.8507 + "шум" в пределах 0...0.13
        mapPoint->isConfirmed = true;
        mapPoint->imageUrls = urls;
        result->append(mapPoint);
    }
    return result;
}

void addMockMapPoints(MapPointsDbDataSource* dataSource) {
    auto tverMapPoints = getMockData("Тверь", 20, 56.8486, 35.8507, 0.00006, 0.00013);
    auto moscowMapPoints = getMockData("Москва", 100, 55.751244, 37.618423, 0.00012, 0.0002);
    dataSource->addRows(tverMapPoints);
    dataSource->addRows(moscowMapPoints);
}
