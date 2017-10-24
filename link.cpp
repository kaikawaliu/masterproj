#include "link.h"

#include <QGraphicsScene>
#include <QPainter>

Link::Link(QPair<int, int> aIds)
    : mIds(aIds),
      color(Qt::gray)
{
    QPen pen = Qt::SolidLine;
    pen.setColor(color);
    pen.setWidth(1);
    setPen(pen);

    this->setZValue(1);
}

void Link::set_pos(QPair<int, int> aStartPos, QPair<int, int> aEndPos)
{
    mStartPos = aStartPos;
    mEndPos = aEndPos;
    tStartPos = mStartPos;
    tEndPos = mEndPos;

    setLine(tStartPos.first,tStartPos.second,tEndPos.first,tEndPos.second);
}

void Link::zoomIn()
{
    tStartPos.first *= zoomrate;
    tStartPos.second *= zoomrate;
    tEndPos.first *= zoomrate;
    tEndPos.second *= zoomrate;

    setLine(tStartPos.first,tStartPos.second,tEndPos.first,tEndPos.second);
}

void Link::zoomOut()
{
    tStartPos.first *= zoomrate;
    tStartPos.second *= zoomrate;
    tEndPos.first *= zoomrate;
    tEndPos.second *= zoomrate;

    setLine(tStartPos.first,tStartPos.second,tEndPos.first,tEndPos.second);
}
