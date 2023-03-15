#include <iostream>
#include <memory>

using namespace std;

template<class T>
class Stack
{
private:
    class Elem
    {
    public:
        T m_data;
        shared_ptr<Elem> m_nextElem;

        Elem(T data, shared_ptr<Elem> nextElem = nullptr)
            : m_data(data), m_nextElem(nextElem)
        {
        }

        ~Elem()
        {
        }
    };

    shared_ptr<Elem> head;
    int size;

public:

    Stack()
        : head(nullptr), size(0)
    {
    }

    ~Stack()
    {
        clear();
    }

    void push(T data);
    T pop();
    int getSize() { return size; }
    void clear();
};

template<class T>
void Stack<T>::push(T data)
{
    if (head == nullptr)
    {
        head = make_shared<Elem>(data);
    }
    else
    {
        head = make_shared<Elem>(data, head);
    }
    size++;
}

template<class T>
T Stack<T>::pop()
{
    if (head->m_nextElem == nullptr)\
    {
        T data = head->m_data;
        head = nullptr;
        return data;
    }
    T data = head->m_data;
    head = head->m_nextElem;
    size--;
    return data;
}

template<class T>
void Stack<T>::clear()
{
    head = nullptr;
}
