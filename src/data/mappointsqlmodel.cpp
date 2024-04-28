#include "mappointsqlmodel.h"

MapPointSqlModel::MapPointSqlModel(QObject *parent): QSqlQueryModel(parent) {
    //connect(this, &QSqlQueryModel::dataChanged, this, &MapPointSqlModel::onDataChanged); dataChanged не вызывается
    connect(this, &QAbstractItemModel::modelReset, this, &MapPointSqlModel::onDataChanged);
}
