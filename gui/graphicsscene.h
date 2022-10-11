#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject *parent = nullptr);

    Q_SIGNAL void clickedItem(const QPointF &point);
    Q_SIGNAL void setFinish(const QPointF &point);
    Q_SIGNAL void removeFinish();
};

#endif // GRAPHICSSCENE_H
