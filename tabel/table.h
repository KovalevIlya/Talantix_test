#ifndef TABLE_H
#define TABLE_H

#include "cell.h"

#include <QObject>
#include <QPoint>

struct Node;

class Table : public QObject
{
    Q_OBJECT
public:
    explicit Table(int columnCount, int rowCount, QObject *parent = nullptr);
    void reset(int columnCount = -1, int rowCount = -1);
    QList<QPoint> search();

    bool isCorrectIndex(int row, int column) const;
    bool isCorrectIndex(QPoint index) const;

    void checkCell(int row, int column);
    void resetChecking();

    Q_SIGNAL void sizeChanged(int rowCount, int columnCount);

    Q_SLOT void setStart(int row, int column);
    Q_SLOT void setFinish(int row, int column);

    Q_SLOT void setCell(int row, int column, Cell cell);
    Cell cell(int row, int column) const;
    Q_SIGNAL void cellChanged(int row, int column, Cell cell);

    Q_SLOT void setColumnCount(int columnCount);
    int columnCount() const;
    Q_SIGNAL void columnCountChanged(int columnCount);

    Q_SLOT void setRowCount(int rowCount);
    int rowCount() const;
    Q_SIGNAL void rowCountChanged(int rowCount);

private:
    QList<QPoint> getPath(Node *node);
    void clearTree();
    void initTable();

    QList<QList<Node *>> _tree;
    QVector<QVector<Cell>> _table;
    QPoint _start { -1, -1 };
    QPoint _finish { -1, -1 };
    int _columnCount;
    int _rowCount;
};

#endif // TABLE_H
