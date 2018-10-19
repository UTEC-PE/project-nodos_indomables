#ifndef NODE_H
#define NODE_H

#ifndef NODE_COUNTER
#define NODE_COUNTER

char __node_counter = 0;

#endif

template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;

        EdgeSeq edges;

    private:
        N data;
        double x;
        double y;

    public:
        Node() : data(__node_counter++), x(0), y(0) {};
        Node(double x, double y) : data(__node_counter++), x(x), y(y) {};

        int replace(double x, double y) {
            this->x = x;
            this->y = y;
        }
        N get() {
            return data;
        }
};

#endif
