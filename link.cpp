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

void Link::set_pos(QPair<int, int> aStartPos,
                   QPair<int, int> aEndPos,
                   QPair<int, int> aStartSize,
                   QPair<int, int> aEndSize)
{
    mStartPos = aStartPos;
    mEndPos = aEndPos;
    mStartSize = aStartSize;
    mEndSize = aEndSize;

    tStartPos.first = (double)mStartPos.first;
    tStartPos.second = (double)mStartPos.second;
    tEndPos.first = (double)mEndPos.first;
    tEndPos.second = (double)mEndPos.second;

    tStartSize.first = (double)mStartSize.first;
    tStartSize.second = (double)mStartSize.second;
    tEndSize.first = (double)mEndSize.first;
    tEndSize.second = (double)mEndSize.second;

    setLine((int)tStartPos.first + (int)tStartSize.first/2,
            (int)tStartPos.second + (int)tStartSize.second/2,
            (int)tEndPos.first + (int)tEndSize.first/2,
            (int)tEndPos.second + (int)tEndSize.second/2);
}

void Link::zoomIn()
{
    tStartPos.first *= zoomrate;
    tStartPos.second *= zoomrate;
    tStartSize.first *= zoomrate;
    tStartSize.second *= zoomrate;
    tEndPos.first *= zoomrate;
    tEndPos.second *= zoomrate;
    tEndSize.first *= zoomrate;
    tEndSize.second *= zoomrate;

    setLine((int)tStartPos.first + (int)tStartSize.first/2,
            (int)tStartPos.second + (int)tStartSize.second/2,
            (int)tEndPos.first + (int)tEndSize.first/2,
            (int)tEndPos.second + (int)tEndSize.second/2);
}

void Link::zoomOut()
{
    tStartPos.first /= zoomrate;
    tStartPos.second /= zoomrate;
    tStartSize.first /= zoomrate;
    tStartSize.second /= zoomrate;
    tEndPos.first /= zoomrate;
    tEndPos.second /= zoomrate;
    tEndSize.first /= zoomrate;
    tEndSize.second /= zoomrate;

    setLine((int)tStartPos.first + (int)tStartSize.first/2,
            (int)tStartPos.second + (int)tStartSize.second/2,
            (int)tEndPos.first + (int)tEndSize.first/2,
            (int)tEndPos.second + (int)tEndSize.second/2);
}
