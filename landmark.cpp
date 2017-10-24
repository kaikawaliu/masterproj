#include "landmark.h"

#include <QGraphicsScene>
#include <QPainter>

Landmark::Landmark(LandmarkInfo &aInfo)
    : mInfo(aInfo),
      color(Qt::green)
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
                             tSize.first/2,tSize.second/2);
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
