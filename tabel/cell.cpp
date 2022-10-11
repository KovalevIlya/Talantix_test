#include "cell.h"

using namespace CellNS;

Cell::Cell(const int row, const int column, const Type type)
    : _type(type), _defaultType(type), _row(row), _column(column)
{

}

bool Cell::operator ==(const Cell rth) const
{
    if (_type == rth._type
        && _defaultType == rth._defaultType
        && _row == rth._row
        && _column == rth._column) {
        return true;
    }
    return false;
}

void Cell::resetType()
{
    _type = _defaultType;
}

void Cell::setType(const Type type)
{
    if (_type == type)
        return;

    if (type != Type::Start && type != Type::Finish) {
        _defaultType = type;
    }

    _type = type;
}

Type Cell::type() const
{
    return _type;
}

void Cell::setColumn(const int column)
{
    if (_column == column)
        return;

    _column = column;
}

int Cell::column() const
{
    return _column;
}

void Cell::setRow(const int row)
{
    if (_row == row)
        return;

    _row = row;
}

int Cell::row() const
{
    return _row;
}

void Cell::setChecking(const int checking)
{
    if (_checking == checking)
        return;

    _checking = checking;
}

int Cell::checking() const
{
    return _checking;
}
