#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QtWidgets>
#include <QList>
#include <QHash>

#include "fileparser.h"
//#include "graphitems.h"
#include "landmark.h"
#include "obstacle.h"
#include "link.h"
#include "diagramview.h"

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
    void slot_hovered(bool aHovered);
    void slot_zoom(bool zoom);
private:
    //funcs
    void setup_sigslot();
    void setup_view();

    void zoomIn();
    void zoomOut();

    //vars
    FP::FileParser file;
    QGraphicsScene scene;
    DiagramView view;
    bool hovered = false;
    int scalelevel = 10;
    int sceneWidth = 16000;
    int sceneHeight = 8000;

    QList<QString> LoadTypes;
    QList<Obstacle*> Obstacles;
    QHash<int,Landmark*> Landmarks;
    QHash<QPair<int,int>,Link*> Links;
    QList<Obstacle> tObstacles;
    QHash<QPair<int,int>,Link> tLinks;
};

#endif // PLATFORM_H
