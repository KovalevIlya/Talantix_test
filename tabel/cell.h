#ifndef CELL_H
#define CELL_H

#include <QObject>

class Cell
{
    Q_GADGET
public:
    enum class Type
    {
        Open = 0,
        Close,
        Start,
        Finish,
    };
    Q_ENUM(Type)

    Cell() = default;
    explicit Cell(int row, int column, Type type = Type::Open);

    bool operator ==(Cell rth);

    void resetType();

    void setType(Type type);
    Type type() const;

    void setColumn(int column);
    int column() const;

    void setRow(int row);
    int row() const;

    void setChecking(int checking);
    int checking() const;

private:
    Type _tempType = Type::Open;
    Type _type = Type::Open;
    int _row = -1;
    int _column = -1;
    bool _checking = false;
};

#endif // CELL_H
