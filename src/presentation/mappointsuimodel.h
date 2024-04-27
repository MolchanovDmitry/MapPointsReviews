#ifndef MAPPOINTSUIMODEL_H
#define MAPPOINTSUIMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QQmlListProperty>
#include "../domain/mappoint.h"
#include "mappointui.h"

class MapPointsUiModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum Roles {
        IdRole,
        TitleRole = Qt::UserRole + 1,
        DescriptionRole,
        LatitudeRole,
        LongitudeRole
    };


    explicit MapPointsUiModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

public slots: //TODO
    void updateMapPoints(QList<MapPoint*> mapPoints);

signals://TODO
    // void onMapPointsUpdated(QString text);


private:
    QList<MapPointUi*> mapPoints = QList<MapPointUi*>();

};

#endif // MAPPOINTSUIMODEL_H
