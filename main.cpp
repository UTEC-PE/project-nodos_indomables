// #include <GL/glut.h>
#include <iostream>
#include <fstream>

#include "read.h"
#include "undirected_graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    Read<graph> r("test.txt");

    auto *g = r.getGraph();

    g->print_nodes();

    cout << endl;

    g->print_edges();

    // g->test_print();

    graph h(g->weight());

    g->bfs(0, &h);

    h.print_nodes();

    cout << endl;

    h.print_edges();

    cin.get();
    return EXIT_SUCCESS;
}
