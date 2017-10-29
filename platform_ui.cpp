#include "platform.h"

#include <iterator>

void Platform::slot_zoom(bool zoom)
{
    if(zoom /*&& hovered*/)
    {
        if(0<=scalelevel && scalelevel<200)
        {
            zoomIn();

            scalelevel++;
        }
    }else
    {
        if(0<scalelevel && scalelevel<=200)
        {
            zoomOut();

            scalelevel--;
        }
    }
}

void Platform::zoomIn()
{
    double rateX = (double)mousePos.x()/sceneWidth;
    double rateY = (double)mousePos.y()/sceneHeight;

    //scene & hoverlayer
    scene.zoomIn();
    hoverlayer->zoomIn();
    //Landmark
    for(QHash<int,Landmark*>::iterator i = Landmarks->begin(); i != Landmarks->end(); ++i)
    {
        i.value()->zoomIn();
    }
    //Obstacle
    for(int i = 0; i < Obstacles.size(); ++i)
    {
        Obstacles[i]->zoomIn();
    }
    //Link
    for(QHash<QPair<int,int>,Link*>::iterator i = Links.begin(); i != Links.end(); ++i)
    {
        i.value()->zoomIn();
    }
    //AGV
    for(QHash<int,AGV*>::iterator i = AGVs.begin(); i != AGVs.end(); ++i)
    {
        i.value()->zoomIn();
    }

    sceneWidth*=zoomrate;
    sceneHeight*=zoomrate;

    view.centerOn(sceneWidth*rateX,sceneHeight*rateY);
}

void Platform::zoomOut()
{
    double rateX = (double)mousePos.x()/sceneWidth;
    double rateY = (double)mousePos.y()/sceneHeight;

    //scene & hoverlayer
    scene.zoomOut();
    hoverlayer->zoomOut();
    //Landmark
    for(QHash<int,Landmark*>::iterator i = Landmarks->begin(); i != Landmarks->end(); ++i)
    {
        i.value()->zoomOut();
    }
    //Obstacle
    for(int i = 0; i < Obstacles.size(); ++i)
    {
        Obstacles[i]->zoomOut();
    }
    //Link
    for(QHash<QPair<int,int>,Link*>::iterator i = Links.begin(); i != Links.end(); ++i)
    {
        i.value()->zoomOut();
    }
    //AGV
    for(QHash<int,AGV*>::iterator i = AGVs.begin(); i != AGVs.end(); ++i)
    {
        i.value()->zoomOut();
    }

    sceneWidth/=zoomrate;
    sceneHeight/=zoomrate;

    view.centerOn(sceneWidth*rateX,sceneHeight*rateY);
}

void Platform::slot_hover(QPointF aScenePos)
{
    mousePos = aScenePos;
}

void Platform::slot_mousepressed()
{

}

