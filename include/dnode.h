#ifndef DNODE_H
#define DNODE_H

template <typename T>
struct DNode {
    int rank;
    T data;
    DNode <T> *parent;

    DNode(T data) : data(data), rank(0), parent(this) {};
};

#endif
