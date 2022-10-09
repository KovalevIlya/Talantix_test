#include "graphicsrectitem.h"
#include "graphicsscene.h"
#include "eventtypechenged.h"

#include <QDebug>
#include <QBrush>

GraphicsRectItem::GraphicsRectItem(const QRectF &rect, const CellNS::Type type, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{
    editType(type);
    setAcceptHoverEvents(true);
}

void GraphicsRectItem::editType(const CellNS::Type type)
{
    QBrush brush;
    QString text;
    switch (type) {
    case CellNS::Type::Open:
        brush = QBrush();
        text = "";
        break;
    case CellNS::Type::Close:
        brush = QBrush(Qt::DiagCrossPattern);
        text = "";
        break;
    case CellNS::Type::Start:
        brush = QBrush();
        text = "A";
        break;
    case CellNS::Type::Finish:
        brush = QBrush();
        text = "B";
        break;
    }

    setBrush(brush);
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

    QGraphicsRectItem::sceneEvent(event);

}

void GraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit qobject_cast<GraphicsScene *>(scene())->clickedItem(boundingRect().topLeft());
//    qDebug() << Q_FUNC_INFO << this->rect();

}

void GraphicsRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug() << Q_FUNC_INFO << this->rect();
}

void GraphicsRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug() << Q_FUNC_INFO << this->rect();
}
