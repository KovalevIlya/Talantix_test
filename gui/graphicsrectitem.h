#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include "global.h"

#include <QGraphicsRectItem>

/// Отображаемая клетка лабиринта
class GraphicsRectItem : public QGraphicsRectItem
{
public:
    /// Конструктор
    /// \param rect Область клетки
    /// \param type Тип клетки
    /// \param parent Родительский объект
    GraphicsRectItem(const QRectF &rect, const CellNS::Type type, QGraphicsItem *parent = nullptr);

    /// Изменить тип клетки
    /// \param type Тип клетки
    void editType(const CellNS::Type type);

protected:
    /// Обработчик событий сцены
    /// \param event Событие
    bool sceneEvent(QEvent *event) override;
    /// Обработчик событий клика мышью
    /// \param event Событие клика мышью
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    /// Обработчик событий входа курсора в область клетки
    /// \param event событие входа курсора в область клетки
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    /// Обработчик событий выхода курсора в область клетки
    /// \param event событие выхода курсора в область клетки
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // GRAPHICSRECTITEM_H
