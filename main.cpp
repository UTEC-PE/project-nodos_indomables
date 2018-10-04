// #include <GL/glut.h>
#include <iostream>
#include <fstream>

#include "read.h"

using namespace std;

int main(int argc, char *argv[]) {
    Read<graph> r("graph1.txt");

    graph *g = r.getGraph();

    g->print_nodes();

    cout << endl;

    g->print_edges();

    cin.get();
    return EXIT_SUCCESS;
}
