#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include "global.h"

#include <QGraphicsRectItem>

class GraphicsRectItem : public QGraphicsRectItem
{
public:
    GraphicsRectItem(const QRectF &rect, const CellNS::Type type, QGraphicsItem *parent = nullptr);

    void editType(const CellNS::Type type);

protected:
    bool sceneEvent(QEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // GRAPHICSRECTITEM_H
