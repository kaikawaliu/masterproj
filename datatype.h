#ifndef DATATYPE_H
#define DATATYPE_H

#include <QObject>

#define zoomrate 1.25
#define stepinterval 100

enum LandmarkType{
    LoadPort = 1,
    ChargeStation = 11,
    Waypoint = -1,
};

struct LandmarkInfo{
    int mId;
    LandmarkType mType;
    QString mLoadType = "";
    QString mMachine = "";
    QPair<int,int> mPos;
    QPair<int,int> mSize;
};

struct ObstacleInfo{
    QPair<int,int> mPos;
    QPair<int,int> mSize;
};

struct Task{
    QString mMachine;
    int mSrcNode;
    int mDestNode;
    int mTime;
    int mDontExecuteBefore;
};

#endif // DATATYPE_H
