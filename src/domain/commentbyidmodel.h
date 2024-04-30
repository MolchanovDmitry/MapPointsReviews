#ifndef COMMENTBYIDMODEL_H
#define COMMENTBYIDMODEL_H

#include <QObject>
#include "comments.h"

/**
 * Бизнесовая модель комментариев.
 * В текущей реализации - прокся между слоем источника данных и слоем представления.
 */
class CommentsByIdModel : public QObject {
    Q_OBJECT
  public:
    explicit CommentsByIdModel(QObject *parent = nullptr);

  public slots:
    void updateComments(Comments *comments);

  signals:
    void commentsUpdated(Comments *comments);

};

#endif // COMMENTBYIDMODEL_H
