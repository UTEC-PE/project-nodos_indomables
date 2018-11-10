#include <iostream>
#include <fstream>
#include <set>

// Buscar graficador Cinder

#include "read.h"
#include "undirected_graph.h"
#include "disjoint.h"

using namespace std;

int main(int argc, char *argv[]) {
    Read<undirectedGraph> r("graph3.txt");
    auto g = r.getGraph();

    g->print_nodes();

    cout << endl;

    g->print_edges();

    undirectedGraph h(g->weight());

    g->dfs(0, [&h] (Traits::N n0, Traits::N n1) -> void {
        cout << n1 << ' ';
    });

    // g->dfs(0, [&h] (Traits::N n0, Traits::N n1) -> void {
    //     cout << "Discovered: " << n1 << endl;
    // }, [] (Traits::N n0, Traits::N n1) -> void {
    //     cout << "Visited: " << n1 << endl;
    // });

    h.print_edges();

    cin.get();

    // set <int> s;
    //
    // for (int i = 0; i < 10; i++)
    //     s.insert(i);
    //
    // for (auto i : s) {
    //     cout << i << endl;
    // }

    return EXIT_SUCCESS;
}
