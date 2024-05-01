#include "reviewsbyidmodel.h"

ReviewsByIdModel::ReviewsByIdModel(QObject *parent) : QObject(parent) {

}

void ReviewsByIdModel::updateReviews(Reviews *reviews) {
    print("CommentsByIdModel", *reviews);
    emit reviewsUpdated(reviews);
}
