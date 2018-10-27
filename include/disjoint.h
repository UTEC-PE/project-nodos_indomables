#ifndef DISJOINT_H
#define DISJOINT_H

#include <map>

#include "dnode.h"

using namespace std;

template <typename T>
class DisjointSet {
    private:
        map<T, DNode <T> *> nodes;

    public:
        DisjointSet() {};
        void makeSet(T data)  {
            this->nodes[data] = new DNode <T>(data);
        }
        bool unionSet(T data1, T data2) {
            DNode <T> *parent1 = findSet(data1);
            DNode <T> *parent2 = findSet(data2);

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
        DNode <T> *findSet(T data) {
            return findSet(this->nodes[data]);
        }
        DNode <T> *findSet(DNode <T> *node) {
            return node == node->parent ? node : (node->parent = findSet(node->parent));
        }
        ~DisjointSet() {};
};

#endif
