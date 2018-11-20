#ifndef NODE_H
#define NODE_H

#include <random>

template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;

        EdgeSeq edges;
        int d;

    private:
        N data;
        double x;
        double y;


    public:
        Node(N data) : data(data) {
						std::random_device rd;

						this->x = rd() / rd.max();
            this->y = rd() / rd.max();
        };
        Node(N data, double x, double y) : data(data), x(x), y(y) {};
        Node(const Node &node) : data(node.data), x(node.x), y(node.y) {};

        void replace(double x, double y) {
            this->x = x;
            this->y = y;
        }
        inline N get() {
            return this->data;
        }
        inline int degree() {
            return this->d;
        }
        inline int in_degree() {
            return this->d - this->edges.size();
        }
        inline int out_degree() {
            return this->edges.size();
        }
};

#endif
