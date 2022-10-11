#include "graphicsrectitem.h"
#include "graphicsscene.h"
#include "eventtypechenged.h"

#include <QDebug>
#include <QBrush>

GraphicsRectItem::GraphicsRectItem(const QRectF &rect, const CellNS::Type type,
                                   QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{
    editType(type);
    setAcceptHoverEvents(true);
}

void GraphicsRectItem::editType(const CellNS::Type type)
{
    QString text;
    switch (type) {
    case CellNS::Type::Open:
        setBrush(QBrush());
        text = "";
        break;
    case CellNS::Type::Close:
        setBrush(QBrush(Qt::DiagCrossPattern));
        text = "";
        break;
    case CellNS::Type::Start:
        text = "A";
        break;
    case CellNS::Type::Finish:
        text = "B";
        break;
    }

    for (auto item : childItems()) {
        if (auto textItem = static_cast<QGraphicsSimpleTextItem *>(item)) {
            textItem->setText(text);
            auto rect = boundingRect();
            auto textRect = textItem->boundingRect();
            textItem->setX(rect.x() + rect.width() / 2 - textRect.width() / 2);
            textItem->setY(rect.y() + rect.height() / 2 - textRect.height() / 2);
        }
    }
    update();
}

bool GraphicsRectItem::sceneEvent(QEvent *event)
{
    if (event->type() == EventTypeChenged::type)
        editType(static_cast<EventTypeChenged *>(event)->typeCell());

    return QGraphicsRectItem::sceneEvent(event);
}

void GraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit qobject_cast<GraphicsScene *>(scene())->clickedItem(boundingRect().topLeft());
}

void GraphicsRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    emit qobject_cast<GraphicsScene *>(scene())->setFinish(boundingRect().topLeft());
}

void GraphicsRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    emit qobject_cast<GraphicsScene *>(scene())->removeFinish();
}
