#ifndef DNODE_H
#define DNODE_H

struct DNode {
    int rank;
    int data;
    DNode* parent;

    DNode(int data) : data(data), rank(0), parent(this) {};
};

#endif
