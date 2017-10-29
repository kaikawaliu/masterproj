#include "platform.h"

Platform::Platform(QObject *parent) : QObject(parent)
{   
    setup_sigslot();
    setup_view();
//    setup_agv();
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

    connect(&scene,SIGNAL(mouseWheelZoom(bool)),this,SLOT(slot_zoom(bool)));
    connect(&scene,SIGNAL(mousePressed()),this,SLOT(slot_mousepressed()));
}

void Platform::setup_view()
{
    scene.init(sceneWidth,sceneHeight);
    hoverlayer = new HoverLayer(sceneWidth,sceneHeight);
    connect(hoverlayer,SIGNAL(sendHoverMove(QPointF)),this,SLOT(slot_hover(QPointF)));
    scene.addItem(hoverlayer);
    Landmarks = new QHash<int,Landmark*>;
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

void Platform::setup_agv()
{
    for(QHash<int,Landmark*>::iterator i = Landmarks->begin(); i != Landmarks->end(); ++i)
    {
        qDebug()<<"landmark"<<i.value()->get_id()<<i.value()->get_type();
        if(i.value()->get_type()==LoadPort)
        {
            AGV* tAGV = new AGV(i.value()->get_id(),Landmarks);
            AGVs.insert(i.value()->get_id(),tAGV);
            scene.addItem(AGVs.value(i.value()->get_id()));
        }
    }
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
    Landmarks->insert(aLandmark.mId,tLandmark);
    scene.addItem(Landmarks->value(aLandmark.mId));

    if(aLandmark.mType==ChargeStation)
    {
        AGV* tAGV = new AGV(aLandmark.mId,Landmarks);
        AGVs.insert(aLandmark.mId,tAGV);
        scene.addItem(tAGV);
    }
}

void Platform::slot_link(QPair<int, int> aLink)
{
    qDebug()<<"Link: "<<aLink;
    Link* tLink = new Link(aLink);
    QPair<int,int> tStartPos = Landmarks->value(aLink.first)->get_pos();
    QPair<int,int> tEndPos = Landmarks->value(aLink.second)->get_pos();
    QPair<int,int> tStartSize = Landmarks->value(aLink.first)->get_size();
    QPair<int,int> tEndSize = Landmarks->value(aLink.first)->get_size();
    tLink->set_pos(tStartPos, tEndPos, tStartSize, tEndSize);
    Links.insert(aLink, tLink);
    scene.addItem(Links[aLink]);
}
