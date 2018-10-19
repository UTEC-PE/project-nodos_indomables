// #include <GL/glut.h>
#include <iostream>
#include <fstream>

#include "read.h"

using namespace std;

int main(int argc, char *argv[]) {
  std::cout << "ok" << '\n';
    Read<graph> r("graph1.txt");

    graph *g = r.getGraph();

    //g->print_nodes();

    //cout << endl;

  //  g->print_edges();
    g->DFS(0);
    cout << endl;
    cin.get();

    return EXIT_SUCCESS;
}
