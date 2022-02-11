#pragma once
#include <iostream>
using namespace std;
struct TMonom
{
	double coeff;
	int x, y, z;
	bool operator==(const TMonom& m)
	{
		if (x == m.x && y == m.y && z == m.z)
			return true;
		else
			false;
	}
	bool operator<(const TMonom& m)
	{
		int a, b;
		a = 100 * x + 10 * y + z;
		b = 100 * m.x + 10 * m.y + m.z;
		if (a < b)
			return true;
		else
			return false;
	}
	bool operator>(const TMonom& m)
	{
		int a, b;
		a = 100 * x + 10 * y + z;
		b = 100 * m.x + 10 * m.y + m.z;
		if (a > b)
			return true;
		else
			return false;
	}
	friend ostream& operator<<(ostream& os, const TMonom& m)
	{

	}
};
template <class T>
struct TNode
{
	T val;
	TNode* pNext;

};
template <class T>
class TList
{
protected:
	TNode<T>* pFirst, * pCuer, * pPrev, * pLast, * pStop;
	int len;
public:
	TList()
	{
		pStop = nullptr;
		pFirst = pStop, pCuer = pStop, pPrev = pStop, pLast = pStop;
		len = 0;
	}
	bool IsEmpty()
	{
		return pFirst == nullptr;
	}
	bool IsFull()
	{
		return pFirst != nullptr;
	}
	void InsFirst(T value)
	{
		TNode<T>* new_node = new TNode<T>();
		new_node->val = value;
		new_node->pNext = pFirst;
		pFirst = new_node;
		len++;
		if (len == 0)
			pLast = pFirst;
	}
	void InsLast(T value)
	{
		TNode<T>* new_node = new TNode<T>();
		new_node->val = value;
		new_node->pNext = pStop;
		pLast = new_node;
		len++;
		if (len == 0)
			pLast = pFirst;
		else
			InsFirst(value);
}
};