#include "obstacle.h"

#include <QGraphicsScene>
#include <QPainter>

Obstacle::Obstacle(ObstacleInfo &aInfo)
    : mInfo(aInfo),
      color(Qt::gray)
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
                             tSize.first/2,tSize.second/2);
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
