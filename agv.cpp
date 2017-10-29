#include "agv.h"

AGV::AGV(int aLandmarkId, QHash<int, Landmark *> *&arLandmarks)
    :
      mrLandmarks(arLandmarks)
{
    mStaticLoc = aLandmarkId;

    mrLandmarks->value(aLandmarkId)->occupied = true;

    color = mrLandmarks->value(mStaticLoc)->get_spcolor();

    mPos = mrLandmarks->value(mStaticLoc)->get_pos();
    mSize = mrLandmarks->value(mStaticLoc)->get_size();

    tPos.first = (double)mPos.first;
    tPos.second = (double)mPos.second;
    tSize.first = (double)mSize.first;
    tSize.second = (double)mSize.second;

    setPos((int)tPos.first,(int)tPos.second);
    setZValue(3);
}

QRectF AGV::boundingRect() const
{
    return QRect(0,0,(int)tSize.first,(int)tSize.second);
}

QPainterPath AGV::shape() const
{
    QPainterPath path;
    path.addRect(0,0,(int)tSize.first,(int)tSize.second);

    return path;
}

void AGV::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(color);
    painter->drawRect((int)tSize.first/4,(int)tSize.second/4,
                      tSize.first/2,tSize.second/2);
}

void AGV::zoomIn()
{
    scalefactor *= zoomrate;

    tPos.first = (double)((double)mPos.first * scalefactor);
    tPos.second = (double)((double)mPos.second * scalefactor);
    tSize.first = (double)((double)mSize.first * scalefactor);
    tSize.second = (double)((double)mSize.second * scalefactor);

    setPos((int)tPos.first,(int)tPos.second);
    this->update();
}

void AGV::zoomOut()
{
    scalefactor /= zoomrate;

    tPos.first = (double)((double)mPos.first * scalefactor);
    tPos.second = (double)((double)mPos.second * scalefactor);
    tSize.first = (double)((double)mSize.first * scalefactor);
    tSize.second = (double)((double)mSize.second * scalefactor);

    setPos((int)tPos.first,(int)tPos.second);
    this->update();
}

void AGV::assign_tasks(Task aTask)
{
    mTasks.append(aTask);
}

void AGV::step()
{
    if(!mTasks.isEmpty())
    {
        int dest_x = mrLandmarks->value(mTasks.first().mDestNode)->get_pos().first;
        int dest_y = mrLandmarks->value(mTasks.first().mDestNode)->get_pos().second;
        int src_x = mrLandmarks->value(mTasks.first().mSrcNode)->get_pos().first;
        int src_y = mrLandmarks->value(mTasks.first().mSrcNode)->get_pos().second;

        int x_diff = dest_x - src_x;
        int y_diff = dest_y - src_y;
        int steps = mTasks.first().mTime/stepinterval;

        double x_shift = x_diff / steps;
        double y_shift = x_diff / steps;
        //before movement
        if(!moving_x && !moving_y)
        {
            if(!mrLandmarks->value(mTasks.first().mDestNode)->occupied)
            {
                curstep++;
                if(abs(x_shift) >= abs(x_diff))
                {
                    mPos.first = dest_x;
                }else
                {
//                    mPos.first += x_shift;
                    mPos.first = src_x + (int)curstep * x_shift;
                    moving_x = true;
                }
                if(abs(y_shift) >= abs(y_diff))
                {
                    mPos.second = dest_y;
                }else
                {
//                    mPos.second += y_shift;
                    mPos.second = src_y + (int)curstep * y_shift;
                    moving_y = true;
                }
                mrLandmarks->value(mTasks.first().mSrcNode)->occupied = false;

                if(!moving_x && !moving_y)
                {
                    mrLandmarks->value(mTasks.first().mDestNode)->occupied = true;
                    mTasks.removeFirst();
                    curstep = 0;
                }

                refresh();
            }
        }else
        {
            curstep++;

            if(moving_x)
            {
                int x_distance = dest_x - mPos.first;

                if(abs(x_shift) >= abs(x_distance) || curstep == steps)
                {
                    mPos.first = dest_x;
                    moving_x = false;
                }else
                {
                    mPos.first = src_x + (int)curstep * x_shift;
                }
            }
            if(moving_y)
            {
                int y_distance = dest_y - mPos.second;

                if(abs(y_shift) >= abs(y_distance) || curstep == steps)
                {
                    mPos.second = dest_y;
                    moving_y = false;
                }else
                {
                    mPos.second = src_y + (int)curstep * y_shift;
                }
            }

            if(!moving_x && !moving_y)
            {
                mrLandmarks->value(mTasks.first().mDestNode)->occupied = true;
                mTasks.removeFirst();
                curstep = 0;
            }

            refresh();
        }
    }
}

void AGV::refresh()
{
    tPos.first = (double)mPos.first * scalefactor;
    tPos.second = (double)mPos.second * scalefactor;

    setPos((int)tPos.first,(int)tPos.second);
    this->update();
}

void AGV::reset()
{
    mPos.first = mrLandmarks->value(mStaticLoc)->get_pos().first;
    mPos.second = mrLandmarks->value(mStaticLoc)->get_pos().second;

    refresh();
}
