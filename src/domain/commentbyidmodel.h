#ifndef COMMENTBYIDMODEL_H
#define COMMENTBYIDMODEL_H

#include <QObject>

class CommentByIdModel : public QObject
{
    Q_OBJECT
public:
    explicit CommentByIdModel(QObject *parent = nullptr);

signals:

};

#endif // COMMENTBYIDMODEL_H
