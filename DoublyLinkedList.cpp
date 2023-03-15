#include <iostream>
#include <memory>

using namespace std;

template<class T>
class DoublyList
{
private:
	class Elem
	{
	public:
		shared_ptr<Elem> m_next;
		shared_ptr<Elem> m_prev;
		T m_data;

		Elem(T data, shared_ptr<Elem> prev = nullptr)
			: m_data(data), m_prev(prev), m_next(nullptr)
		{
		}

		~Elem()
		{
		}
	};

	int size;
	shared_ptr<Elem> head;
	shared_ptr<Elem> tail;

public:

	DoublyList()
	: size(0), head(nullptr), tail(nullptr)
	{
	}

	~DoublyList()
	{
		clear();
	}

	void push_back(const T data);
	void push_front(const T data);
	void pop_front();
	void pop_back();
	void clear();
	void insert(const T data, const int index);
	void removeAt(const int index);
	int getSize() { return size; };
	T& operator[](const int index);
};

template<class T>
void DoublyList<T>::push_back(const T data)
{
	if (head == nullptr)
	{
		head = make_shared<Elem>(data);
		tail = head;
	}
	else
	{
		tail->m_next = make_shared<Elem>(data, tail);
		tail = tail->m_next;
	}

	size++;
}

template<class T>
void DoublyList<T>::push_front(const T data)
{
	if (head == nullptr)
	{
		head = make_shared<Elem>(data);
		tail = head;
	}
	else
	{
		head->m_prev = make_shared<Elem>(data);
		shared_ptr<Elem> temp = head;
		head = head->m_prev;
		head->m_next = temp;
	}

	size++;
}

template<class T>
void DoublyList<T>::pop_front()
{
	head = head->m_next;
	head->m_prev = nullptr;
	size--;
}

template<class T>
void DoublyList<T>::pop_back()
{
	tail = tail->m_prev;
	tail->m_next = nullptr;
	size--;
}

template<class T>
void DoublyList<T>::clear()
{
	while (head != tail)
		pop_back();

	tail = nullptr;
	head = nullptr;
}

template<class T>
void DoublyList<T>::insert(const T data, const int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else if (index == size)
	{
		push_back(data);
	}
	else if (index < size / 2)
	{
		shared_ptr<Elem> current = head;
		for (int count{ 0 }; count != index - 1; count++)
		{
			current = current->m_next;
		}
		shared_ptr <Elem> temp = current->m_next;
		current->m_next = make_shared<Elem>(data, current);
		current = current->m_next;
		current->m_next = temp;
		temp->m_prev = current;
		size++;
	}
	else
	{
		shared_ptr<Elem> current = tail;
		for (int count{ getSize() - 1 }; count != index - 1; count--)
		{
			current = current->m_prev;
		}
		shared_ptr <Elem> temp = current->m_next;
		current->m_next = make_shared<Elem>(data, current);
		current = current->m_next;
		current->m_next = temp;
		temp->m_prev = current;
		size++;
	}
}

template<class T>
void DoublyList<T>::removeAt(const int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else if (index == size - 1)
	{
		pop_back();
	}
	else if (index < size / 2)
	{
		shared_ptr<Elem> current = head;
		for (int count{ 0 }; count != index - 1; count++)
		{
			current = current->m_next;
		}
		shared_ptr <Elem> temp = current->m_next->m_next;
		current->m_next = temp;
		temp->m_prev = current;
		size--;
	}
	else
	{
		shared_ptr<Elem> current = tail;
		for (int count{ getSize() - 1 }; count != index - 1; count--)
		{
			current = current->m_prev;
		}
		shared_ptr <Elem> temp = current->m_next->m_next;
		current->m_next = temp;
		temp->m_prev = current;
		size--;
	}
}

template<class T>
T& DoublyList<T>::operator[](const int index)
{
	if (index < size / 2)
	{
		shared_ptr<Elem> current = head;
		for (int count{ 0 }; count != index; count++)
		{
			current = current->m_next;
		}
		return current->m_data;
	} 
	else
	{
		shared_ptr<Elem> current = tail;
		for (int count{ getSize() - 1}; count != index; count--)
		{
			current = current->m_prev;
		}
		return current->m_data;
	}
}
