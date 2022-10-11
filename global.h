#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>

/// Пространство имен клеток лабиринта
namespace CellNS {
Q_NAMESPACE

/// Типы клеток
enum class Type
{
    Open, ///< Открыта
    Close, ///< Заблокирована
    Start, ///< Начало пути
    Finish ///< Конец Пути
};
Q_ENUM_NS(Type)

}

constexpr int MAX_ROW_COUNT = 100; ///< Максимальное количество строк в лабиринте
constexpr int MAX_COLUMN_COUNT = 100; ///< Максимальное количество столбцов в лабиринте

#endif // GLOBAL_H
