// #include <GL/glut.h>
#include <iostream>
#include <fstream>

#include "read.h"
#include "undirected_graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    Read<graph> r("graph1.txt");

    graph *g = r.getGraph();

    g->print_nodes();

    cout << endl;

    g->print_edges();

    // g->test_print();

    cin.get();
    return EXIT_SUCCESS;
}
