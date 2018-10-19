#ifndef D_GRAPH
#define D_GRAPH

#include <iostream>

#include "graph.h"

template <typename Tr>
class DirectedGraph : public Graph <Tr> {
    public:
        typedef DirectedGraph<Tr> self;
        typedef Node<self> node;
        typedef Edge<self> edge;

        typedef typename Tr::N N;
        typedef map<N,node*> NodeSeq;
        typedef map<N,edge*> EdgeSeq;

        typedef typename Tr::E E;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

        int in_degree(N n_index) {};
        int out_degree(N n_index) {};
        bool strongly_connected() {};

        void test_print() {
            cout << "Directed!" << endl;
        }
};

typedef DirectedGraph<Traits> directedGraph;

#endif
