#include "obstacle.h"

#include <QGraphicsScene>
#include <QPainter>

Obstacle::Obstacle(ObstacleInfo &aInfo)
    : mInfo(aInfo),
      color(Qt::gray)
{
    tPos.first = (double)mInfo.mPos.first;
    tPos.second = (double)mInfo.mPos.second;
    tSize.first = (double)mInfo.mSize.first;
    tSize.second = (double)mInfo.mSize.second;

    this->setZValue(1);
    setPos((int)tPos.first,(int)tPos.second);
}

QRectF Obstacle::boundingRect() const
{
    qreal adjust = 0.5;
    return QRect(/*-tSize.first/2*/0-adjust,
                 /*-tSize.second/2*/0-adjust,
                 (int)tSize.first+adjust,
                 (int)tSize.second+adjust);
}

QPainterPath Obstacle::shape() const
{
    QPainterPath path;
    path.addRect(/*-tSize.first/2*/0, /*-tSize.second/2*/0,
                 (int)tSize.first, (int)tSize.second);
    return path;
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawRect(/*-tSize.first/2*/0,/*-tSize.second/2*/0,
                             (int)tSize.first,(int)tSize.second);
}

void Obstacle::zoomIn()
{
    tPos.first *= zoomrate;
    tPos.second *= zoomrate;
    tSize.first *= zoomrate;
    tSize.second *= zoomrate;

    setPos((int)tPos.first,(int)tPos.second);
    this->update();
}

void Obstacle::zoomOut()
{
    tPos.first /= zoomrate;
    tPos.second /= zoomrate;
    tSize.first /= zoomrate;
    tSize.second /= zoomrate;

    setPos((int)tPos.first,(int)tPos.second);
    this->update();
}
