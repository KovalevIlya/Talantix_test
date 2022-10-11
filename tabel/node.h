#ifndef NODE_H
#define NODE_H

#include <QPoint>

/// Элемент дерева пути
struct Node
{
    Node() = delete;
    /// Конструктор перемещения
    /// \param index Индекс клетки
    /// \param parent Родителький элемент дерева
    Node(const QPoint &&index, Node *parent = nullptr);
    /// Конструктор копировани
    /// \param index Индекс клетки
    /// \param parent Родителький элемент дерева
    Node(const QPoint &index, Node *parent = nullptr);

    QPoint index; ///< Индекс клетки
    Node *parent = nullptr; ///< Родителький элемент дерева
};

#endif // NODE_H
