#include "graph.h"

bool *visited;

template <typename Tr>
dfs_recursive(N n,
  function <void (N, N)> discovery = [] (N source, N discovered) -> void {},
  function <void (N, N)> visit = [] (N source, N visited) -> void {}) {
    visited[n] = true;

    for (auto i : nodes[n]->edges) {
        if (!visited[i.first]) {
            discovery(n, i.first);

            dfs_recursive(i.first, h);
        } else {
            visit(n, i.first);
        }
    }
}

template <typename Tr>
void Graph<Tr>::dfs(N n,
  function <void (N, N)> discovery = [] (N source, N discovered) -> void {},
  function <void (N, N)> visit = [] (N source, N visited) -> void {}) {
  	visited = new bool [nodes.size()]();

  	h->insert_node(n);

  	visited[n] = true;

  	dfs_recursive(n, discovery, visit);
}
