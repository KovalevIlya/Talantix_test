#include "eventtypechenged.h"

const int EventTypeChenged::type = QEvent::registerEventType();

EventTypeChenged::EventTypeChenged(const CellNS::Type typeCell_)
    : QEvent(static_cast<QEvent::Type>(type)), _typeCell(typeCell_)
{

}

CellNS::Type EventTypeChenged::typeCell()
{
    return _typeCell;
}
