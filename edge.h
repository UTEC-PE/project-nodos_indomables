#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::node node;

        node *nodes[2];

    private:
        E data;
        bool dir;

    public:
        Edge(node *node1, node *node2, E data) :
        data(data) {
            nodes[0] = node1;
            nodes[1] = node2;

            node1->edges[node2->get()] = this;
            node2->edges[node1->get()] = this;
        }
        inline E get_data() {
            return data;
        }
        void killSelf() {
            nodes[1]->edges.erase(nodes[0]->get());
            nodes[0]->edges.erase(nodes[1]->get());

            delete this;
        };
};

#endif
