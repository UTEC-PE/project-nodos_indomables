#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>

#include "node.h"
#include "edge.h"
#include "disjoint.h"
#include "traits.h"

using namespace std;

template <typename Tr, typename G>
class Graph {
    public:
        typedef G self;
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
        NodeIte ni;
        EdgeIte ei;

		public:
				Graph () {};
				Graph (int n) {
						while (n--)
								insert_node();
				};
				virtual void insert_node() {
						node *n = new node(this->nodes.size());

						this->nodes[n->get()] = n;
				}
				virtual void insert_node(double x, double y) {
						node *n = new node(this->nodes.size(), x, y);

						this->nodes[n->get()] = n;
				}
				virtual void insert_edge(N node1, N node2, E weight = 1) {
						new edge(this->nodes.at(node1), this->nodes.at(node2), weight);
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
				void bfs(N n = 0,
					function <void (N, N)> discovery = [] (N source, N discovered) -> void {},
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

												discovery(root.front(), i.first);
										} else {
												visit(root.front(), i.first);
										}

								root.pop();
						}

						delete [] visited;
				};
				void dfs(N n = 0,
					function <void (N, N)> discovery = [] (N source, N discovered) -> void {},
					function <void (N, N)> visit = [] (N source, N visited) -> void {}) {
				  	bool *visited = new bool [nodes.size()]();

				  	visited[n] = true;

				  	dfs_recursive(n, visited, discovery, visit);
				}
				bool bipartite() {
						DisjointSet <N> d;

						for (auto i : nodes)
								d.makeSet(i.first);


						int *color = new int[nodes.size()] ();

						for (auto i : nodes) {
								if (i.first == d.findSet(i.first)->data) {
										bool b = true;

										bfs(i.first,
											[color, &d] (N src, N disc) -> void {
												color[disc] = color[src] == 1 ? 2 : 1;
												d.unionSet(src, src);
								    	},
											[color, &b] (N src, N vst) -> void {
												b = b && color[src] != color[vst];
								    	});

										if (!b) {
												delete [] color;

												return false;
										}
								}
						}

						delete [] color;

						return true;

						// bool b = true;
						// int *color = new int[nodes.size()] ();
						//
						// color[0] = 1;
						//
						// for (auto i : component_heads())
						// bfs(0,
						// 	[color] (N s, N d) -> void {
						// 		color[d] = color[s] == 1 ? 2 : 1;
				    // 	},
						// 	[color, &b] (N s, N v) -> void {
						// 		b = b && color[s] != color[v];
				    // 	});
						//
						// delete [] color;
						//
						// return b;
				};
				bool connected() {
						DisjointSet <N> d;

						for (auto i : nodes)
								d.makeSet(i.first);

						dfs(nodes.begin()->first, [&d] (N src, N disc) -> void {
								d.unionSet(src, disc);
						});

						auto i = nodes.begin();

						for (++i; i != nodes.end(); ++i)
								if (i->first == d.findSet(i->first)->data)
										return false;

						return true;
				};
				vector <N> component_heads() {
						DisjointSet <N> d;

						for (auto i : nodes)
								d.makeSet(i.first);

						vector <N> result;

						for (auto i : nodes) {
								if (i.first == d.findSet(i.first)->data) {
										result.push_back(i.first);

										dfs(i.first, [&d] (N src, N disc) -> void {
												d.unionSet(src, disc);
										});
								}
						}

						return result;
				};

		private:
				void dfs_recursive(N n, bool *visited,
					function <void (N, N)> discovery = [] (N source, N discovered) -> void {},
					function <void (N, N)> visit = [] (N source, N visited) -> void {}) {
						visited[n] = true;

						for (auto i : nodes[n]->edges) {
								if (!visited[i.first]) {
										discovery(n, i.first);

										dfs_recursive(i.first, visited, discovery, visit);
								} else {
										visit(n, i.first);
								}
						}
				}

		public:
				~Graph() {
						for (ni = nodes.begin(); ni != nodes.end(); ++ni)
								for (ei = ni->second->edges.begin(); ei != ni->second->edges.end(); ++ei)
										if (ni->first < ei->first)
												delete ei->second;


						for (ni = nodes.begin(); ni != nodes.end(); ++ni)
								delete ei->second;
				}
};

#endif
