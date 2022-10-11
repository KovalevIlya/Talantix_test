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
    explicit Table(const int rowCount, const int columnCount, QObject *parent = nullptr);
    void reset(const int rowCount = -1, const int columnCount = -1);
    QList<QPoint> search();

    Q_SIGNAL void searched(const QList<QPoint> &path);

    bool isCorrectIndex(const int row, const int column) const;
    bool isCorrectIndex(const QPoint &index) const;

    void checkCell(const int row, const int column);
    void resetChecking();

    Q_SIGNAL void sizeChanged(int rowCount, int columnCount);

    bool isStart() const;
    Q_SLOT void setStart(const int row, const int column);
    bool isFinish() const;
    Q_SLOT void setFinish(const int row, const int column);

    Q_SLOT void setCell(const int row, const int column, const Cell &cell);
    Cell cell(const int row, const int column) const;
    Q_SIGNAL void cellChanged(int row, int column, Cell cell);

    Q_SLOT void setColumnCount(const int columnCount);
    int columnCount() const;
    Q_SIGNAL void columnCountChanged(int columnCount);

    Q_SLOT void setRowCount(const int rowCount);
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
