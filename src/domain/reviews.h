#ifndef REVIEWS_H
#define REVIEWS_H

#include <QString>
#include <QDebug>

/**
 * Бизнесовая структура отзыва.
 */
struct Review {
    QString comment;
    int starCount;
};

/**
 * Бизнесовая структура отзывов к точке.
 */
struct Reviews {

    /** Идентификатор точки на карте. */
    qlonglong mapPointId;

    /** Комментарии к точке */
    QList<Review> *reviews = new QList<Review>();
};


/** Для отладки */
static void print(QString tag, Reviews reviews) {
    qDebug()<<tag
            <<" Review mapPointId: "
            <<reviews.mapPointId;
//    foreach(Review review, reviews) {
//        qDebug()<<tag
//                <<" review: "
//                <<review.comment
//                <<" starCount: "
//                <<review.starCount;
//    }

}

#endif // REVIEWS_H
