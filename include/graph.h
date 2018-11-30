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

    struct Scan {
      void operator()(N firstNode, N secondNode...) {
        std::cout << firstNode << " -- " << secondNode << std::endl;
      }

      void operator()(N firstNode...) {
        std::cout << firstNode << std::endl;
      }
    };
    struct Ignore {
      void operator()(...) {};
    };

    struct Print {
      typedef Scan Initiate;
      typedef Scan Discover;
      typedef Ignore Visit;
      typedef Ignore Leave;
    };


    template <typename I = Ignore,
              typename D = Ignore,
              typename V = Ignore,
              typename L = Ignore>
    struct Default {
      typedef I Initiate;
      typedef D Discover;
      typedef V Visit;
      typedef L Leave;
    };

    template <typename Method = Print, typename... Types>
    struct Search {
      typedef typename std::tuple<Types...> TypeContainer;
      typedef typename Method::Initiate Initiate;
      typedef typename Method::Discover Discover;
      typedef typename Method::Visit Visit;
      typedef typename Method::Leave Leave;

      TypeContainer data;
      Initiate initiate_;
      Discover discover_;
      Visit visit_;
      Leave leave_;

      Search(Types... args) : data(args...) {};

      void initiate(N firstNode) {
        initiate_(firstNode, this->data);
      }
      void discover(N firstNode, N secondNode) {
        discover_(firstNode, secondNode, this->data);
      }
      void visit(N firstNode, N secondNode) {
        visit_(firstNode, secondNode, this->data);
      }
      void leave(N firstNode) {
        leave_(firstNode, this->data);
      }

      TypeContainer get() const {
        return data;
      }
      auto get(const int n) const {
        return std::get<n>(data);
      }
    };


	protected:
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

    void bfs(N n = 0) {
      this->bfs<Print>(n);
    }
    template <typename Method = Default<>, typename... Types>
		void bfs(N n = 0,
             Search<Method, Types...>&& search = Search<Method, Types...>()) {
			std::queue <N> root;
			bool *visited = new bool [this->weight()]();

			root.push(n);
			visited[n] = true;


      search.initiate(n);

			while (!root.empty()) {
				for (auto currentNode : this->nodes[root.front()]->edges) {
					if (!visited[currentNode.first]) {
						visited[currentNode.first] = true;
						root.push(currentNode.first);

            search.discover(currentNode.first,root.front());
					} else {
            search.visit(currentNode.first, root.front());
					}
        }

        search.leave(root.front());

				root.pop();
			}

			delete [] visited;
		};
    void dfs(N n = 0) {
      this->dfs<Print>(n);
    }
    template <typename Method = Default<>, typename... Types>
		void dfs(N n = 0,
             Search<Method, Types...>&& search = Search<Method, Types...>()) {
      std::stack <N> root;
      std::stack <EdgeIte> iterators;
	  	bool *visited = new bool [this->weight()]();

      root.push(n);
      iterators.push(this->nodes[n]->edges.begin());
      visited[n] = true;

      search.initiate(n);

      while (!root.empty()) {
        EdgeIte end = this->nodes[root.top()]->edges.end();

        while (iterators.top() != end && visited[iterators.top()->first]) {
          search.visit(iterators.top()->first, root.top());

          ++iterators.top();
        }

        if (iterators.top() != end) {
          visited[iterators.top()->first] = true;

          search.discover(iterators.top()->first, root.top());

          root.push(iterators.top()->first);
          iterators.push(this->nodes[root.top()]->edges.begin());
        } else {
          search.leave(root.top());

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
    std::vector <N> aStar(N initialNode, N finalNode) {
      std::map<N, E> gScore, fScore;
      std::map<N, N> cameFrom;

      std::vector<N> outVector;
      std::vector<int>::iterator count = outVector.begin();

      std::set<N> close, open;


      open.insert(initialNode);
      gScore[initialNode] = 0;
      fScore[initialNode] = this->nodes[initialNode]->heuristica();


      while (!open.empty()) {
        N current = *open.begin();

        if (current == finalNode) break;

        open.erase(current);
        close.insert(current);

        for (auto currentEdge : this->nodes[current]->edges) {
          if (close.count(currentEdge.first)) continue;

          E newCost = gScore[current] + currentEdge.second->weight();

          if (!open.count(currentEdge.first)) {
            open.insert(currentEdge.first);
          } else if (newCost >= gScore[currentEdge.first]) continue;

          cameFrom[currentEdge.first] = current;
          gScore[currentEdge.first] = newCost;
          fScore[currentEdge.first] = newCost
                                    + this->nodes[currentEdge.first]->heuristica();
        }
      }

      for (std::set<int>::iterator iter = close.begin();
           iter != close.end(); ++iter) {
        outVector.insert(outVector.end(), *iter);
        count = outVector.end();
      }

      count = outVector.end();
      outVector.insert(count, *open.begin());

      return outVector;
    }
    std::vector <N> greedyBfs(N initialNode, N finalNode) {
			std::vector <N> outVector;
			std::vector<int>::iterator count = outVector.begin();

			std::map <E, N> root;

      std::vector<bool> visited(this->weight(), false);
			N currentNode = root[nodes[initialNode]->heuristica()] = initialNode;

			visited[initialNode] = true;

			while (!root.empty() && currentNode != finalNode) {
				root.clear();

				for (auto i : nodes[currentNode]->edges) {
					if (!visited[i.first]) {
						visited[i.first] = true;
						root.insert(i.second->nodes[1]->heuristica(), i.first);
					}
				}

				currentNode = root.begin()->second;
				outVector.insert(count, currentNode);
				count = outVector.begin();
			}

			return outVector;
		};

    self operator= (self g) {
      return this->g(g);
    }

		std::string toOutputStream() const {
      int maxNodeLength = 0;

      for (auto node : this->nodes) {
        int currentLength = std::to_string(node.first).length();

        if (currentLength > maxNodeLength) {
          maxNodeLength = currentLength;
        }
      }


      std::string table;
      int maxLineLength = 0;

      for (auto currentNode : this->nodes) {
        std::string currentString = std::to_string(currentNode.first),
                    currentLine;

        currentLine.append(std::string(maxNodeLength - currentString.length(), ' ') +
                   currentString +
                   " |");

        for (auto neighborNode : currentNode.second->edges) {
          currentLine.append(" " + std::to_string(neighborNode.first));
        }

        int currentLineLength = currentLine.length();

        if (currentLineLength > maxLineLength) {
          maxLineLength = currentLineLength;
        }

        table.append(currentLine + "\n");
      }

	    std::string output;

	    output.append("\n********* Output *********\n\nAdjacency List\n" +
                    std::string(maxLineLength, '-') + "\n" +
                    table +
                    std::string(maxLineLength, '-') +
                    "\n\n**** Finished printing ****\n");

	    return output;
	  }
		friend std::ostream &operator<<(std::ostream &os, const self &g) {
	    std::string s = g.toOutputStream();
	    os << s;
	    return os;
	  }
};

#endif
