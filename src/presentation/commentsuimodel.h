#ifndef COMMENTSUIMODEL_H
#define COMMENTSUIMODEL_H

#include <QAbstractItemModel>
#include <QQmlListProperty>
#include "../domain/comments.h"

/**
 * UI модуль комментариев, на который подписывается объект из QML
 */
class CommentsUiModel : public QAbstractListModel {
    Q_OBJECT

  public:

    /** Доступные роли полей в модели */
    enum Roles {
        MapPointId,
        Comment
    };

    explicit CommentsUiModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void clear();

  public slots:
    void updateComments(Comments *comments);

  private:
    Comments *comments = new Comments();
};

#endif // COMMENTSUIMODEL_H
