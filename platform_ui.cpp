#include "platform.h"

#include <iterator>

void Platform::slot_hovered(bool aHovered)
{
    hovered = aHovered;
}

void Platform::slot_zoom(bool zoom)
{
    if(zoom /*&& hovered*/)
    {
        if(0<scalelevel && scalelevel<20)
        {
            zoomIn();

            scalelevel++;
        }
    }else
    {
        if(0<scalelevel && scalelevel<20)
        {
            zoomOut();

            scalelevel--;
        }
    }
}

void Platform::zoomIn()
{
    //Landmark
    for(QHash<int,Landmark*>::iterator i = Landmarks.begin(); i != Landmarks.end(); ++i)
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
    //Machine
    //To be continued...

    sceneWidth*=zoomrate;
    sceneHeight*=zoomrate;
    scene.setSceneRect(0,0,sceneWidth,sceneHeight);
}

void Platform::zoomOut()
{
    //Landmark
    for(QHash<int,Landmark*>::iterator i = Landmarks.begin(); i != Landmarks.end(); ++i)
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
    //Machine
    //To be continued...

    sceneWidth/=zoomrate;
    sceneHeight/=zoomrate;
    scene.setSceneRect(0,0,sceneWidth,sceneHeight);
}
