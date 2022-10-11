#include "graphicsview.h"

#include <QtMath>
#include <QWheelEvent>
#include <QScrollBar>

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{

}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    const QPointF point = mapToScene(event->pos());

    constexpr double coef = 8.0 * 45.0;
    const double factor = qPow(1.1, event->delta() / coef);
    scale(factor, factor);

    const QPointF delta = mapFromScene(point) - event->pos();
    horizontalScrollBar()->setValue(delta.x() + horizontalScrollBar()->value());
    verticalScrollBar()->setValue(delta.y() + verticalScrollBar()->value());
}
