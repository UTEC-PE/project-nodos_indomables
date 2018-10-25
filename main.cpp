// #include <GL/glut.h>
#include <iostream>
#include <fstream>

#include "read.h"

using namespace std;

int main(int argc, char *argv[]) {
    Read<graph> r("graph1.txt");

    graph *g = r.getGraph();
    graph h;
    //g->print_nodes();

    //cout << endl;

    // g->print_edges();
    g->DFS(6, &h);
    h.print_nodes();
    h.print_edges();
    cout << endl;
    cin.get();

    return EXIT_SUCCESS;
}
