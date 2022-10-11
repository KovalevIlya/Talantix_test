#include "eventtypechenged.h"

const int EventTypeChenged::type = QEvent::registerEventType();

EventTypeChenged::EventTypeChenged(const CellNS::Type typeCell)
    : QEvent(static_cast<QEvent::Type>(type)), _typeCell(typeCell)
{

}

CellNS::Type EventTypeChenged::typeCell() const
{
    return _typeCell;
}
