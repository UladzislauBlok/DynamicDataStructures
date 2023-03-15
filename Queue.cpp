#include <iostream>
#include <memory>

using namespace std;

template<class T>
class Queue
{
private:
    class Elem
    {
    public:
        T m_data;
        shared_ptr<Elem> m_prevElem;

        Elem(T data, shared_ptr<Elem> prevElem = nullptr)
            : m_data(data), m_prevElem(prevElem)
        {
        }

        ~Elem()
        {
        }
    };

    shared_ptr<Elem> head;
    shared_ptr<Elem> tail;
    int size;

public:

    Queue()
        : head(nullptr), tail(nullptr), size(0)
    {
    }

    ~Queue()
    {
        clear();
    }

    void push(T data);
    T pop();
    int getSize() { return size; }
    void clear();
};

template<class T>
void Queue<T>::push(T data)
{
    if (head == nullptr)
    {
        head = make_shared<Elem>(data);
        tail = head;
    }
    else
    {
        tail->m_prevElem = make_shared<Elem>(data);
        tail = tail->m_prevElem;
    }
    size++;
}

template<class T>
T Queue<T>::pop()
{
    if (tail == head)
    {
        T data = tail->m_data;
        tail = nullptr;
        head = nullptr;
        return data;
    }
    T data = head->m_data;
    head = head->m_prevElem;
    size--;
    return data;
}

template<class T>
void Queue<T>::clear()
{
    head = nullptr;
    tail = nullptr;
}