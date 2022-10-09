#ifndef CELL_H
#define CELL_H

#include "global.h"

class Cell
{
//    Q_GADGET
public:
//    enum class Type
//    {
//        Open = 0,
//        Close,
//        Start,
//        Finish,
//    };
//    Q_ENUM(Type)

    Cell() = default;
    explicit Cell(int row, int column, CellNS::Type type = CellNS::Type::Open);

    bool operator ==(Cell rth);

    void resetType();

    void setType(CellNS::Type type);
    CellNS::Type type() const;

    void setColumn(int column);
    int column() const;

    void setRow(int row);
    int row() const;

    void setChecking(int checking);
    int checking() const;

    CellNS::Type _tempType = CellNS::Type::Open;
private:
    CellNS::Type _type = CellNS::Type::Open;
    int _row = -1;
    int _column = -1;
    bool _checking = false;
};

#endif // CELL_H
