#ifndef EVENTTYPECHENGED_H
#define EVENTTYPECHENGED_H

#include "global.h"

#include <QEvent>

class EventTypeChenged : public QEvent
{
public:
    EventTypeChenged(const CellNS::Type typeCell);

    CellNS::Type typeCell() const;

    static const int type;

private:
    CellNS::Type _typeCell;
};

#endif // EVENTTYPECHENGED_H
