#ifndef U_GRAPH
#define U_GRAPH

#include "graph.h"

template <typename Tr>
class UndirectedGraph : public Graph <Tr> {
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

        void kruskal(self *g) {};
        void prim(self *g) {};
};

#endif
