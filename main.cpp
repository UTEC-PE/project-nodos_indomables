//#include <GL/glut.h>
#include <iostream>
#include <fstream>

#include "read.h"
#include "node.h"

using namespace std;

int main(int argc, char *argv[]) {
	Read<graph> r("graph1.txt");

	graph *g = r.getGraph();

	g->print_nodes();

	cout << endl;

	g->print_edges();

	g->DFS(g->nodes);
	cin.get();
	return EXIT_SUCCESS;
}
