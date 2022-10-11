#include "table.h"
#include "node.h"

#include <QRandomGenerator>

Table::Table(const int rowCount, const int columnCount, QObject *parent)
    : QObject(parent), _columnCount(columnCount), _rowCount(rowCount)
{
    initTable();
}

void Table::reset(const int rowCount, const int columnCount)
{
    if (rowCount >= 0)
        _rowCount = rowCount;

    if (columnCount >= 0)
        _columnCount = columnCount;

    initTable();
}

QList<QPoint> Table::search()
{
    if (!isCorrectIndex(_start) || !isCorrectIndex(_finish)) {
        emit searched({});
        return {};
    }

    clearTree();
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

            for (const auto index : indices) {
                if (index == _finish) {
                    const auto path = getPath(new Node(index, _tree[i][j]));
                    emit searched(path);
                    return path;
                }

                if (!isCorrectIndex(index))
                    continue;

                if (!_table[index.x()][index.y()].checking()
                    && _table[index.x()][index.y()].type() == CellNS::Type::Open) {
                    _table[index.x()][index.y()].setChecking(true);
                    _tree[i + 1].append(new Node(index, _tree[i][j]));
                }
            }
        }
        ++i;
    }

    emit searched({});
    return {};
}

bool Table::isCorrectIndex(const int row, const int column) const
{
    if (row < 0 || row >= _rowCount || column < 0 || column >= _columnCount)
        return false;
    return true;
}

bool Table::isCorrectIndex(const QPoint &index) const
{
    return isCorrectIndex(index.x(), index.y());
}

void Table::checkCell(const int row, const int column)
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

bool Table::isStart() const
{
    return isCorrectIndex(_start);
}

void Table::setStart(const int row, const int column)
{

    if (isCorrectIndex(_start)) {
        const int x = _start.x();
        const int y = _start.y();

        _table[x][y].resetType();
        emit cellChanged(x, y, _table[x][y]);
    }

    if (!isCorrectIndex(row, column)) {
        _start = { -1, -1 };
        return;
    }

    if (_start == _finish || QPoint(row, column) == _finish)
        setFinish(-1, -1);

    _table[row][column].setType(CellNS::Type::Start);

    _start = { row, column };

    emit cellChanged(row, column, _table[row][column]);
}

bool Table::isFinish() const
{
    return isCorrectIndex(_finish);
}

void Table::setFinish(const int row, const int column)
{
    if (isCorrectIndex(_finish)) {
        const int x = _finish.x();
        const int y = _finish.y();

        _table[x][y].resetType();
        emit cellChanged(x, y, _table[x][y]);
    }

    if (!isCorrectIndex(row, column)) {
        _finish = { -1, -1 };
        return;
    }

    if (_finish == _start || QPoint(row, column) == _start)
        setStart(-1, -1);

    _table[row][column].setType(CellNS::Type::Finish);

    _finish = { row, column };

    emit cellChanged(row, column, _table[row][column]);
}

void Table::setCell(const int row, int column, const Cell &cell)
{
    if (!isCorrectIndex(row, column))
        return;

    if (_table[row][column] == cell)
        return;

    _table[row][column] = cell;

    emit cellChanged(row, column, _table[row][column]);
}

Cell Table::cell(const int row, const int column) const
{
    if (!isCorrectIndex(row, column))
        return Cell();

    return _table[row][column];
}

void Table::setColumnCount(const int columnCount)
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

void Table::setRowCount(const int rowCount)
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
    _start = { -1, -1 };
    _finish = { -1, -1 };
    _table.reserve(_rowCount);

    for (int row = 0; row < _rowCount; ++row) {
        QVector<Cell> line;
        line.reserve(_columnCount);
        for (int column = 0; column < _columnCount; ++column) {
            CellNS::Type type = static_cast<CellNS::Type>(QRandomGenerator::system()->bounded(0, 2));
            line.insert(column, Cell(row, column, type));
        }
        _table.insert(row, line);
    }

    emit sizeChanged(_rowCount, _columnCount);
}
