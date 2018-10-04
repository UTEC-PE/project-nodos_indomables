#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

#include "node.h"
#include "edge.h"

using namespace std;

class Traits {
	public:
		typedef int N;
		typedef int E;
};

template <typename Tr>
class Graph {
    public:
        typedef Graph<Tr> self;
        typedef Node<self> node;
        typedef Edge<self> edge;
        typedef vector<node*> NodeSeq;
        typedef list<edge*> EdgeSeq;
        typedef typename Tr::N N;
        typedef typename Tr::E E;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

    private:
        NodeSeq nodes;
				EdgeSeq edges;
        NodeIte ni;
        EdgeIte ei;

		public:
				void insert_node(double x, double y) {
						node *n = new node(x, y);

						nodes.push_back(n);
				}
				void insert_edge(N node1, N node2, E weight, bool direction) {
						edge *e = new edge(nodes.at(node1), nodes.at(node2), weight, direction);
				}
				void print_nodes() {
						for (ni = nodes.begin(); ni != nodes.end(); ++ni)
								cout << (*ni)->get() << ' ';

						cout << endl;
				}
				void print_edges() {
						for (ni = nodes.begin(); ni != nodes.end(); ++ni) {
								N current = (*ni)->get();

								for (ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ++ei)
										if ((*ei)->nodes[0]->get() >= current && (*ei)->nodes[1]->get() >= current)
												cout << (*ei)->nodes[0]->get() << ' '
														 << (*ei)->nodes[1]->get() << ' '
														 << (*ei)->get_data() << ' '
														 << (*ei)->direction() << endl;
								}

						cout << endl;
				}

				~Graph() {
						for (ni = nodes.begin(); ni != nodes.end(); ++ni)
								delete *ni;


						for (ei = edges.begin(); ei != edges.end(); ++ei)
								delete *ei;
				}
};

typedef Graph<Traits> graph;

#endif
