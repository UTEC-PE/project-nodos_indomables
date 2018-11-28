// #include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <map>

#include "read.h"

using namespace std;

int main(int argc, char *argv[]) {
    Read<graph> r("graph1.txt");
    vector<int> v;
    graph *g = r.getGraph();
    v=g->aStar(0,1);
    for (vector<int>::iterator it = v.begin() ; it != v.end(); ++it)
    cout << ' ' << *it;
    // graph h;
    // g->greedy_bfs(0, 5, h);
    //graph h;
    // g->PRIM(5, &h);
    // h.print_nodes();
    //h.print_edges();
    cout << endl;
    cin.get();

    return EXIT_SUCCESS;
}
