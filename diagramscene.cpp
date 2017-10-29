#include "diagramscene.h"

#include <QDebug>

DiagramScene::DiagramScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

void DiagramScene::init(double aWidth, double aHeight)
{
    mWidth=aWidth;
    mHeight=aHeight;

    this->setSceneRect(0,0,(int)mWidth,(int)mHeight);
    this->setItemIndexMethod(QGraphicsScene::NoIndex);
}

void DiagramScene::zoomIn()
{
    mWidth *= zoomrate;
    mHeight *= zoomrate;

    this->setSceneRect(0,0,(int)mWidth,(int)mWidth);
}

void DiagramScene::zoomOut()
{
    mWidth /= zoomrate;
    mHeight /= zoomrate;

    this->setSceneRect(0,0,(int)mWidth,(int)mWidth);
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    emit mousePressed();
}

void DiagramScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(event->delta() > 0)
    {
        emit mouseWheelZoom(true);
    }else
    {
        emit mouseWheelZoom(false);
    }
}

//*******************************************************************************

HoverLayer::HoverLayer(double aWidth, double aHeight)
    : mWidth(aWidth),mHeight(aHeight)
{
    setPos(0,0);
    setZValue(0);
    setAcceptHoverEvents(true);
}

QRectF HoverLayer::boundingRect() const
{
    return QRectF(0,0,(int)mWidth,(int)mHeight);
}

void HoverLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(0,0,(int)mWidth,(int)mHeight);
}

QPainterPath HoverLayer::shape() const
{
    QPainterPath path;
    path.addRect(0,0,(int)mWidth,(int)mHeight);
    return path;
}

void HoverLayer::zoomIn()
{
    mWidth *= zoomrate;
    mHeight *= zoomrate;

    this->update();
}

void HoverLayer::zoomOut()
{
    mWidth /= zoomrate;
    mHeight /= zoomrate;

    this->update();
}

void HoverLayer::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF tHoverPos = event->scenePos();
    emit sendHoverMove(tHoverPos);
}
