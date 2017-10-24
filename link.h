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
    void set_pos(QPair<int,int> aStartPos,
                 QPair<int,int> aEndPos,
                 QPair<int,int> aStartSize,
                 QPair<int,int> aEndSize);

    void zoomIn();
    void zoomOut();
private:
    QPair<int,int> mIds;
    QColor color;
    QPair<int,int> mStartPos, mEndPos, mStartSize, mEndSize;
    QPair<double,double> tStartPos, tEndPos, tStartSize, tEndSize;
};

#endif // LINK_H
