#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <ostream>
#include <boost/heap/fibonacci_heap.hpp>

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


	// protected:
    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;

	public:
		Graph () {};
		Graph (int n) {
			while (n--)
				this->insertNode();
		}
    Graph (const self& g) : Graph(g.nodes.size()) {
      for (auto n : g.nodes) {
        for (auto e : n.second->edges) {
          this->insertEdge(n.first, e.first, e.second->weight());
        }
      }
    }

		void insertNode() {
			node *n = new node(this->weight());

			this->nodes[n->get()] = n;
		}
		void insertNode(double x, double y) {
			node *n = new node(this->weight(), x, y);

			this->nodes[n->get()] = n;
		}
		void insertEdge(N node1, N node2, E weight = 1) {
			new edge(this->nodes.at(node1), this->nodes.at(node2), weight);
		}


		inline int weight() const {
			return this->nodes.size();
		}
    inline int degree(N n) const {
			return this->nodes[n]->degree();
		};

		void printNodes() const {
			for (auto currentNode : this->nodes) {
				std::cout << currentNode.second->get() << ' ';
      }

			std::cout << std::endl;
		}
		void printEdges() const {
			for (auto i : this->nodes) {
				for (auto j : i.second->edges) {
					if (i.first < j.first) {
						std::cout << i.first << ' ' << j.first << ' ' << j.second->weight() << std::endl;
          }
        }
      }

			std::cout << std::endl;
		}

		void bfs(N n = 0,
			       std::function <void (N, N)> discoveredVertex = [] (N source, N discovered) -> void {},
			       std::function <void (N, N)> visitedVertex = [] (N source, N visited) -> void {}) {
			std::queue <N> root;
			bool *visited = new bool [this->weight()]();

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
	  	bool *visited = new bool [this->weight()]();

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

			int *color = new int[this->weight()] ();

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

			return v == this->weight();
		};
		std::vector <N> componentHeads() {
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
    std::vector <E> dijkstra(N initialNode) {
      typedef std::pair<N, E> pair;

      struct comparator {
        bool operator()(const pair p1, const pair p2) {
          return p1.second < p2.second;
        }
      };

      std::priority_queue<pair, std::vector<pair>, comparator> minHeap;
      std::vector<bool> visited(this->weight(), false);
      std::vector<E> distance(this->weight(), -1);
      std::vector<N> previous(this->weight(), -1);

      minHeap.push({initialNode, 0});
      visited[initialNode] = true;
      distance[initialNode] = 0;

      int newGrafNumberOfNodes = 0;

      while (!minHeap.empty()) {
        N currentNode;

        do {
          currentNode = minHeap.top().first;
          minHeap.pop();
        } while (visited[currentNode] && !minHeap.empty());

        visited[currentNode] = true;

        for (auto neighborIterator : this->nodes[currentNode]->edges) {
          N neighborNode = neighborIterator.first;

          if (!visited[neighborNode] &&
              (distance[neighborNode] == -1 ||
              distance[currentNode] + neighborIterator.second->weight() < distance[neighborNode])) {
            distance[neighborNode] = distance[currentNode] + neighborIterator.second->weight();
            previous[neighborNode] = currentNode;

            minHeap.push({neighborNode, distance[neighborNode]});
          }
        }

        newGrafNumberOfNodes++;
      }

      return distance;
    }
    std::pair<std::vector<std::vector<E>>,
              std::vector<std::vector<N>>> floydWarshall() {
      std::vector<std::vector<E>> distances(this->weight());
      std::vector<std::vector<N>> sources(this->weight());

      for (int row = 0; row < this->weight(); row++) {
        distances[row].resize(this->weight(), -1);

        for (auto currentEdge : this->nodes[row]->edges) {
          distances[row][currentEdge.first] = currentEdge.second->weight();
        }
      }

      for (int row = 0; row < this->weight(); row++) {
        sources[row].resize(this->weight(), -1);

        for (int column = 0; column < this->weight(); column++) {
          if (row != column) {
            sources[row][column] = column;
          } else {
            distances[row][column] = 0;
          }
        }
      }

      for (int iteration = 0; iteration < this->weight(); iteration++) {
        for (int row = 0; row < this->weight(); row++) {
          for (int column = 0; column < this->weight(); column++) {
            E rowToIt = distances[row][iteration],
              itToCol = distances[iteration][column],
              rowToCol = distances[row][column];

            if (row != column && (rowToIt != -1 && itToCol != -1 &&
                (rowToCol == -1 || rowToIt + itToCol < rowToCol))) {
              distances[row][column] = rowToIt + itToCol;
              sources[row][column] = iteration;
            }
          }
        }
      }

      return {distances, sources};
    }

    self operator= (self g) {
      this->g(g);
    }

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
