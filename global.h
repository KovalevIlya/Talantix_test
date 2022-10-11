#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>

namespace CellNS {
Q_NAMESPACE

enum class Type
{
    Open,
    Close,
    Start,
    Finish
};
Q_ENUM_NS(Type)

}

constexpr int MAX_ROW_COUNT = 100;
constexpr int MAX_COLUMN_COUNT = 100;

#endif // GLOBAL_H
