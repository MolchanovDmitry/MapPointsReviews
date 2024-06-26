#ifndef MAPPOINTSUIMODEL_H
#define MAPPOINTSUIMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QQmlListProperty>
#include "mappointui.h"

/**
 * UI модуль на который подписывается объект из QML
 */
class MapPointsUiModel : public QAbstractListModel {
    Q_OBJECT
  public:

    /** Роли данной модели */
    enum Roles {
        IdRole,
        TitleRole = Qt::UserRole + 1,
        DescriptionRole,
        LatitudeRole,
        LongitudeRole,
        IsConfirmedRole,
        ImageUrls,
    };


    explicit MapPointsUiModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

  public slots:
    void updateMapPoints(QList<MapPointUi*> uiMapPoints);

  private:
    QList<MapPointUi*> mapPoints = QList<MapPointUi*>();

};

#endif // MAPPOINTSUIMODEL_H
