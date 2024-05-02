#include "addcommenthandler.h"

AddReviewHandler::AddReviewHandler(QObject *parent) : QObject(parent) {

}

void AddReviewHandler::addReview(int mapPointId, int starCount, QString comment) {
    Review review;
    review.comment = comment;
    review.starCount = starCount;
    review.date = QDateTime::currentMSecsSinceEpoch();

    emit onAddReviewRequest(mapPointId, review);
}
