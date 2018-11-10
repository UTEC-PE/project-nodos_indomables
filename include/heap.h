#ifndef HEAP
#define HEAP

#include <iostream>

using namespace std;

class Heap {
    private:
        int *array;
        size_t size;

    public:
        Heap(int *array, size_t size) : array(array), size(size) {
            for (int i = (size - 1) / 2; i >= 0; i--)
                heapify(i);
        };

        inline int left(int i) {
            return (i << 1) + 1;
        }
        inline int right(int i) {
            return (i << 1) + 2;
        }
        void exchange(int i, int j) {
          int tmp = array[i];
          array[i] = array[j];
          array[j] = tmp;
        }
        void heapify(int i) {
            int l = left(i), r = right(i), largest = i;

            if (l < size && array[l] > array[largest])
                largest = l;

            if (r < size && array[r] > array[largest])
                largest = r;

            if (largest != i) {
                exchange(i, largest);

                heapify(largest);
            }
        };
        void heapsort() {
            for (int i = size - 1; i >= 1; i--) {
                exchange(0, i);

                size--;

                heapify(0);
            }
        }

        ~Heap() {};
};

#endif
