#ifndef COMMENTS_H
#define COMMENTS_H

#include <QString>
#include <QDebug>

/**
 * Бизнесовая структура точки на карте
 */
struct Comments
{
    qlonglong mapPointId;
    QList<QString> *comments = new QList<QString>();
};

#endif // COMMENTS_H
