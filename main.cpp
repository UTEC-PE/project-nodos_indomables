// #include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <map>

#include "read.h"

using namespace std;

int main(int argc, char *argv[]) {
    Read<graph> r("graph1.txt");

    graph *g = r.getGraph();
    g->aStar(3, 5);

    //graph h;
    // g->PRIM(5, &h);
    // h.print_nodes();
    //h.print_edges();
    cout << endl;
    cin.get();

    return EXIT_SUCCESS;
}
