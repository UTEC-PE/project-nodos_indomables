#include "disjoint.h"

void DisjointSet::makeSet(int data) {
    this->nodes[data] = new DNode(data);
}

bool DisjointSet::unionSet(int data1, int data2) {
    DNode* parent1 = findSet(data1);
    DNode* parent2 = findSet(data2);

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

DNode* DisjointSet::findSet(int data) {
    return findSet(this->nodes[data]);
}

DNode* DisjointSet::findSet(DNode* node) {
    DNode* current = node;
    while (current != current->parent)
        current = current->parent;

    return node->parent = current;
}
