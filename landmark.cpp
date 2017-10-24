#include "landmark.h"

#include <QGraphicsScene>
#include <QPainter>

Landmark::Landmark(LandmarkInfo &aInfo)
    : mInfo(aInfo),
      color(Qt::gray)
{
    tPos.first = (double)mInfo.mPos.first;
    tPos.second = (double)mInfo.mPos.second;
    tSize.first = (double)mInfo.mSize.first;
    tSize.second = (double)mInfo.mSize.second;

    this->setZValue(2);
    setPos((int)tPos.first,(int)tPos.second);
}

QRectF Landmark::boundingRect() const
{
    qreal adjust = 0.5;
    return QRect(/*-tSize.first/2-adjust*/0,
                 /*-tSize.second/2-adjust*/0,
                 (int)tSize.first+adjust,
                 (int)tSize.second+adjust);
}

QPainterPath Landmark::shape() const
{
    QPainterPath path;
    path.addRect(/*-tSize.first/2*/0, /*-tSize.second/2*/0,
                 (int)tSize.first, (int)tSize.second);
    return path;
}

void Landmark::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(color);
    painter->setBrush(/*color*/Qt::transparent);
    painter->drawRoundedRect(/*-tSize.first/2*/0,/*-tSize.second/2*/0,
                             (int)tSize.first,(int)tSize.second,
                             (int)tSize.first/2,(int)tSize.second/2);
}

void Landmark::zoomIn()
{
    tPos.first *= zoomrate;
    tPos.second *= zoomrate;
    tSize.first *= zoomrate;
    tSize.second *= zoomrate;

    setPos((int)tPos.first,(int)tPos.second);
    this->update();
}

void Landmark::zoomOut()
{
    tPos.first /= zoomrate;
    tPos.second /= zoomrate;
    tSize.first /= zoomrate;
    tSize.second /= zoomrate;

    setPos((int)tPos.first,(int)tPos.second);
    this->update();
}
