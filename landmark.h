#ifndef LANDMARK_H
#define LANDMARK_H

#include <QGraphicsItem>

#include "datatype.h"

class Landmark : public QGraphicsItem
{
public:
    Landmark(LandmarkInfo aInfo, QColor aColor);

    int get_id(){return mInfo.mId;}
    LandmarkType get_type(){return mInfo.mType;}
    QString get_loadtype(){return mInfo.mLoadType;}
    QString get_machine(){return mInfo.mMachine;}
    QPair<int,int> get_pos(){return mInfo.mPos;}
    QPair<int,int> get_size(){return mInfo.mSize;}
    QColor get_spcolor(){return spColor;}

    bool occupied = false;

    void zoomIn();
    void zoomOut();

    //for Landmark_Loadport
    void collect();
    void reset();

    //built-in virtual funcs
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    QObject *mParent;
    LandmarkInfo mInfo;
    QColor color, spColor;
    QPair<double,double> tPos;
    QPair<double,double> tSize;
    bool collected;
    double tFontSize = 20;
};


#endif // LANDMARK_H
