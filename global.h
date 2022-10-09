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

#endif // GLOBAL_H
