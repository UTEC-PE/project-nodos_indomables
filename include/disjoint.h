#ifndef DISJOINT_H
#define DISJOINT_H

#include <iostream>
#include <map>

#include "dnode.h"

using namespace std;

template <typename T>
class DisjointSet {
    private:
        map<T, DNode<T>*> nodes;

    public:
        DisjointSet() {};
        void makeSet(T data);
        bool unionSet(T data1, T data2);
        DNode<T>* findSet(T data);
        DNode<T>* findSet(DNode<T>* node);
        ~DisjointSet() {};
};

#endif
