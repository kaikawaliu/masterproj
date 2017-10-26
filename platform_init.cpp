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
    l_LoadTypes.append(aLoadType);
//    QColor tColor(rand()%255,rand()%255,rand()%255);
//    gColors.append(tColor/*QColor(rand()%255,rand()%255,rand()%255)*/);
    QList<int> tColor;
    tColor.append(rand()%255);
    tColor.append(rand()%255);
    tColor.append(rand()%255);
    l_Colors.append(tColor);
}

void Platform::slot_landmark(LandmarkInfo aLandmark)
{
    qDebug()<<"Landmark: "<<"[Id] "<<aLandmark.mId<<
              " \n[LandmarkType] "<<aLandmark.mType<<" [LoadType] "<<aLandmark.mLoadType<<" [Machine] "<<aLandmark.mMachine<<
              " \n[Pos] "<<aLandmark.mPos<<" [Size] "<<aLandmark.mSize;
    QColor spColor = Qt::gray;
    if(aLandmark.mType==LoadPort || aLandmark.mType==ChargeStation)
    {
        QList<int> tColor = l_Colors[l_LoadTypes.indexOf(aLandmark.mLoadType)];
        spColor = QColor(tColor[0], tColor[1], tColor[2]);
    }

    Landmark* tLandmark = new Landmark(aLandmark, spColor);
    Landmarks.insert(aLandmark.mId,tLandmark);
    scene.addItem(Landmarks[aLandmark.mId]);
}

void Platform::slot_link(QPair<int, int> aLink)
{
    qDebug()<<"Link: "<<aLink;
    Link* tLink = new Link(aLink);
    QPair<int,int> tStartPos = Landmarks[aLink.first]->get_pos();
    QPair<int,int> tEndPos = Landmarks[aLink.second]->get_pos();
    QPair<int,int> tStartSize = Landmarks[aLink.first]->get_size();
    QPair<int,int> tEndSize = Landmarks[aLink.first]->get_size();
    tLink->set_pos(tStartPos, tEndPos, tStartSize, tEndSize);
    Links.insert(aLink, tLink);
    scene.addItem(Links[aLink]);
}
