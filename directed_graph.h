#ifndef D_GRAPH
#define D_GRAPH

#include "graph.h"

template <typedef T>
class UndirectedGraph : public Graph {
    public:
        typedef UndirectedGraph<Tr> self;
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
};

#endif
