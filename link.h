#ifndef LINK_H
#define LINK_H

#include <QGraphicsItem>

#include "datatype.h"

class Link : public QGraphicsLineItem
{
public:
    Link(QPair<int,int> aIds);

    QPair<int,int> get_ids(){return mIds;}

    //in initial view
    void set_pos(QPair<int,int> aStartPos, QPair<int,int> aEndPos);

    void zoomIn();
    void zoomOut();
private:
    QPair<int,int> mIds;
    QColor color;
    QPair<int,int> mStartPos, mEndPos;
    QPair<int,int> tStartPos, tEndPos;
};

#endif // LINK_H
