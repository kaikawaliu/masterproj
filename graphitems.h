#ifndef GRAPHITEMS_H
#define GRAPHITEMS_H

#include <QObject>
#include <QGraphicsItem>

#include "datatype.h"

#define zoomrate 1.25

class Machine : public QGraphicsItem
{
public:
    Machine();


public:
    //built-in virtual funcs
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
private:
    QColor color;
};



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

class Link : public QGraphicsLineItem
{
public:
    Link(QPair<int,int> aIds);

    QPair<int,int> get_ids(){return mIds;}

    //in initial view
    void set_pos(QPair<int,int> aStartPos, QPair<int,int> aEndPos);

    void zoomIn();
    void zoomOut();
private:
    QPair<int,int> mIds;
    QColor color;
    QPair<int,int> mStartPos, mEndPos;
    QPair<int,int> tStartPos, tEndPos;
};

#endif // GRAPHITEMS_H
