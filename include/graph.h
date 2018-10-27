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
        typedef map<N, node*> NodeSeq;
        typedef map<N, edge*> EdgeSeq;

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
				void insert_node() {
						node *n = new node(this->nodes.size());

						this->nodes[n->get()] = n;
				}
				void insert_node(double x, double y) {
						node *n = new node(this->nodes.size(), x, y);

						this->nodes[n->get()] = n;
				}
				void insert_edge(N node1, N node2, E weight = 1) {
						new edge(this->nodes.at(node1), this->nodes.at(node2), weight);
				}
				void print_nodes() {
						for (auto i : nodes)
								cout << i.second->get() << ' ';

						cout << endl;
				}
				void print_edges() {
						for (auto i : nodes)
								for (auto j : i.second->edges)
										if (i.first < j.first)
												cout << i.first << ' ' << j.first << ' ' << j.second->get_data() << endl;

						cout << endl;
				}
				inline int weight() {
						return nodes.size();
				}
				inline int degree(N n) {
						return nodes[n]->degree();
				};
				void bfs(N n = 0,
					function <void (N, N)> discoveredVertex = [] (N source, N discovered) -> void {},
					function <void (N, N)> visitedVertex = [] (N source, N visited) -> void {}) {
						queue <N> root;
						bool *visited = new bool [nodes.size()]();

						root.push(n);
						visited[n] = true;

						while (!root.empty()) {
								for (auto i : nodes[root.front()]->edges)
										if (!visited[i.first]) {
												visited[i.first] = true;
												root.push(i.first);

												discoveredVertex(root.front(), i.first);
										} else {
												visitedVertex(root.front(), i.first);
										}

								root.pop();
						}

						delete [] visited;
				};
				void dfs(N n = 0,
					function <void (N, N)> discoverVertex = [] (N source, N discovered) -> void {},
					function <void (N, N)> visitedVertex = [] (N source, N visited) -> void {},
					function <void (N)> postVisitVertex = [] (N source) -> void {}) {
				  	bool *visited = new bool [nodes.size()]();

				  	visited[n] = true;

				  	dfs_recursive(n, visited, discoverVertex, visitedVertex, postVisitVertex);
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
				};
				bool connected() {
						int v = 1;

						dfs(nodes.begin()->first, [&v] (N src, N disc) -> void {
								v++;
						});

						return v == nodes.size();
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
					function <void (N, N)> discoverVertex = [] (N source, N discovered) -> void {},
					function <void (N, N)> visitedVertex = [] (N source, N visited) -> void {},
					function <void (N)> postVisitVertex = [] (N source) -> void {}) {
						visited[n] = true;

						for (auto i : nodes[n]->edges) {
								if (!visited[i.first]) {
										discoverVertex(n, i.first);

										dfs_recursive(i.first, visited, discoverVertex, visitedVertex, postVisitVertex);
								} else {
										visitedVertex(n, i.first);
								}
						}

						postVisitVertex(n);
				}
};

#endif
