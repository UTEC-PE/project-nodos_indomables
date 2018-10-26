#ifndef U_GRAPH
#define U_GRAPH

#include <iostream>
#include <vector>
#include <algorithm>

#include "graph.h"
#include "traits.h"

using namespace std;

template <typename Tr>
class UndirectedGraph : public Graph <Tr, UndirectedGraph<Tr>> {
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


        UndirectedGraph () : Graph <Tr, UndirectedGraph<Tr>>() {};
        UndirectedGraph (int n) : Graph <Tr, UndirectedGraph<Tr>>(n) {}

        void kruskal(function <void (N, N)> newEdge = [] (N node0, N node1) -> void {}) {
						DisjointSet <N> d;

            vector <edge *> sortedEdges;

						for (auto i : this->nodes) {
								d.makeSet(i.first);

                for (auto j : i.second->edges)
                    if (i.first < j.first)
                        sortedEdges.push_back(j.second);
            }

            sort(sortedEdges.begin(), sortedEdges.end(), [] (edge *edge1, edge *edge2) -> bool {
                return edge1->get_data() < edge2->get_data();
            });

            for (auto i : sortedEdges) {
                N n0 = i->nodes[0]->get(), n1 = i->nodes[1]->get();
                if (d.findSet(n0) != d.findSet(n1)) {
                    d.unionSet(n0, n1);

                    newEdge(n0, n1);
                }
            }


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
