#include <iostream>
#include <fstream>

// Buscar graficador Cinder

#include "read.h"
#include "undirected_graph.h"
#include "disjoint.h"

using namespace std;

int main(int argc, char *argv[]) {
    Read<undirectedGraph> r("test.txt");

    undirectedGraph *g = r.getGraph();

    g->print_nodes();

    cout << endl;

    g->print_edges();

    undirectedGraph h(g->weight());

    g->kruskal([&h, &g] (Traits::N n0, Traits::N n1) -> void {
        h.insert_edge(n0, n1);
    });

    h.print_edges();


    cin.get();
    return EXIT_SUCCESS;
}
