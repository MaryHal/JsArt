#ifndef _BinaryHeap_h_
#define _BinaryHeap_h_

#include <cstddef>

#define LEFT(x) (2*(x) + 1)
#define RIGHT(x) (2*(x) + 2)
#define PARENT(x) ((x) / 2)

template <class T>
class BinaryHeap
{
    private:
    T* data;
    size_t size;
    size_t capacity;

    int (*cmp)(const T& a, const T& b);

    public:
    BinaryHeap(int (*compare)(const T& a, const T& b), size_t cap)
        : data(NULL), size(0), capacity(cap), cmp(compare)
    {
        data = new T[capacity];
    }

    ~BinaryHeap()
    {
        delete [] data;
    }

    size_t getSize() const
    {
        return size;
    }

    size_t getCapacity() const
    {
        return capacity;
    }

    void add(const T* element)
    {
        if (!element)
            return;
        int hole = ++size;
        percolateUp(hole, element);
    }

    T* remove()
    {
        if (size < 1)
            return NULL;

        T* element = data[1];
        data[1] = data[size--];
        percolateDown(1);

        return element;
    }

    void percolateDown(int hole)
    {
        int child;
        T* tmp = data[hole];

        for(; hole * 2 <= size; hole = child)
        {
            child = hole * 2;
            if(child != size &&
               cmp(data[child + 1], data[child] ) < 0)
            {
                child++;
            }
            if(cmp(data[child], tmp) < 0)
            {
                swap(hole, child);
            }
            else
                break;
        }
        data[hole] = tmp;
    }

    void percolateUp(int hole, const T* element)
    {
        data[0] = data;

        for(; cmp(element, data[hole/2]) < 0; hole /= 2)
        {
            swap(hole, hole/2);
        }
        data[hole] = element;
    }

    void swap(int first, int second)
    {
        T temp = data[first];
        data[first] = data[second];
        data[second] = temp;
    }

    int findIndex(const T* data) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (data[i] == data)
                return i;
        }
        return size;
    }
};

#endif

