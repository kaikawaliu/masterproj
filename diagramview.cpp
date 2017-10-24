#include "diagramview.h"

#include <QWheelEvent>
#include <QHoverEvent>

DiagramView::DiagramView()
{

}

void DiagramView::hoverEnterEvent(QHoverEvent *)
{
    emit mouseHovered(true);
}

void DiagramView::hoverLeaveEvent(QHoverEvent *)
{
    emit mouseHovered(false);
}

void DiagramView::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
        emit mouseWheelZoom(true);
    }else
    {
        emit mouseWheelZoom(false);
    }
}
