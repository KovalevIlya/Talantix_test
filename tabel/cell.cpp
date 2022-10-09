#include "cell.h"

using namespace CellNS;

Cell::Cell(int row, int column, Type type)
    : _type(type), _tempType(type), _row(row), _column(column)
{

}

bool Cell::operator ==(Cell rth)
{
    if (_type == rth._type
        && _tempType == rth._tempType
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

void Cell::setType(Type type)
{
    if (_type == type)
        return;

    if (type != Type::Start && type != Type::Finish) {
        _tempType = type;
    }

    _type = type;
}

Type Cell::type() const
{
    return _type;
}

void Cell::setColumn(int column)
{
    if (_column == column)
        return;
    _column = column;
}

int Cell::column() const
{
    return _column;
}

void Cell::setRow(int row)
{
    if (_row == row)
        return;
    _row = row;
}

int Cell::row() const
{
    return _row;
}

void Cell::setChecking(int checking)
{
    if (_checking == checking)
        return;
    _checking = checking;
}

int Cell::checking() const
{
    return _checking;
}
