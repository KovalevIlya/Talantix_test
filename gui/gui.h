#ifndef GUI_H
#define GUI_H

#include <QWidget>

class Table;
class QGraphicsScene;

class Gui : public QWidget
{
    Q_OBJECT
public:
    explicit Gui(Table *table, QWidget *parent = nullptr);

    void initScene();

private:
    Table* _table;
    QGraphicsScene* _scene;

    int _width = 0;
    int _height = 0;

    const int _widthCell = 50;
    const int _heightCell = 50;
};

#endif // GUI_H
