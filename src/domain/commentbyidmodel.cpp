#include "commentbyidmodel.h"

CommentsByIdModel::CommentsByIdModel(QObject *parent) : QObject(parent)
{

}

void CommentsByIdModel::updateComments(Comments *comments){
    print("CommentsByIdModel", *comments);
    emit commentsUpdated(comments);
}
