#ifndef TRAITS
#define TRAITS

class Traits {
	public:
		typedef int N;
		typedef int E;
};

template <typename T>
struct fibonacci_heap_node {
  T *val;

  fibonacci_heap_node (T *init) : val(init) {};
};

template <typename T>
struct compare_node {
  bool operator()(const fibonacci_heap_node<T>& n1, const fibonacci_heap_node<T>& n2) const {
    return *n1.val > *n2.val;
  }
};
#endif
