#include "table.h"
#include "node.h"

#include <QRandomGenerator>

Table::Table(int columnCount, int rowCount, QObject *parent)
    : QObject(parent), _columnCount(columnCount), _rowCount(rowCount)
{
    initTable();
}

void Table::reset(int columnCount, int rowCount)
{
    if (columnCount >= 0)
        _columnCount = columnCount;

    if (rowCount >= 0)
        _rowCount = rowCount;

    initTable();
}

QList<QPoint> Table::search()
{
    if (!isCorrectIndex(_start) || !isCorrectIndex(_finish))
        return {};

    _tree.append({ new Node(_start) });
    _table[_start.x()][_start.y()].setChecking(true);

    int i = 0;

    while(!_tree[i].isEmpty()) {
        _tree.append(QList<Node *>());
        const int count = _tree[i].count();
        for (int j = 0; j < count; ++j) {
            const int x = _tree[i][j]->index.x();
            const int y = _tree[i][j]->index.y();

            QVector<QPoint> indices = { { x, y + 1 }, { x + 1, y }, { x, y - 1 }, { x - 1, y } };
            for (auto index : indices) {
                if (index == _finish)
                    return getPath(new Node(index, _tree[i][j]));

                if (!isCorrectIndex(index))
                    continue;

                if (!_table[index.x()][index.y()].checking()
                    && _table[index.x()][index.y()].type() == Cell::Type::Open) {
                    _table[index.x()][index.y()].setChecking(true);
                    _tree[i + 1].append(new Node(index, _tree[i][j]));
                }
            }
        }
        ++i;
    }
    return {};
}

bool Table::isCorrectIndex(int row, int column) const
{
    if (row < 0 || row >= _rowCount || column < 0 || column >= _columnCount)
        return false;
    return true;
}

bool Table::isCorrectIndex(QPoint index) const
{
    return isCorrectIndex(index.x(), index.y());
}

void Table::checkCell(int row, int column)
{
    if (!isCorrectIndex(row, column))
        return;

    _table[row][column].setChecking(true);
}

void Table::resetChecking()
{
    for (int row = 0; row < _rowCount; ++row) {
        for (int column = 0; column < _columnCount; ++column)
            _table[row][column].setChecking(false);
    }
}

void Table::setStart(int row, int column)
{
    if (!isCorrectIndex(row, column))
        return;

    if (isCorrectIndex(_start))
        _table[_start.x()][_start.y()].resetType();

    _table[row][column].resetType();
    _table[row][column].setType(Cell::Type::Start);

    if (_start == _finish)
        _finish = { -1, -1 };

    _start = { row, column };

    emit cellChanged(row, column, _table[row][column]);
}

void Table::setFinish(int row, int column)
{
    if (!isCorrectIndex(row, column))
        return;

    if (isCorrectIndex(_finish))
        _table[_finish.x()][_finish.y()].resetType();

    _table[row][column].resetType();
    _table[row][column].setType(Cell::Type::Finish);

    if (_start == _finish)
        _start = { -1, -1 };

    _finish = { row, column };

    emit cellChanged(row, column, _table[row][column]);
}

void Table::setCell(int row, int column, Cell cell)
{
    if (!isCorrectIndex(row, column))
        return;

    if (_table[row][column] == cell)
        return;

    _table[row][column] = cell;

    emit cellChanged(row, column, _table[row][column]);
}

Cell Table::cell(int row, int column) const
{
    if (!isCorrectIndex(row, column))
        return Cell();

    return _table[row][column];
}

void Table::setColumnCount(int columnCount)
{
    if (columnCount < 0 || columnCount == _columnCount)
        return;

    _columnCount = columnCount;

    initTable();

    emit columnCountChanged(_columnCount);
    emit sizeChanged(_rowCount, _columnCount);
}

int Table::columnCount() const
{
    return _columnCount;
}

void Table::setRowCount(int rowCount)
{
    if (rowCount < 0 || rowCount == _rowCount)
        return;

    _rowCount = rowCount;

    initTable();

    emit columnCountChanged(_rowCount);
    emit sizeChanged(_rowCount, _columnCount);
}

int Table::rowCount() const
{
    return _rowCount;
}

QList<QPoint> Table::getPath(Node *node)
{
    QList<QPoint> path;
    Node *tempNode = node;

    while (tempNode) {
        path.prepend(tempNode->index);
        tempNode = tempNode->parent;
    }

    delete node;
    clearTree();

    return path;
}

void Table::clearTree()
{
    const int treeCount = _tree.count();
    for (int i = 0; i < treeCount; ++i) {
        const int subtreeCount = _tree[i].count();
        for (int j = 0; j < subtreeCount; ++j)
            delete _tree[i][j];
    }

    _tree.clear();

    resetChecking();
}

void Table::initTable()
{
    _table.clear();
    _table.reserve(_rowCount);
    for (int row = 0; row < _rowCount; ++row) {
        QVector<Cell> line;
        line.reserve(_columnCount);
        for (int column = 0; column < _columnCount; ++column) {
            Cell::Type type = static_cast<Cell::Type>(QRandomGenerator::system()->bounded(0, 2));
            line.insert(column, Cell(row, column, type));
        }
        _table.insert(row, line);
    }

    emit sizeChanged(_rowCount, _columnCount);
}
