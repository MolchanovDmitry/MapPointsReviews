#ifndef COMMENTS_H
#define COMMENTS_H

#include <QString>
#include <QDebug>

/**
 * Бизнесовая структура точки на карте
 */
struct Comments {
    qlonglong mapPointId;
    QList<QString> *comments = new QList<QString>();
};


static void print(QString tag, Comments comments) {
    qDebug()<<tag
            <<" Comments print. mapPointId: "
            <<comments.mapPointId
            <<" comments: "
            <<comments.comments->join(",");
}

#endif // COMMENTS_H
