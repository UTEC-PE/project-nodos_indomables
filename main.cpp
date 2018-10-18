//#include <GL/glut.h>
#include <iostream>
#include <fstream>

#include "read.h"
#include "node.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout<<"ok"<<endl;
	Read<graph> r("graph1.txt");

	graph *g = r.getGraph();
//	graph *h= new graph();

	g->print_nodes();

	cout << endl;

	g->print_edges();

	//g->DFS();
	//h->print_edges();
	cin.get();
	return EXIT_SUCCESS;
}
