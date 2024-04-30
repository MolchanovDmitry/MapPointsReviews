#include "commentstablemodel.h"
#include <QSqlRecord>

CommentsTableModel::CommentsTableModel(QObject *parent) : QSqlTableModel(parent) {
    connect(this, &CommentsTableModel::modelReset, this, &CommentsTableModel::onDataChanged);
}

void CommentsTableModel::onDataChanged() {
    auto comments = new Comments();
    auto commentList = new QList<QString>();
    int mapPointId = -1;

    for(int i = 0; i < rowCount(); i++) {
        QSqlRecord record = this->record(i);

        if(mapPointId == -1) {
            mapPointId = record.value("mapPointId").toLongLong();
        }
        QString comment = record.value("comment").toString();
        commentList->append(comment);
        qDebug()<<"mapPointId = "<<mapPointId<<" comment = "<<comment;
    }
    comments->mapPointId = mapPointId;
    comments->comments = commentList;

    emit commentsFetched(comments);
}
