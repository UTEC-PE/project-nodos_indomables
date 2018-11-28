#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <limits>
#include <list>
#include <set>

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

				vector <N> aStar(N ni, N nf){
					vector<N> outVector ;
					vector<int>::iterator count;
  				count = outVector.begin();
					set<N> close;
					set<N> open;
					map<N, N> cameFrom;
					map<N, E> gScore;
					map<N, E> fScore;
					open.insert(ni);
					gScore[ni]=0;
					fScore[ni]=nodes[ni]->heuristica();
					while(!open.empty()){
						N current=*open.begin();
						if (current==nf) break;
						open.erase(current);
						close.insert(current);
						for (auto i : nodes[current]->edges){
							if (close.count(i.first)!=0) continue;
							E newCost=gScore[current]+ i.second->get_data();
							if (open.count(i.first)==0) open.insert(i.first);
							else if (newCost>=gScore[i.first]) continue;
							cameFrom[i.first]=current;
							gScore[i.first]=newCost;
							fScore[i.first]=gScore[i.first]+ nodes[i.first]->heuristica();
						}
					}
					for (set<int>::iterator iter=close.begin(); iter!=close.end(); ++iter){
						outVector.insert(count, *iter);
						count = outVector.end();
					}
					count = outVector.end();
					outVector.insert(count, *open.begin());


					return outVector;
				}





				~Graph() {
						for (ni = nodes.begin(); ni != nodes.end(); ++ni)
								delete ni->second;


						for (ei = edges.begin(); ei != edges.end(); ++ei)
								delete ei->second;
				}
};

typedef Graph<Traits> graph;

#endif
