#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>

/// Сцена
class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param parent Родительский объект
    GraphicsScene(QObject *parent = nullptr);

    /// Сигнал о клике на клетку лабиринта
    /// \param point Индекс клетки
    Q_SIGNAL void clickedItem(const QPointF &point);
    /// Сигнал об установке конца пути
    /// \param point Индекс клетки-конца пути
    Q_SIGNAL void setFinish(const QPointF &point);
    /// Сигнал о сбросе конца пути
    Q_SIGNAL void removeFinish();
};

#endif // GRAPHICSSCENE_H
