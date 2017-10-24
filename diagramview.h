#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H

#include <QGraphicsView>
#include <QGraphicsSceneEvent>

class DiagramView : public QGraphicsView
{
    Q_OBJECT
public:
    DiagramView();

signals:
    void mouseHovered(bool aHovered);
    void mouseWheelZoom(bool up);

protected:
    void hoverEnterEvent(QHoverEvent *);
    void hoverLeaveEvent(QHoverEvent *);
    void wheelEvent(QWheelEvent *event);
};

#endif // DIAGRAMVIEW_H
