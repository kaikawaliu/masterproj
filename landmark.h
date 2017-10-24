#ifndef LANDMARK_H
#define LANDMARK_H

#include <QGraphicsItem>

#include "datatype.h"

class Landmark : public QGraphicsItem
{
public:
    Landmark(LandmarkInfo &aInfo);

    int get_id(){return mInfo.mId;}
    LandmarkType get_type(){return mInfo.mType;}
    QString get_loadtype(){return mInfo.mLoadType;}
    QString get_machine(){return mInfo.mMachine;}
    QPair<int,int> get_pos(){return mInfo.mPos;}

    void zoomIn();
    void zoomOut();

    //built-in virtual funcs
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    LandmarkInfo mInfo;
    QColor color;
    QPair<int,int> tPos;
    QPair<int,int> tSize;
};


#endif // LANDMARK_H
