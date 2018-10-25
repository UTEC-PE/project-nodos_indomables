#include "disjoint.h"

template <typename T>
void DisjointSet<T>::makeSet(T data) {
    this->nodes[data] = new DNode<T> (data);
}

template <typename T>
bool DisjointSet<T>::unionSet(T data1, T data2) {
    DNode<T>* parent1 = findSet(data1);
    DNode<T>* parent2 = findSet(data2);

    if (parent1 != parent2) {
        if (parent1->rank >= parent2->rank) {
            parent1->rank = (parent1->rank == parent2->rank) ? parent1->rank + 1 : parent1->rank;
            parent2->parent = parent1;
        } else {
            parent1->parent = parent2;
        }

        return true;
    }

    return false;
}

template <typename T>
DNode<T>* DisjointSet<T>::findSet(T data) {
    return findSet(this->nodes[data]);
}

template <typename T>
DNode<T>* DisjointSet<T>::findSet(DNode<T>* node) {
    DNode<T>* current = node;
    while (current != current->parent)
        current = current->parent;

    return node->parent = current;
}
