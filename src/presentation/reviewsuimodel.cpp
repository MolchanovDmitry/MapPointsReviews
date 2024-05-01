#include "reviewsuimodel.h"

ReviewsUiModel::ReviewsUiModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int ReviewsUiModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return reviews->reviews->count();
}

QVariant ReviewsUiModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    QList<Review> *reviewList = reviews->reviews;
    Review review = reviewList->at(index.row());
    switch (role) {
    case MapPointId:
        return QVariant(reviews->mapPointId);
    case StarCount:
        return QVariant(review.starCount);
    case Comment:
        return QVariant(review.comment);
    case Date:
        return QVariant(review.date);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ReviewsUiModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[MapPointId] = "mapPointId";
    roles[StarCount] = "starCount";
    roles[Comment] = "comment";
    roles[Date] = "date";
    return roles;
}

void ReviewsUiModel::updateReviews(Reviews *reviews) {
    auto reviewList = reviews->reviews;
    auto last = reviewList->count() > 0 ? reviewList->count() - 1 : 0;

    qDebug() << "count: " << reviewList->count() << " last: "<<last;

    clear();

    if(reviewList->count() > 0) {
        beginInsertRows(QModelIndex(), 0, last);
        this->reviews->mapPointId = reviews->mapPointId;
        this->reviews->reviews->append(*reviews->reviews);
        endInsertRows();
    }
}

void ReviewsUiModel::clear() {
    auto reviewList = reviews->reviews;
    auto last = reviewList->count() > 0 ? reviewList->count() - 1 : 0;
    beginRemoveRows(QModelIndex(), 0, last);
    this->reviews->mapPointId = -1;
    this->reviews->reviews->clear();
    endRemoveRows();
}
