#ifndef REVIEWSUIMODEL_H
#define REVIEWSUIMODEL_H

#include <QAbstractItemModel>
#include <QQmlListProperty>
#include "../domain/reviews.h"

/**
 * Модель отзывов, на который подписывается UI
 */
class ReviewsUiModel : public QAbstractListModel {
    Q_OBJECT

  public:

    /** Доступные роли полей в модели */
    enum Roles {
        MapPointId,
        StarCount,
        Date,
        Comment
    };

    explicit ReviewsUiModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void clear();

  public slots:
    void updateReviews(Reviews *reviews);

  private:
    Reviews *reviews = new Reviews();
};

#endif // REVIEWSUIMODEL_H
