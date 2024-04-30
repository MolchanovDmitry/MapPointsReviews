#ifndef ADDCOMMENTHANDLER_H
#define ADDCOMMENTHANDLER_H

#include <QObject>

/**
 * Обработчик намерения добавить комментарий к точке
 */
class AddCommentHandler : public QObject {
    Q_OBJECT
  public:
    explicit AddCommentHandler(QObject *parent = nullptr);

  signals:
    void addComment(int mapPointId, QString comment);

};

#endif // ADDCOMMENTHANDLER_H
