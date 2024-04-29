#ifndef COMMENTSTABLEMODEL_H
#define COMMENTSTABLEMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include "../domain/comments.h"

class CommentsTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit CommentsTableModel(QObject *parent = nullptr);

public slots:
    void onDataChanged();

signals:
    void commentsFetched(Comments *comments);

};

#endif // COMMENTSTABLEMODEL_H
