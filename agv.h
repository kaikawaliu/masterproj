#ifndef AGV_H
#define AGV_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

#include "datatype.h"
#include "landmark.h"

class AGV : public QGraphicsItem
{
public:
    AGV(int aLandmarkId,
        QHash<int, Landmark *> *&arLandmarks);

    void assign_tasks(Task aTask);

    void zoomIn();
    void zoomOut();

    QRectF boundingRect() const override;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void step();
    void reset();

private:
    void refresh();

    double scalefactor = 1;
    int curstep = 0;
//    bool moving = false;
    bool moving_x = false;
    bool moving_y = false;
    QHash<int,Landmark*>* mrLandmarks;
    QColor color;
    int mStaticLoc;
    QPair<int,int> mPos, mSize;
    QPair<double,double> tPos, tSize;
    QList<Task> mTasks;
};

#endif // AGV_H
