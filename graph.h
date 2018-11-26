#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <limits>
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

        typedef typename Tr::N N;
        typedef map<N,node*> NodeSeq;
        typedef map<N,edge*> EdgeSeq;

        typedef typename Tr::E E;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;

    private:
        NodeSeq nodes;
				EdgeSeq edges;
        NodeIte ni;
        EdgeIte ei;

		public:
			void insert_node(N node1){
				node *n=new node(node1);
				nodes[n->get()] = n;
			}
				void insert_node(double x, double y) {
						node *n = new node(x, y);

						nodes[n->get()] = n;
				}
				void insert_edge(N node1, N node2, E weight, bool direction) {
						edge *e = new edge(nodes.at(node1), nodes.at(node2), weight, direction);
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
														 << ei->second->get_data() << ' '
														 << ei->second->direction() << endl;
								}

						cout << endl;
				}


				// void aStar(N ninit, N nfin){
				// 	map<N, N> came_from;
				// 	map<N, E> cost_so_far;
				// 	priority_queue<N,E> fronti;
				// 	fronti.push(ninit,0);
				// 	came_from[ninit]=ninit;
				// 	cost_so_far[ninit]=0;
				// 	while (!fronti.empty()) {
				// 		N current=fronti.get();
				// 		if (current==nfin){
				// 			break;
				// 		}
				// 		for (ei = nodes[current]->edges.begin(); ei != nodes[current]->edges.end(); ++ei){
				// 			E new_cost= cost_so_far[current] + ei->second->get_data();
				// 			if(cost_so_far.find(ei->second->nodes[1]->get())==cost_so_far.end() || new_cost < cost_so_far[ei->second->nodes[1]->get()]){
				// 				cost_so_far[ei->second->nodes[1]->get()] = new_cost;
				//         E priority = new_cost + ei->second->nodes[1]->heuristica();
				// 				fronti.push(ei->second->nodes[1]->get(),priority);
				// 				came_from[ei->second->nodes[1]->get()]=current;
				// 			}
				// 		}
				// 	}
				// 	for(int i=0;i<fronti.size();i++){
				// 		cout<<fronti[i]<<" ";
				// 	}
				// }

				void greedy_bfs(N ni, N nf) {
						set <N, int> root;
						set <N> close;
						bool *visited = new bool [nodes.size()]();
						N actual;

						root.insert(ni, ni.heuristica());
						actual=root.begin();
						visited[ni] = true;

						while (!root.empty() || actual!=nf) {
								root.erase(root.begin());
								close.insert(actual);
								for (auto i : nodes[actual]->edges)
										if (!visited[i.first]) {
												visited[i.first] = true;
												root.insert(i.first, i.first.heuristica());
											}
								actual=root.begin();
						}

						delete [] visited;
				};


				~Graph() {
						for (ni = nodes.begin(); ni != nodes.end(); ++ni)
								delete ni->second;


						for (ei = edges.begin(); ei != edges.end(); ++ei)
								delete ei->second;
				}
};

typedef Graph<Traits> graph;

#endif
