#include "mappointsqlmodel.h"

MapPointSqlModel::MapPointSqlModel(QObject *parent): QSqlQueryModel(parent) {
    //QObject::connect(this, &QSqlQueryModel::dataChanged, this, &MapPointSqlModel::onDataChanged);
}
