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
    Type type();

    void setColumn(int column);
    int column();

    void setRow(int row);
    int row();

    void setChecking(int checking);
    int checking();

private:
    Type _tempType = Type::Open;
    Type _type = Type::Open;
    int _row = -1;
    int _column = -1;
    bool _checking = false;
};
//Q_DECLARE_METATYPE(Cell)


#endif // CELL_H
