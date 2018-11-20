#ifndef D_GRAPH
#define D_GRAPH

#include <iostream>

#include "graph.h"

// struct DirectedNodeConstructor;

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
        DirectedGraph(int n) : Graph <Tr, DirectedGraph<Tr>> (n) {};
        DirectedGraph(self& g) : Graph <Tr, self> (g) {}

        inline int in_degree(N n) {
            return this->nodes[n]->in_degree();
        };
        inline int out_degree(N n) {
            return this->nodes[n]->out_degree();
        };
        inline bool source(N n) {
            return !this->nodes[n]->in_degree();
        };
        inline bool sink(N n) {
            return !this->nodes[n]->out_degree();
        };
        void reverse(self *g) {
            for (auto i : this->nodes)
                g->insert_node();

            for (auto i : this->nodes)
                for (auto j : i.second->edges)
                    g->insert_edge(j.first, i.first);
        }
        bool strongly_connected() {
            std::stack <N> route;
						bool *visited = new bool[this->nodes.size()] ();

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
            visited = new bool[this->nodes.size()] ();

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

        ~DirectedGraph() {
            for (auto i : this->nodes)
                for (auto j : i.second->edges)
                    delete j.second;

            for (auto i : this->nodes)
                delete i.second;
        }
};

// struct DirectedNodeConstructor {
// 		typedef DirectedGraph<Traits> G;
// 		typedef typename G::node node;
// 		typedef typename G::edge edge;
//
// 		void operator() (edge *e, node *node1, node *node2) {
//         node1->edges[node2->get()] = e;
// 		}
// };

typedef DirectedGraph<Traits> directedGraph;

#endif
