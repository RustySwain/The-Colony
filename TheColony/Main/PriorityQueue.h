#pragma once
#include <algorithm>
#include <deque>

using namespace std;

template<typename T>
class PriorityQueue
{
	deque<T> open;
	int parentIndex(int _child);
	void swap(T const& _lhs, T const& _rhs);
	bool(*compare)(T const&, T const&);

public:
	explicit PriorityQueue(bool(*)(T const&, T const&));
	void enqueue(T const& _val);
	bool empty();
	void clear();
	size_t size() const;
	void pop();
	void remove(T const& _val);
	T front() const;
};

template<typename T>
PriorityQueue<T>::PriorityQueue(bool(*c)(T const &, T const &)) : open(), compare(c)
{
}

template<typename T>
void PriorityQueue<T>::enqueue(T const& _val)
{
	open.insert(std::upper_bound(open.begin(), open.end(), _val, compare), _val);

	/*int index = (int)open.size();
	open.push_back(_val);
	while (index > 1)
	{
		int parent = index / 2;
		if (open[parent]->isGreater(open[index]))
		{
			swap(index, parent);
			index = parent;
		}
		else
			break;
	}*/
}

template<typename T>
bool PriorityQueue<T>::empty()
{
	return open.empty();
}

template<typename T>
void PriorityQueue<T>::clear()
{
	open.clear();
}

template<typename T>
size_t PriorityQueue<T>::size() const
{
	return open.size();
}

template<typename T>
void PriorityQueue<T>::pop()
{
	open.pop_back();
}

template<typename T>
void PriorityQueue<T>::remove(T const & _val)
{
	open.erase(std::remove(open.begin(), open.end(), _val), open.end());
}

template<typename T>
T PriorityQueue<T>::front() const
{
	return open.back();
}

template<typename T>
int PriorityQueue<T>::parentIndex(int _child)
{
	return _child / 2;
}

template<typename T>
void PriorityQueue<T>::swap(T const & _lhs, T const & _rhs)
{
	T temp = open[_lhs];
	open[_lhs] = open[_rhs];
	open[_rhs] = temp;
}
