#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;
};

#endif // GRAPHICSVIEW_H
