#ifndef U_GRAPH
#define U_GRAPH

#include <iostream>
#include <vector>
#include <algorithm>

#include "graph.h"

using namespace std;

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

        UndirectedGraph () {};
        UndirectedGraph (int n) {
						while (n--)
								this->insert_node();
				};

        void kruskal(self *g) {


            // cout << "Inside" << endl;
            // vector <edge *> sorted_edges;
            //
            // for (this->ni = this->nodes.begin(); this->ni != this->nodes.end(); ++this->ni)
						// 		for (this->ei = this->ni->second->edges.begin(); this->ei != this->ni->second->edges.end(); ++this->ei)
						// 				if (this->ni->first < this->ei->first)
            //             sorted_edges.push_back(this->ei->second);
            //
            // sort(sorted_edges.begin(), sorted_edges.end(), [] (edge *e1, edge * e2) {
            //     return e1->get_data() < e2->get_data();
            // });
            //
            // cout << sorted_edges.size() << endl << endl << endl;

            // DisjointSet sets;
            //
            // for (auto i : nodes)
            //     sets.makeSet(i.first);
            //
        };
        void prim(self *g) {};
};

typedef UndirectedGraph<Traits> undirectedGraph;

#endif
