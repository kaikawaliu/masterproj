#include "graphitems.h"

#include <QGraphicsScene>
#include <QPainter>

//MACHINE ***********************************
Machine::Machine()
    : color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    this->setZValue(2);
}

QRectF Machine::boundingRect() const
{
    qreal adjust = 0.5;
    return QRect(-20-adjust, -20-adjust, 40+adjust, 40+adjust);
}

QPainterPath Machine::shape() const
{
    QPainterPath path;
    path.addRect(-20, -20, 40, 40);
    return path;
}

void Machine::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(color);
    painter->drawRect(-20,-20,40,40);
}



//*******************************************************************
//LANDMARK **********************************************************
//*******************************************************************
Landmark::Landmark(LandmarkInfo &aInfo)
    : color(Qt::green),
      mInfo(aInfo)
{
    tPos = mInfo.mPos;
    tSize = mInfo.mSize;
    this->setZValue(2);
    setPos(tPos.first,tPos.second);
}

QRectF Landmark::boundingRect() const
{
    qreal adjust = 0.5;
    return QRect(-tSize.first/2-adjust,
                 -tSize.second/2-adjust,
                 tSize.first+adjust,
                 tSize.second+adjust);
}

QPainterPath Landmark::shape() const
{
    QPainterPath path;
    path.addRect(-tSize.first/2, -tSize.second/2,
                 tSize.first, tSize.second);
    return path;
}

void Landmark::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(color);
    painter->drawRoundedRect(-tSize.first/2,-tSize.second/2,
                             tSize.first,tSize.second,
                             tSize.first/2,tSize.second/2,);
}

void Landmark::zoomIn()
{
    tPos.first *= zoomrate;
    tPos.second *= zoomrate;
    tSize.first *= zoomrate;
    tSize.second *= zoomrate;

    setPos(tPos.first,tPos.second);
    this->update();
}

void Landmark::zoomOut()
{
    tPos.first /= zoomrate;
    tPos.second /= zoomrate;
    tSize.first /= zoomrate;
    tSize.second /= zoomrate;

    setPos(tPos.first,tPos.second);
    this->update();
}



//*******************************************************************
//OBSTACLE **********************************************************
//*******************************************************************
Obstacle::Obstacle(ObstacleInfo &aInfo)
    : color(Qt::gray),
      mInfo(aInfo)
{
    tPos = mInfo.mPos;
    tSize = mInfo.mSize;
    this->setZValue(1);
    setPos(tPos.first,tPos.second);
}

QRectF Obstacle::boundingRect() const
{
    qreal adjust = 0.5;
    return QRect(-tSize.first/2-adjust,
                 -tSize.second/2-adjust,
                 tSize.first+adjust,
                 tSize.second+adjust);
}

QPainterPath Obstacle::shape() const
{
    QPainterPath path;
    path.addRect(-tSize.first/2, -tSize.second/2,
                 tSize.first, tSize.second);
    return path;
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(color);
    painter->drawRoundedRect(-tSize.first/2,-tSize.second/2,
                             tSize.first,tSize.second,
                             tSize.first/2,tSize.second/2,);
}

void Obstacle::zoomIn()
{
    tPos.first *= zoomrate;
    tPos.second *= zoomrate;
    tSize.first *= zoomrate;
    tSize.second *= zoomrate;

    setPos(tPos.first,tPos.second);
    this->update();
}

void Obstacle::zoomOut()
{
    tPos.first /= zoomrate;
    tPos.second /= zoomrate;
    tSize.first /= zoomrate;
    tSize.second /= zoomrate;

    setPos(tPos.first,tPos.second);
    this->update();
}

//*******************************************************************
//LINK **************************************************************
//*******************************************************************
Link::Link(QPair<int, int> aIds)
    : color(Qt::gray),
      mIds(aIds)
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
