#include <iostream>
#include <memory>

using namespace std;

template<class T>
class SingleList
{
private:
	class Elem
	{
	public:
		shared_ptr<Elem> m_next;
		T m_data;

		Elem(T data, shared_ptr<Elem>next = nullptr)
			: m_data(data), m_next(next)
		{
		}

		~Elem()
		{
		}
	};

	int size;
	shared_ptr<Elem> head;

public:

	SingleList()
		: size(0), head(nullptr)
	{
	}

	~SingleList()
	{
		clear();
	}

	void pop_front();
	void pop_back();
	void push_back(T data);
	void push_front(T data);
	void clear();
	void insert(T data, const int index);
	void removeAt(const int index);
	T& operator[](const int index);
	int getSize();
};

template<class T>
void SingleList<T>::pop_front()
{
	head = head->m_next;
	size--;
}

template<class T>
void SingleList<T>::pop_back()
{
	removeAt(size - 1);
}

template<class T>
void SingleList<T>::push_back(T data)
{
	if (head == nullptr) {
		head = make_shared<Elem>(data);
	}
	else
	{
		shared_ptr<Elem> current = head;
		while (current->m_next != nullptr) {
			current = current->m_next;
		}
		current->m_next = make_shared<Elem>(data);
	}
	size++;
}

template<class T>
void SingleList<T>::push_front(T data)
{
	head = make_shared<Elem>(data, head);
	size++;
}

template<class T>
void SingleList<T>::clear()
{
	head = nullptr;
}

template<class T>
void SingleList<T>::insert(T data, const int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		shared_ptr<Elem> current = head;
		for (int count{ 0 }; count != index - 1; count++) {
			current = current->m_next;
		}
		shared_ptr<Elem> temp = current->m_next;
		current->m_next = make_shared<Elem>(data, temp);
	}
	size++;
}

template<class T>
void SingleList<T>::removeAt(const int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		shared_ptr<Elem> current = head;
		for (int count{ 0 }; count != index - 1; count++) {
			current = current->m_next;
		}
		current->m_next = current->m_next->m_next;
	}
	size--;
}

template<class T>
T& SingleList<T>::operator[](const int index)
{
	shared_ptr<Elem> current = head;
	for (int count{0}; count != index; count++) {
		current = current->m_next;
	}
	return current->m_data;
}

template<class T>
int SingleList<T>::getSize()
{
	return size;
}