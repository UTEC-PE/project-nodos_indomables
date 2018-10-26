#ifndef D_GRAPH
#define D_GRAPH

#include <iostream>

#include "graph.h"

template <typename Tr>
class DirectedGraph : public Graph <Tr, DirectedGraph<Tr>> {
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

        int in_degree(N n) {};
        int out_degree(N n) {};
        bool source_node(N n) {};
        bool sink(N n) {};
        bool strongly_connected() {};
};

typedef DirectedGraph<Traits> directedGraph;

#endif
