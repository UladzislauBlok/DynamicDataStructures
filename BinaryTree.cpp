#include <iostream>
#include <memory>
#include <cassert>

using namespace std;


template<class T1, class T2>
class Maps
{
private:
	class Elem
	{
		public:
			shared_ptr<Elem> m_right;
			shared_ptr<Elem> m_left;
			T1 m_key;
			T2 m_data;

			Elem(T1 key, T2 data)
				: m_key(key), m_data(data), m_right(nullptr), m_left(nullptr)
			{
			}

			~Elem()
			{
			}
	};

	shared_ptr<Elem> root;

public:
	Maps()
		: root(nullptr)
	{
	}

	~Maps()
	{
		clear();
	}

	void push(const T1 key, const T2 data);
	T2& at(const T1 key);
	void clear();
};

template<class T1, class T2>
void Maps<T1, T2>::push(const T1 key, const T2 data)
{
	if (root == nullptr)
	{
		root = make_shared<Elem>(key, data);
	}
	else
	{
		shared_ptr<Elem> current = root;
		while (1)
		{
			assert(key != current->m_key, "The keys can't match");
			if (current->m_key > key)
			{
				if (current->m_left != nullptr)
				{
					current = current->m_left;
				}
				else
				{
					current->m_left = make_shared<Elem>(key, data);
					break;
				}
			}
			else
			{
				if (current->m_right != nullptr)
				{
					current = current->m_right;
				}
				else
				{
					current->m_right = make_shared<Elem>(key, data);
					break;
				}
			}
		}
	}
}

template<class T1, class T2>
T2& Maps<T1, T2>::at(const T1 key)
{
	shared_ptr<Elem> current = root;
	while (1)
	{
		if (current->m_key == key) return current->m_data;
		if (current->m_key > key)
		{
			current = current->m_left;
		}
		else
		{
			current = current->m_right;
		}
	}
}

template<class T1, class T2>
void Maps<T1, T2>::clear()
{
	root = nullptr;
}
