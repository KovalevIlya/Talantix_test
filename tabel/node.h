#ifndef NODE_H
#define NODE_H

#include <QPoint>

struct Node
{
    Node() = delete;
    Node(QPoint &&index, Node *parent = nullptr);
    Node(const QPoint &index, Node *parent = nullptr);

    QPoint index;
    Node *parent = nullptr;
};

#endif // NODE_H
