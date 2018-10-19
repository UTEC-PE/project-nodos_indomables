#ifndef READ_H
#define READ_H

#include <fstream>

#include "graph.h"
#include "undirected_graph.h"
#include "directed_graph.h"

using namespace std;

/**
 * Clase de ayuda para leer el grafo desde un archivo,
 * no es necesario que la utilicen, podrían implementar su lector
 * desde su grafo o algún otro lado
 **/
template <typename G>
class Read {
		public:
				typedef typename G::N N;
				typedef typename G::E E;

		private:
				G *g;

		public:
				Read(char* file) {
						fstream input(file, fstream::in);

						int n, dir;

						input >> n >> dir;

						double x, y;

						if (dir)
								g = new directedGraph();
						else
								g = new undirectedGraph();

						for (int i = 0; i < n; i++) {
								input >> x >> y;

								g->insert_node(x, y);
						}

						N node1, node2;
						E weight;

						while (input >> node1 >> node2 >> weight)
								g->insert_edge(node1, node2, weight);

						input.close();
				};

				auto getGraph() {
						return g;
				}

				~Read() {
						delete g;
				}
};

#endif
