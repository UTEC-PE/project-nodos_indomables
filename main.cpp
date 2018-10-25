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

    // undirectedGraph *g = new undirectedGraph();
    //
    // g->insert_node();
    // g->insert_node();
    // g->insert_node();
    //
    // g->insert_edge(1, 2);
    // g->insert_edge(1, 0);

    g->print_nodes();

    cout << endl;

    g->print_edges();

    undirectedGraph h(g->weight());

    // void (undirectedGraph::*f1)(undirectedGraph::N node1, undirectedGraph)::N node2);
    // f1 = &undirectedGraph::insert_edge;
    //
    //
    cout << g->bipartite() << endl;
    //
    // cout << "Kruskal" << endl;
    // g->kruskal(&h);
    // cout << "End Kruskal" << endl;
    //
    // g->print_edges();

    // DisjointSet<int> d;

    // int n = 10;

    // while (n--)
    //     d.makeSet(n);

    // d.unionSet(1, 3);
    // d.unionSet(2, 4);
    // d.unionSet(3, 4);

    // if (d.findSet(1) == d.findSet(2))
    //     cout << "Same set" << endl;
    // else
    //     cout << "Different set" << endl;

    // cout << d.findSet(1) << endl;


    cin.get();
    return EXIT_SUCCESS;
}
