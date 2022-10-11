#ifndef CELL_H
#define CELL_H

#include "global.h"

/// Клетка лабиринта
class Cell
{
public:
    /// Конструктор "по умолчанию"
    Cell() = default;
    /// Конструктор
    /// \param row Строка
    /// \param column Столбец
    /// \param type Тип клетки
    explicit Cell(const int row, const int column, const CellNS::Type type = CellNS::Type::Open);

    /// Оператор равества
    /// \param rth Правый элемент сравнения
    /// \return Равны ли клетки
    bool operator ==(const Cell rth) const;

    /// Сбросить тип клетки
    void resetType();

    /// Установить тип клетки
    /// \param type Тип клетки
    void setType(const CellNS::Type type);
    /// Получить тип клетки
    /// \return Тип клетки
    CellNS::Type type() const;

    /// Установить столбец
    /// \param column Столбец
    void setColumn(const int column);
    /// Получить столбец
    /// \return Столбец
    int column() const;

    /// Установить строку
    /// \param row Строка
    void setRow(const int row);
    /// Получить строку
    /// \return Строка
    int row() const;

    /// Установить флаг проверки
    /// \param checking Флаг проверки
    void setChecking(const int checking);
    /// Получит флаг проверки
    /// \return Флаг проверки
    int checking() const;

private:
    CellNS::Type _type = CellNS::Type::Open; ///< Текущий тип клетки
    CellNS::Type _defaultType = CellNS::Type::Open; ///< Тип клетки по умолчанию
    int _row = -1; ///< Строка
    int _column = -1; ///< Столбец
    bool _checking = false; ///< Флаг проверки
};

#endif // CELL_H
