#ifndef TABLE_H
#define TABLE_H

#include "cell.h"

#include <QObject>
#include <QPoint>

struct Node;

/// Таблица лабиринта
class Table : public QObject
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param rowCount Количество строк
    /// \param columnCount Количество столбцов
    /// \param parent Родительский объект
    explicit Table(const int rowCount, const int columnCount, QObject *parent = nullptr);
    /// Сбросить лабиринт
    /// \param rowCount Количество строк
    /// \param columnCount Количество столбцов
    void reset(const int rowCount = -1, const int columnCount = -1);
    /// Поиск пути
    /// \return Путь
    QList<QPoint> search();

    /// Сигнал об окончании поиска пути
    /// \param Найденый путь
    Q_SIGNAL void searched(const QList<QPoint> &path);

    /// Проверка корректности индекса
    /// \param row Строка
    /// \param column Столбец
    /// \return Является ли корректным индексом
    bool isCorrectIndex(const int row, const int column) const;
    /// Проверка корректности индекса
    /// \param index Индекс
    /// \return Является ли корректным индексом
    bool isCorrectIndex(const QPoint &index) const;

    /// Установить флаг проврки у клетки
    /// \param row Строка
    /// \param column Столбец
    void setCheckingCell(const int row, const int column);
    /// Сбросить флаги проверки у клеток
    void resetChecking();

    /// Сигнал об изменении размера таблицы
    /// \param rowCount Новое количество строк
    /// \param columnCount Новое количество столбцов
    Q_SIGNAL void sizeChanged(int rowCount, int columnCount);

    /// Проверка начала пути
    /// \return Установлено ли начало пути
    bool isStart() const;
    /// Установить начало пути
    /// \param row Строка
    /// \param column Столбец
    Q_SLOT void setStart(const int row, const int column);
    /// Проверка конца пути
    /// \return Установлен ли конец пути
    bool isFinish() const;
    /// Установить конец пути
    /// \param row Строка
    /// \param column Столбец
    Q_SLOT void setFinish(const int row, const int column);

    /// Установить клетку в позицию
    /// \param row Строка
    /// \param column Столбец
    /// \param cell Клетка
    Q_SLOT void setCell(const int row, const int column, const Cell &cell);
    /// Получить клетку
    /// \param row Строка
    /// \param column Столбец
    /// \return Клетка
    Cell cell(const int row, const int column) const;
    /// Сигнал об изменении клетки
    /// \param row Строка
    /// \param column Столбец
    /// \param cell Клетка
    Q_SIGNAL void cellChanged(int row, int column, const Cell &cell);

    /// Установить количество столбцов
    /// \param columnCount Количество столбцов
    /// \note Лабиринт будет пересобран
    Q_SLOT void setColumnCount(const int columnCount);
    /// Получить количество столбцов
    /// \return  Количество столбцов
    /// \brief clearTree
    ///
    int columnCount() const;
    /// Сигнал об изменении количества столбцов
    /// \param columnCount
    Q_SIGNAL void columnCountChanged(int columnCount);

    /// Установить количество строк
    /// \param rowCount количество строк
    /// \note Лабиринт будет пересобран
    Q_SLOT void setRowCount(const int rowCount);
    /// Получить количество строк
    /// \return Количество строк
    int rowCount() const;
    /// Сигнал об изменении количество строк
    /// \param rowCount Количество строк
    Q_SIGNAL void rowCountChanged(int rowCount);

private:
    /// Получить путь из списка
    /// \param node Вершина списка
    /// \return Путь
    QList<QPoint> getPath(Node *node);
    /// Очистить дерево поиска пути
    void clearTree();
    /// Инициализировать лабиринт
    void initTable();

    QList<QList<Node *>> _tree; ///< Дерево путь
    QVector<QVector<Cell>> _table; ///< Таблица лабиринта
    QPoint _start { -1, -1 }; ///< Индекс начала пути
    QPoint _finish { -1, -1 }; ///< Индекс конца пути
    int _columnCount; ///< Количество столбцов
    int _rowCount; ///< Количество строк
};

#endif // TABLE_H
