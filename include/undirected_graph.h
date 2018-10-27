#ifndef U_GRAPH
#define U_GRAPH

#include <iostream>
#include <vector>
#include <algorithm>

#include "graph.h"
#include "traits.h"

using namespace std;

struct UndirectedNodeConstructor;
struct UndirectedNodeDestructor;

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

        typedef UndirectedNodeConstructor Constructor;


        UndirectedGraph() : Graph <Tr, UndirectedGraph<Tr>> () {};
        UndirectedGraph(int n) : Graph <Tr, UndirectedGraph<Tr>> (n) {}

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
        };
        void prim(self *g) {};

        virtual ~UndirectedGraph() {
						for (auto i : this->nodes)
								for (auto j : i.second->edges)
										if (i.first < j.first)
												delete j.second;

						for (auto i : this->nodes)
								delete i.second;
				}
};

struct UndirectedNodeConstructor {
		typedef UndirectedGraph<Traits> G;
		typedef typename G::node node;
		typedef typename G::edge edge;

		void operator() (edge *e, node *node1, node *node2) {
        node1->edges[node2->get()] = e;
        node2->edges[node1->get()] = e;
		}
};

typedef UndirectedGraph<Traits> undirectedGraph;

#endif
