#include "cell.h"

Cell::Cell(int row, int column, Cell::Type type)
    : _type(type), _tempType(type), _row(row), _column(column)
{

}

bool Cell::operator ==(Cell rth)
{
    if (_type == rth._type
        && _row == rth._row
        && _column == rth._column) {
        return true;
    }
    return false;
}

void Cell::resetType()
{
    _type = _tempType;
}

void Cell::setType(Cell::Type type)
{
    if (_type == type)
        return;

    if (type == Type::Start || type == Type::Finish)
        _tempType = _type;

    _type = type;
}

Cell::Type Cell::type()
{
    return _type;
}

void Cell::setColumn(int column)
{
    if (_column == column)
        return;
    _column = column;
}

int Cell::column()
{
    return _column;
}

void Cell::setRow(int row)
{
    if (_row == row)
        return;
    _row = row;
}

int Cell::row()
{
    return _row;
}

void Cell::setChecking(int checking)
{
    if (_checking == checking)
        return;
    _checking = checking;
}

int Cell::checking()
{
    return _checking;
}
