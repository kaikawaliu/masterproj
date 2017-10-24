#include "platform.h"

Platform::Platform(QObject *parent) : QObject(parent)
{   
    setup_sigslot();
    setup_view();
}

void Platform::setup_sigslot()
{
    qRegisterMetaType<ObstacleInfo>("ObstacleInfo");
    qRegisterMetaType<LandmarkInfo>("LandmarkInfo");
    qRegisterMetaType<QPair<int,int>>("QPair<int,int>");
    connect(&file,SIGNAL(sig_machine(QString)),this,SLOT(slot_machine(QString)));
    connect(&file,SIGNAL(sig_loadtype(QString)),this,SLOT(slot_loadtype(QString)));
    connect(&file,SIGNAL(sig_obstacle(ObstacleInfo)),this,SLOT(slot_obstacle(ObstacleInfo)));
    connect(&file,SIGNAL(sig_landmark(LandmarkInfo)),this,SLOT(slot_landmark(LandmarkInfo)));
    connect(&file,SIGNAL(sig_link(QPair<int,int>)),this,SLOT(slot_link(QPair<int,int>)));

    connect(&view,SIGNAL(mouseHovered(bool)),this,SLOT(slot_hovered(bool)));
    connect(&view,SIGNAL(mouseWheelZoom(bool)),this,SLOT(slot_zoom(bool)));
}

void Platform::setup_view()
{
    scene.setSceneRect(0,0,sceneWidth,sceneHeight);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    //setup elements
    if(!file.load_file())
        return;
    view.setScene(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Factory 8"));
    view.resize(1080,720);
    view.show();
}

void Platform::slot_machine(QString aMachine)
{
    qDebug()<<"Machine: "<<aMachine;
}

void Platform::slot_obstacle(ObstacleInfo aObstacle)
{
    qDebug()<<"Obstacle: "<<"[Pos] "<<aObstacle.mPos<<" [Size] "<<aObstacle.mSize;
    Obstacle* tObstacle = new Obstacle(aObstacle);
    Obstacles.append(tObstacle);
    scene.addItem(tObstacle);
}

void Platform::slot_loadtype(QString aLoadType)
{
    qDebug()<<"LoadType: "<<aLoadType;
    LoadTypes.append(aLoadType);
}

void Platform::slot_landmark(LandmarkInfo aLandmark)
{
    qDebug()<<"Landmark: "<<"[Id] "<<aLandmark.mId<<
              " \n[LandmarkType] "<<aLandmark.mType<<" [LoadType] "<<aLandmark.mLoadType<<" [Machine] "<<aLandmark.mMachine<<
              " \n[Pos] "<<aLandmark.mPos<<" [Size] "<<aLandmark.mSize;
    Landmark* tLandmark = new Landmark(aLandmark);
    Landmarks.insert(aLandmark.mId,tLandmark);
    scene.addItem(Landmarks[aLandmark.mId]);
}

void Platform::slot_link(QPair<int, int> aLink)
{
    qDebug()<<"Link: "<<aLink;
    Link* tLink = new Link(aLink);
    QPair<int,int> tStartPos = Landmarks[aLink.first]->get_pos();
    QPair<int,int> tEndPos = Landmarks[aLink.second]->get_pos();
    tLink->set_pos(tStartPos, tEndPos);
    Links.insert(aLink, tLink);
    scene.addItem(Links[aLink]);
}
