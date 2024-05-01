#include "reviewststablemodel.h"
#include <QSqlRecord>

ReviewsTableModel::ReviewsTableModel(QObject *parent) : QSqlTableModel(parent) {
    connect(this, &ReviewsTableModel::modelReset, this, &ReviewsTableModel::onDataChanged);
}

void ReviewsTableModel::onDataChanged() {
    auto reviews = new Reviews();
    auto reviewList = new QList<Review>();
    int mapPointId = -1;

    for(int i = 0; i < rowCount(); i++) {
        QSqlRecord record = this->record(i);

        if(mapPointId == -1) {
            mapPointId = record.value("mapPointId").toLongLong();
        }

        Review review;
        review.comment = record.value("comment").toString();
        review.starCount = record.value("starCount").toInt();
        reviewList->append(review);

        qDebug()<<"mapPointId = "<<mapPointId<<" comment = "<<review.comment << " rating: "<<review.starCount;
    }
    reviews->mapPointId = mapPointId;
    reviews->reviews = reviewList;

    emit reviewsFetched(reviews);
}
