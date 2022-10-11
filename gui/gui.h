#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QMutex>

class Table;
class GraphicsScene;
class QGraphicsItem;

class Gui : public QWidget
{
    Q_OBJECT
public:
    explicit Gui(Table *table, QWidget *parent = nullptr);

    void initScene();
    Q_SLOT void setPath(const QList<QPoint> &path);
    void removeStartPath();
    void search();

    QPoint getTablePoint(const QPointF &point) const;
    QPointF getScenePoint(const QPoint &point) const;
    QPointF getLinePoint(const QPoint &point) const;

private:
    Table* _table;
    GraphicsScene* _scene;
    QGraphicsItem *_startPath = nullptr;
    QMutex _mutex;

    bool _isFinish = false;

    int _width = 0;
    int _height = 0;

    const int _widthCell = 50;
    const int _heightCell = 50;
};

#endif // GUI_H
