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

    cout << g->bipartite() << endl;

    // vector <Traits::N> result = g->component_heads();
    //
    // for (auto i : result)
    //     cout << i << endl;

    cin.get();
    return EXIT_SUCCESS;
}
