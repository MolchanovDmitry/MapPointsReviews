#ifndef FETCHCOMMENTSHANDLER_H
#define FETCHCOMMENTSHANDLER_H

#include <QObject>

/**
 * Обработчик намерения получить отзыв по конкретному pointId
 */
class FetchCommentsHandler : public QObject {
    Q_OBJECT
  public:
    explicit FetchCommentsHandler(QObject *parent = nullptr);

  signals:

    void fetchComments(int pointId);

};

#endif // FETCHCOMMENTSHANDLER_H
