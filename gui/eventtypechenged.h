#ifndef EVENTTYPECHENGED_H
#define EVENTTYPECHENGED_H

#include "global.h"

#include <QEvent>

/// Событие изменения типа клетки
class EventTypeChenged : public QEvent
{
public:
    /// Конструктор
    /// \param typeCell Новый тип клетки
    EventTypeChenged(const CellNS::Type typeCell);

    /// Получить тип клетки
    /// \return Тип клетки
    CellNS::Type typeCell() const;

    static const int type; ///< Тип события

private:
    CellNS::Type _typeCell; ///< Тип клетки
};

#endif // EVENTTYPECHENGED_H
