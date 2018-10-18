#ifndef READ_H
#define READ_H

#include <fstream>

#include "graph.h"

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
				graph *g;

		public:
				Read(char* file) {
						fstream input(file, fstream::in);

						g = new G;

						int n;

						input >> n;

						double x, y;

						for (int i = 0; i < n; i++) {
								input >> x >> y;

								g->insert_node(x, y);
						}

						N node1, node2;
						E weight;
						bool directed;

						while (input >> node1 >> node2 >> weight >> directed)
								g->insert_edge(node1, node2, weight, directed);

						input.close();
				};

				graph *getGraph() {
						return g;
				}

				~Read() {
						delete g;
				}
};

#endif
