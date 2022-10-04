#include "node.h"

Node::Node(QPoint &&index, Node *parent)
    : parent(parent)
{
    this->index = std::move(index);
}

Node::Node(const QPoint &index, Node *parent)
    : parent(parent)
{
    this->index = index;
}
