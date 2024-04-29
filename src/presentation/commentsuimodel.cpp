#include "commentsuimodel.h"

CommentsUiModel::CommentsUiModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int CommentsUiModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()){
        return 0;
    }
    return comments->comments->count();
}

QVariant CommentsUiModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    QList<QString*> *commentList = comments->comments;
    QString *comment = commentList->at(index.row());
    switch (role) {
    case MapPointId:
        return QVariant(comments->mapPointId);
    case Comment:
        //return QVariant(*comment);
        return QVariant("asdasdasd");
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CommentsUiModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[MapPointId] = "mapPointId";
    roles[Comment] = "comment";
    return roles;
}

void CommentsUiModel::updateComments(Comments *comments)
{
    auto commentList = comments->comments;
    qDebug() << "CommentsUiModel::updateComments count: " << commentList->count();

    if(commentList->count()>0){
        beginRemoveRows(QModelIndex(), 0, commentList->count() - 1);
        this->comments->mapPointId = -1;
        this->comments->comments->clear();
        endRemoveRows();
    }

    if(commentList->count()>0){
        beginInsertRows(QModelIndex(), 0, commentList->count() - 1);
        this->comments->mapPointId = comments->mapPointId;
        this->comments->comments->append(*comments->comments);
        endInsertRows();
    }
    qDebug() << "CommentsUiModel::updateComments finish";
}
