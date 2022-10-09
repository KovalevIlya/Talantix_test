#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "global.h"

#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject *parent = nullptr);

    Q_SIGNAL void clickedItem(QPointF point);
};

#endif // GRAPHICSSCENE_H
