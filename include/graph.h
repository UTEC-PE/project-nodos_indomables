#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <ostream>

#include "node.h"
#include "edge.h"
#include "disjoint.h"
#include "traits.h"

template <typename Tr, typename G>
class Graph {
  public:
    typedef G self;
    typedef Node<self> node;
    typedef Edge<self> edge;

    typedef typename Tr::N N;
    typedef std::map<N, node*> NodeSeq;
    typedef std::map<N, edge*> EdgeSeq;

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
				this->insert_node();
		}
    Graph (self& g) : Graph(g.nodes.size()) {
      for (auto n : g.nodes) {
        for (auto e : n.second->edges) {
          insert_edge(n.first, e.first, e.second->get_data());
        }
      }
    }

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
			for (auto i : this->nodes)
				std::cout << i.second->get() << ' ';

			std::cout << std::endl;
		}
		void print_edges() {
			for (auto i : this->nodes)
				for (auto j : i.second->edges)
					if (i.first < j.first)
						std::cout << i.first << ' ' << j.first << ' ' << j.second->get_data() << std::endl;

			std::cout << std::endl;
		}
		inline int weight() {
			return this->nodes.size();
		}
		inline int degree(N n) {
			return this->nodes[n]->degree();
		};
		void bfs(N n = 0,
			       std::function <void (N, N)> discoveredVertex = [] (N source, N discovered) -> void {},
			       std::function <void (N, N)> visitedVertex = [] (N source, N visited) -> void {}) {
			std::queue <N> root;
			bool *visited = new bool [this->nodes.size()]();

			root.push(n);
			visited[n] = true;

			while (!root.empty()) {
				for (auto i : this->nodes[root.front()]->edges)
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
             std::function <void (N, N)> discoverVertex = [] (N source, N discovered) -> void {},
			       std::function <void (N, N)> visitedVertex = [] (N source, N visited) -> void {},
			       std::function <void (N)> postVisitVertex = [] (N source) -> void {}) {
      std::stack <N> root;
      std::stack <EdgeIte> iterators;
	  	bool *visited = new bool [this->nodes.size()]();

      root.push(n);
      iterators.push(this->nodes[n]->edges.begin());
      visited[n] = true;

      while (!root.empty()) {
        EdgeIte end = this->nodes[root.top()]->edges.end();

        while (iterators.top() != end && visited[iterators.top()->first]) {
          visitedVertex(root.top(), iterators.top()->first);
          ++iterators.top();
        }

        if (iterators.top() != end) {
          visited[iterators.top()->first] = true;

          discoverVertex(root.top(), iterators.top()->first);

          root.push(iterators.top()->first);
          iterators.push(this->nodes[root.top()]->edges.begin());
        } else {
          root.pop();
          iterators.pop();
        }
      }

			delete [] visited;
		}
		bool bipartite() {
			DisjointSet <N> d;

			for (auto i : this->nodes)
				d.makeSet(i.first);

			int *color = new int[this->nodes.size()] ();

			for (auto i : this->nodes) {
				if (i.first == d.findSet(i.first)->data) {
					bool b = true;

					this->bfs(i.first,
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

			this->dfs(this->nodes.begin()->first, [&v] (N src, N disc) -> void {
				v++;
			});

			return v == this->nodes.size();
		};
		vector <N> component_heads() {
			DisjointSet <N> d;

			for (auto i : this->nodes)
				d.makeSet(i.first);

			std::vector <N> result;

			for (auto i : this->nodes) {
				if (i.first == d.findSet(i.first)->data) {
					result.push_back(i.first);

					dfs(i.first, [&d] (N src, N disc) -> void {
						d.unionSet(src, disc);
					});
				}
			}

			return result;
		};

		// std::string toOutputStream() const {
		//     std::string str;
		//     str.append("\n********* Output *********\n\n");
		//     str.append(std::to_string(this->numberOfStates) + " " +
		//                std::to_string(this->initialState) + " " +
		//                std::to_string(this->finalStates.size()));
		//     for (const state &s : this->finalStates) {
		//       	str.append(" " + std::to_string(s));
		//     }
		//     str.append("\n");
		//     for (int sFrom = 0; sFrom < this->TransitionTable.size(); ++sFrom) {
		//       	str.append(std::to_string(sFrom) + " 0 " +
		//                  std::to_string(this->TransitionTable[sFrom][0]) + "\n");
		//       	str.append(std::to_string(sFrom) + " 1 " +
		//                  std::to_string(this->TransitionTable[sFrom][1]) + "\n");
		//     }
		//     str.append("\n**** Finished printing ****\n");
		//
		//     return str;
	  // }
		// friend std::ostream &operator<<(std::ostream &os, const self &A) {
		//     std::string s = A.toOutputStream();
		//     os << s;
		//     return os;
	  // }
};

#endif
