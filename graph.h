#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
//#include <list>
#include <map>
#include <stack>

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
	typedef typename Tr::E E;
	typedef map<N,node*> NodeSeq;
	typedef map<N,edge*> EdgeSeq;

	typedef typename NodeSeq::iterator NodeIte;
	typedef typename EdgeSeq::iterator EdgeIte;

private:
	NodeSeq nodes;
	EdgeSeq edges;
	NodeIte ni;
	EdgeIte ei;

public:
	void insert_node(double x, double y) {
		node *n = new node(x, y);

		nodes[n->get()]=n;
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

	// void delete_nodo(N node1) {
	//
	// }

	// vector<bool> visited;
	// void DFS_used(N node1){
	// 	visited[node1]=true;
	// 	stack.push(node1);
	// 	for (ei=edges.begin();ei!=edges.end();++ei){
	// 		if (visited[ei]==false) {
	// 			cout << ni->second->get() << ' ';
	// 			DFS_used(ei);
	// 		}
	// 	}
	//
	// }

	void DFS(N node1){
		stack <int> pila;
		vector <bool> visited;
		pila.push(node1);
		visited[node1]=true;
		while (pila!=NULL){
			
		}
		for (ni=node1; ni!=nodes.end();++ni){
			cout << ni->second->get() << ' ';
		}
	}

	void PRIM(N node) {

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
