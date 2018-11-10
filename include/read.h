#ifndef READ_H
#define READ_H

#include <fstream>

#include "graph.h"
#include "undirected_graph.h"
#include "directed_graph.h"

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
				Read(string file) {
						std::fstream input(file, std::fstream::in);

						int n;

						input >> n;

						this->g = new G();

						double x, y;

						for (int i = 0; i < n; i++) {
								input >> x >> y;

								this->g->insert_node(x, y);
						}

						N node1, node2;
						E weight;

						while (input >> node1 >> node2 >> weight)
								this->g->insert_edge(node1, node2, weight);

						input.close();
				};

				auto getGraph() {
						return this->g;
				}

				~Read() {
						delete this->g;
				}
};

#endif
