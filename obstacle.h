#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsItem>

#include "datatype.h"

class Obstacle : public QGraphicsItem
{
public:
    Obstacle(ObstacleInfo &aInfo);

    void zoomIn();
    void zoomOut();

    //built-in virtual funcs
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    ObstacleInfo mInfo;
    QColor color;
    QPair<int,int> tPos;
    QPair<int,int> tSize;
};

#endif // OBSTACLE_H
