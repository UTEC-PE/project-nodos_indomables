#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <stack>
#include <queue>

#include "node.h"
#include "edge.h"
#include "disjoint.h"

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

        typedef typename Tr::N N;
        typedef map<N,node*> NodeSeq;
        typedef map<N,edge*> EdgeSeq;

        typedef typename Tr::E E;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

		protected:
        NodeSeq nodes;
				EdgeSeq edges;
        NodeIte ni;
        EdgeIte ei;

		public:
				Graph () {};
				Graph (int n) {
						while (n--)
								insert_node();
				};

				void insert_node() {
						node *n = new node(nodes.size());

						nodes[n->get()] = n;
				}
				void insert_node(double x, double y) {
						node *n = new node(nodes.size(), x, y);

						nodes[n->get()] = n;
				}
				void insert_edge(N node1, N node2, E weight = 1) {
						new edge(nodes.at(node1), nodes.at(node2), weight);
				}
				void print_nodes() {
						for (ni = nodes.begin(); ni != nodes.end(); ++ni)
								cout << ni->second->get() << ' ';

						cout << endl;
				}
				void print_edges() {
						for (ni = nodes.begin(); ni != nodes.end(); ++ni) {
								N current = ni->second->get();

								for (ei = ni->second->edges.begin(); ei != ni->second->edges.end(); ++ei)
										if (ei->second->nodes[0]->get() >= current && ei->second->nodes[1]->get() >= current)
												cout << ei->second->nodes[0]->get() << ' '
														 << ei->second->nodes[1]->get() << ' '
														 << ei->second->get_data() << endl;
								}

						cout << endl;
				}
				inline int weight() {
						return nodes.size();
				}
				inline int degree(N n) {
						return nodes[n]->edges.size();
				};
				void bfs(N n, self *g) {
						queue <N> root;
						bool *visited = new bool [nodes.size()]();

						root.push(n);

						while (!root.empty()) {
								for (auto i : nodes[root.front()]->edges)
										if (!visited[i.first]) {
												visited[i.first] = true;
												root.push(i.first);

												g->insert_edge(root.front(), i.first, i.second->get_data());
										}

								root.pop();
						}

						delete [] visited;
				}
				void bfs(N n,
					function <void (N, N)> discover = [] (N source, N discovered) -> void {},
					function <void (N, N)> visit = [] (N source, N visited) -> void {}) {
						queue <N> root;
						bool *visited = new bool [nodes.size()]();

						root.push(n);
						visited[n] = true;

						while (!root.empty()) {
								for (auto i : nodes[root.front()]->edges)
										if (!visited[i.first]) {
												visited[i.first] = true;
												root.push(i.first);

												discover(root.front(), i.first);
										} else {
												visit(root.front(), i.first);
										}

								root.pop();
						}

						delete [] visited;
				};
				void dfs(self *g) {};
				bool bipartite() {
						bool b = true;
						int *color = new int[nodes.size()] ();

						color[0] = 1;

						bfs(0,
							[color] (N source, N discovered) -> void {
								color[discovered] = color[source] == 1 ? 2 : 1;
				    	},
							[color, &b] (N source, N visited) -> void {
								b = b && color[source] != color[visited];
				    	});

						delete [] color;

						return b;
				};
				bool connected() {};
				bool bipartite_component(N n) {};
				vector <N> component_heads() {};

				~Graph() {
						for (ni = nodes.begin(); ni != nodes.end(); ++ni)
								for (ei = ni->second->edges.begin(); ei != ni->second->edges.end(); ++ei)
										if (ni->first < ei->first)
												delete ei->second;


						for (ni = nodes.begin(); ni != nodes.end(); ++ni)
								delete ei->second;
				}
};

typedef Graph<Traits> graph;

#endif
