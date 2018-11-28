#ifndef U_GRAPH
#define U_GRAPH

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "traits.h"

template <typename Tr>
class UndirectedGraph : public Graph <Tr, UndirectedGraph<Tr>> {
  public:
    typedef UndirectedGraph<Tr> self;
    typedef Graph<Tr, UndirectedGraph<Tr>> father;
    typedef Node<self> node;
    typedef Edge<self> edge;

    typedef typename Tr::N N;
    typedef std::map<N,node*> NodeSeq;
    typedef std::map<N,edge*> EdgeSeq;

    typedef typename Tr::E E;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;

    struct EdgeConstructor {
  		void operator() (edge *e, node *node1, node *node2) {
        node1->edges[node2->get()] = e;
        node2->edges[node1->get()] = e;
  		}
    };

    struct edgeGreater {
      bool operator() (edge *e1, edge *e2) {
        return e1->weight() > e2->weight();
      }
    };

    struct nodeGreater {
      bool operator() (node *n1, node *n2) {
        return n1->get() > n2->get();
      }
    };


    UndirectedGraph() {};
    UndirectedGraph(int n) {
			while (n--) {
				this->insertNode();
      }
    }
    UndirectedGraph(const self& g) : UndirectedGraph(g.weight()) {
      for (auto n : g.nodes) {
        for (auto e : n.second->edges) {
          this->insertEdge(n.first, e.first, e.second->weight());
        }
      }
    }

    void kruskal(std::function <void (N, N)> newEdge = [] (N node0, N node1) -> void {}) {
			DisjointSet <N> d;

      vector <edge *> sortedEdges;

			for (auto i : this->nodes) {
				d.makeSet(i.first);

        for (auto j : i.second->edges)
          if (i.first < j.first)
            sortedEdges.push_back(j.second);
      }

      sort(sortedEdges.begin(), sortedEdges.end(), [] (edge *edge1, edge *edge2) -> bool {
          return edge1->weight() < edge2->weight();
      });

      for (auto i : sortedEdges) {
        N n0 = i->nodes[0]->get(), n1 = i->nodes[1]->get();

        if (d.findSet(n0) != d.findSet(n1)) {
          d.unionSet(n0, n1);

          newEdge(n0, n1);
        }
      }
    };
    void prim(std::function <void (N, N)> newEdge = [] (N node0, N node1) -> void {}) {
      typedef std::set <node *, nodeGreater> nodeSet;

      std::priority_queue<edge *, std::vector<edge *>, edgeGreater> sortedEdges;
      nodeSet visited;

      visited.insert(this->nodes.begin()->second);
      // cout << (visited.find(2) == visited.end()) << endl;

			for (typename nodeSet::iterator i = visited.begin(); i != visited.end(); ++i) {
        for (auto j : (*i)->edges) {
          if (visited.find(this->nodes[j.first]) == visited.end()) {
            sortedEdges.push(j.second);
          }
        }

        edge *tmp;
        node *next;

        do {
          tmp = sortedEdges.top();
          sortedEdges.pop();
        } while (visited.find(next = tmp->nodes[tmp->nodes[0] == *i ? 1 : 0]) != visited.end());

        visited.insert(next);

        cout << "DONE " << visited.size() << endl;

        newEdge(tmp->nodes[0]->get(), tmp->nodes[1]->get());
      }
    };

    virtual ~UndirectedGraph() {
			for (auto i : this->nodes)
				for (auto j : i.second->edges)
					if (i.first < j.first)
						delete j.second;

			for (auto i : this->nodes)
				delete i.second;
		}
};

typedef UndirectedGraph<Traits> undirectedGraph;

#endif
