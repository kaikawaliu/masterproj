#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QtWidgets>
#include <QList>
#include <QHash>

#include "fileparser.h"
#include "landmark.h"
#include "obstacle.h"
#include "link.h"
#include "diagramscene.h"
#include "agv.h"

class Platform : public QObject
{
    Q_OBJECT
public:
    explicit Platform(QObject *parent = nullptr);


signals:

public slots:
    void slot_machine(QString aMachine);
    void slot_loadtype(QString aLoadType);
    void slot_obstacle(ObstacleInfo aObstacle);
    void slot_landmark(LandmarkInfo aLandmark);
    void slot_link(QPair<int,int> aLink);
    void slot_mousepressed();
    void slot_zoom(bool zoom);
    void slot_hover(QPointF aScenePos);
private:
    //funcs
    void setup_sigslot();
    void setup_view();
    void setup_agv();

    void zoomIn();
    void zoomOut();

    //vars
    FP::FileParser file;
    double sceneWidth = 16000;
    double sceneHeight = 8000;
    QGraphicsView view;
    DiagramScene scene;
    HoverLayer* hoverlayer;
    int scalelevel = 10;
    QPointF mousePos = QPointF(sceneWidth/2,sceneHeight/2);

    QList<Obstacle*> Obstacles;
    QHash<int,Landmark*>* Landmarks;
    QHash<QPair<int,int>,Link*> Links;
    QHash<int,AGV*> AGVs;

    QList<QString> l_LoadTypes;
    QList<QList<int>> l_Colors;
};

#endif // PLATFORM_H
