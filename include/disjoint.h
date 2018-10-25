#ifndef DISJOINT_H
#define DISJOINT_H

#include <iostream>
#include <map>

#include "dnode.h"

using namespace std;

class DisjointSet {
    private:
        map<int, DNode*> nodes;

    public:
        DisjointSet() {};
        void makeSet(int data);
        bool unionSet(int data1, int data2);
        DNode* findSet(int data);
        DNode* findSet(DNode* node);
        ~DisjointSet() {};
};

#endif
