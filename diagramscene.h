#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QGraphicsObject>
#include <QPainter>

#include "datatype.h"

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DiagramScene(QObject *parent=nullptr);

    void init(double aWidth, double aHeight);
    void zoomIn();
    void zoomOut();

signals:
    void mousePressed();
    void mouseWheelZoom(bool up);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);

private:
    double mWidth, mHeight;
};

class HoverLayer : public QGraphicsObject
{
    Q_OBJECT
public:
    HoverLayer(double aWidth, double aHeight);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QPainterPath shape() const;

    void zoomIn();
    void zoomOut();
signals:
    void sendHoverMove(QPointF aScenePos);

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    double mWidth, mHeight;
};

#endif // DIAGRAMSCENE_H
