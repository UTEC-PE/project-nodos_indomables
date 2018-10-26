#include <iostream>
#include <fstream>

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

    // cout << g->connected() << endl;

    undirectedGraph h(g->weight());

    g->dfs(0, [&h] (Traits::N source, Traits::N discovered) -> void {
        h.insert_edge(source, discovered);
    });

    h.print_edges();

    cin.get();
    return EXIT_SUCCESS;
}
