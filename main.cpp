#include <iostream>
#include <fstream>
#include <vector>

// Buscar graficador Cinder

#include "read.h"
#include "undirected_graph.h"
#include "disjoint.h"


template <typename N>
void func(N base, N discovered) {
    cout << "base: " << base << " discovered: " << discovered << "!" << endl;
}

using namespace std;

int main(int argc, char *argv[]) {
    Read<undirectedGraph> r("test.txt");

    auto g = r.getGraph();

    g->print_nodes();

    cout << endl;

    g->print_edges();

    undirectedGraph h(g->weight());

    g->kruskal([&h] (Traits::N n0, Traits::N n1) -> void {
        cout << n0 << ' ' << n1 << endl;
    });

    cin.get();
    return EXIT_SUCCESS;
}
