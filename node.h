#ifndef NODE_H
#define NODE_H

#include <random>

using namespace std;

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
        Node(N data) : data(data) {
						random_device rd;

						x = rd() / rd.max();
            y = rd() / rd.max();
        };
        Node(N data, double x, double y) : data(data), x(x), y(y) {};

        int replace(double x, double y) {
            this->x = x;
            this->y = y;
        }
        inline N get() {
            return data;
        }
        void killSelf() {
            for (auto i : edges)
                i.second->killSelf();
        };
};

#endif
