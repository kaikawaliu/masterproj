#include "landmark.h"

#include <QDebug>

#include <QGraphicsScene>
#include <QPainter>

Landmark::Landmark(LandmarkInfo aInfo, QColor aColor)
    : mInfo(aInfo),
      color(Qt::gray),
      spColor(aColor)
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
    return QRect(0,
                 0,
                 (int)tSize.first/*+adjust*/,
                 (int)tSize.second/*+adjust*/);
}

QPainterPath Landmark::shape() const
{
    QPainterPath path;
    path.addRect(0, 0,
                 (int)tSize.first, (int)tSize.second);
    return path;
}

void Landmark::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    if((mInfo.mType==LoadPort && !collected) || mInfo.mType==ChargeStation)
    {
        painter->setPen(spColor);
        painter->setFont(QFont(painter->font().family(),(int)tFontSize));
        painter->drawText(0,0,
                          (int)tSize.first,(int)tSize.second,
                          Qt::AlignCenter,mInfo.mLoadType);
    }else
    {

    }

    painter->setBrush(Qt::transparent);
    painter->setPen(color);

    painter->drawRoundedRect(0,0,
                             (int)tSize.first,(int)tSize.second,
                             (int)tSize.first/2,(int)tSize.second/2);
}

void Landmark::zoomIn()
{
    tPos.first *= zoomrate;
    tPos.second *= zoomrate;
    tSize.first *= zoomrate;
    tSize.second *= zoomrate;
    tFontSize *= 1+(zoomrate-1)/2;

    setPos((int)tPos.first,(int)tPos.second);
    this->update();
}

void Landmark::zoomOut()
{
    tPos.first /= zoomrate;
    tPos.second /= zoomrate;
    tSize.first /= zoomrate;
    tSize.second /= zoomrate;
    tFontSize /= 1+(zoomrate-1)/2;

    setPos((int)tPos.first,(int)tPos.second);
    this->update();
}

void Landmark::collect()
{
    collected=true;
    this->update();
}

void Landmark::reset()
{
    collected=false;
    this->update();
}
