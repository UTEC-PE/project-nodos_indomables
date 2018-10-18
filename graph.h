#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
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
	list<N>*adj;
	void insert_node(double x, double y) {
		node *n = new node(x, y);

		nodes[n->get()]=n;
	}
	void insert_edge(N node1, N node2, E weight, bool direction) {
		edge *e = new edge(nodes.at(node1), nodes.at(node2), weight, direction);
		adj[node1].push_back(node2);
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
	// 
	// void DFS(){
	// 	cout<<"ok";
	// 	N node1=nodes.begin()->first;
	// 	stack <N> stack;
	// 	bool *visited=new bool[nodes.size()]();
	// 	stack.push(node1);
	// 	while (!stack.empty()){
	// 		node1=stack.top();
	// 		if (!visited[node1]){
	// 			cout << node1 << ' ';
	// 			visited[node1]=true;
	// 		}
	// 		for(ei=nodes[node1]->edges.begin();ei!=nodes[node1]->edges.end();++ei)
	// 			if (!visited[ei->second->get_data()])
	// 				stack.push(ei->second->get_data());
	// 		stack.pop();
	// 	}
	// }
	//
	// void PRIM(N node1) {
	//
	// }

	~Graph() {
		for (ni = nodes.begin(); ni != nodes.end(); ++ni)
			delete ni->second;


		for (ei = edges.begin(); ei != edges.end(); ++ei)
			delete ei->second;
	}
};

typedef Graph<Traits> graph;

#endif
