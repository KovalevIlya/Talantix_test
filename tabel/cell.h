#ifndef CELL_H
#define CELL_H

#include "global.h"

class Cell
{
public:
    Cell() = default;
    explicit Cell(const int row, const int column, const CellNS::Type type = CellNS::Type::Open);

    bool operator ==(const Cell rth) const;

    void resetType();

    void setType(const CellNS::Type type);
    CellNS::Type type() const;

    void setColumn(const int column);
    int column() const;

    void setRow(const int row);
    int row() const;

    void setChecking(const int checking);
    int checking() const;

private:
    CellNS::Type _type = CellNS::Type::Open;
    CellNS::Type _tempType = CellNS::Type::Open;
    int _row = -1;
    int _column = -1;
    bool _checking = false;
};

#endif // CELL_H
