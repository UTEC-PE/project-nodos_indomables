#ifndef D_GRAPH
#define D_GRAPH

#include <iostream>

#include "graph.h"

template <typename Tr>
class DirectedGraph : public Graph <Tr, DirectedGraph<Tr>> {
    public:
        typedef DirectedGraph<Tr> self;
        typedef Node<self> node;
        typedef Edge<self> edge;

        typedef typename Tr::N N;
        typedef std::map<N,node*> NodeSeq;
        typedef std::map<N,edge*> EdgeSeq;

        typedef typename Tr::E E;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

        struct EdgeConstructor {
      		void operator() (edge *e, node *node1, node *node2) {
            node1->edges[node2->get()] = e;
      		}
        };


        DirectedGraph() {};
        DirectedGraph(int n) {
          while (n--) {
    				this->insertNode();
          }
        };
        DirectedGraph(const self& g) : DirectedGraph(g.weight()) {
          for (auto n : g.nodes) {
            for (auto e : n.second->edges) {
              this->insertEdge(n.first, e.first, e.second->weight());
            }
          }
        }

        inline int inDegree(N n) {
            return this->nodes[n]->inDegree();
        };
        inline int outDegree(N n) {
            return this->nodes[n]->outDegree();
        };
        inline bool source(N n) {
            return !this->nodes[n]->inDegree();
        };
        inline bool sink(N n) {
            return !this->nodes[n]->outDegree();
        };
        void reverse(self *g) {
          for (auto i : this->nodes)
            g->insertNode();

          for (auto i : this->nodes)
            for (auto j : i.second->edges)
              g->insertEdge(j.first, i.first);
        }
        bool strongly_connected() {
            std::stack <N> route;
						bool *visited = new bool[this->weight()] ();

						for (auto i : this->nodes) {
								if (!visited[i.first]) {
                    visited[i.first] = true;

										this->dfs(i.first,
											[visited] (N src, N disc) -> void {
                        visited[disc] = true;
                      },
											[] (N src, N vst) -> void {},
                      [&route] (N node) -> void {
                        route.push(node);
								    	});
								}
						}


            self g;
            this->reverse(&g);

            delete [] visited;
            visited = new bool[this->weight()] ();

            vector <vector <N>> result;

            while (!route.empty()) {
              if (!visited[route.top()]) {
                visited[route.top()] = true;
                cout << route.top() << ' ';

								g.dfs(route.top(), [&] (N src, N disc) -> void {
                    if (!visited[disc]) {
                        visited[disc] = true;
                        cout << disc << ' ';
                    }
                });

                cout << endl;
              }

              route.pop();
            }


            delete [] visited;

            return false;
        };
    		void print_edges() {
    			for (auto i : this->nodes) {
    				for (auto j : i.second->edges) {
  						std::cout << i.first << ' ' << j.first << ' ' << j.second->weight() << std::endl;
            }
          }

    			std::cout << std::endl;
    		}

        ~DirectedGraph() {
          for (auto i : this->nodes) {
            for (auto j : i.second->edges) {
              delete j.second;
            }
          }

          for (auto i : this->nodes) {
            delete i.second;
          }
        }
};

typedef DirectedGraph<Traits> directedGraph;

#endif
