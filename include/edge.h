#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::E N;
        typedef typename G::node node;
        typedef typename G::EdgeConstructor Constructor;

        node *nodes[2];

    protected:
        E data;
        bool dir;
        Constructor cns;

    public:
        Edge(node *node1, node *node2, E data) :
        data(data) {
            this->nodes[0] = node1;
            this->nodes[1] = node2;

            cns(this, node1, node2);

            node1->d++;
            node2->d++;
        }
        inline E weight() {
            return this->data;
        }
};

#endif
