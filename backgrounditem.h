#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include <QObject>
#include <QGraphicsItem>

class BackGroundItem : public QGraphicsItem
{
public:
    BackGroundItem(QPair<int,int> aSize);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QPainterPath shape() const;
signals:
    void mouseHovered(bool aHovered);
    void mouseWheelZoom(bool up);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
private:
    QPair<int,int> aSize;
};

#endif // BACKGROUNDITEM_H
