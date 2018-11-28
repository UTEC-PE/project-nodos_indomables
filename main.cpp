#include <iostream>
#include <fstream>
#include <set>
#include <boost/heap/fibonacci_heap.hpp>
#include <math.h>

// Buscar graficador Cinder

#include "read.h"
#include "undirected_graph.h"

using namespace std;

struct node {
  int *val;

  node(int *i) : val(i) {};
};

struct compare {
  bool operator()(const node& n1, const node& n2) const {
    return *n1.val > *n2.val;
  }
};

int main(int argc, char *argv[]) {
  Read<undirectedGraph> r("graph4.txt");
  auto g(r.getGraph());

  g.printNodes();

  cout << endl;

  g.printEdges();

  g.dijkstra(0);

  undirectedGraph h(g);

  h.printNodes();

  h.printEdges();

  // undirectedGraph h(g->weight());
  //
  // g->dfs(0, [&] (Traits::N n0, Traits::N n1) -> void {
  //   cout << n1 << ' ';
  // });
  //
  // cout << endl;
  //
  // undirectedGraph h(*g);
  //
  // h.print_nodes();
  // h.print_edges();

  // g->dfs(0, [&h] (Traits::N n0, Traits::N n1) -> void {
  //     cout << "Discovered: " << n1 << endl;
  // }, [] (Traits::N n0, Traits::N n1) -> void {
  //     cout << "Visited: " << n1 << endl;
  // });

  // h.print_edges();

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
