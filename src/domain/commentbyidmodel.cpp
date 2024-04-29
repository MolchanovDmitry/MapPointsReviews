#include "commentbyidmodel.h"

CommentsByIdModel::CommentsByIdModel(QObject *parent) : QObject(parent)
{

}

void CommentsByIdModel::updateComments(Comments *comments){
    emit commentsUpdated(comments);
}
