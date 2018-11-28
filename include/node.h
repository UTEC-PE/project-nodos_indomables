#ifndef NODE_H
#define NODE_H

#include <random>
#include <stdexcept>

template <typename G>
class Node {
  public:
    typedef typename G::N N;
    typedef typename G::E E;
    typedef typename G::edge edge;
    typedef typename G::EdgeSeq EdgeSeq;
    typedef typename G::EdgeIte EdgeIte;

    EdgeSeq edges;
    int d;

  private:
    N data;
    double x;
    double y;


  public:
    Node(N data) : data(data) {
			std::random_device rd;

			this->x = rd() / rd.max();
      this->y = rd() / rd.max();
    };
    Node(N data, double x, double y) : data(data), x(x), y(y) {};
    Node(const Node &node) : data(node.data), x(node.x), y(node.y) {};

    void replace(const double x, const double y) {
      this->x = x;
      this->y = y;
    }
    inline N get() const {
      return this->data;
    }
    inline int degree() const {
      return this->d;
    }
    inline int inDegree() const {
      return this->d - this->edges.size();
    }
    inline int outDegree() const {
      return this->edges.size();
    }

    E operator[](const N node) const {
      EdgeIte nodeIterator = this->edges.find(node);

      if (nodeIterator == this->edges.end()) {
        throw std::range_error("  Edge not found\n");
      }

      return nodeIterator->second->weight();
    }

    inline EdgeIte find(const N node) const {
      return this->edges.find(node);
    }
    inline N heuristica() const {
      return this->x + this->y;
    }
};

#endif
