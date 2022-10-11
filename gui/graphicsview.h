#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

/// Виджет отображения сцены
class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    /// Коструктор
    /// \param scene Сцена
    /// \param parent Родительский объект
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

protected:
    /// Обработчик событий колеса мыши
    /// \param event Событие колеса мыши
    void wheelEvent(QWheelEvent *event) override;
};

#endif // GRAPHICSVIEW_H
