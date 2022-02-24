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
	bool operator!=(const TMonom& m)
	{
		return !operator==(m);
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
	friend std::istream& operator>>(std::istream& is, TMonom& m)
	{
		is >> m.coeff >> m.x >> m.y >> m.z;
		return is;
	}
	friend ostream& operator<<(ostream& os, const TMonom& m)
	{
		os << m.coeff;
		if (m.x != 0)
		{
			os << "x";
			if (m.x != 1) os << "^" << m.x;
		}
		if (m.y != 0)
		{
			os << "y";
			if (m.y != 1) os << "^" << m.y;
		}
		if (m.z != 0)
		{
			os << "z";
			if (m.z != 1) os << "^" << m.y;
		}
		return os;
	
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
	TList();
	~TList();

	bool IsEmpty();
	bool IsFull();

	void InsFirst(T element);
	void InsLast(T element);
	void InsCuer(T element);
	void DelFirst();
	void DelCuer();
	T GetCuer();

	void Revert();
	void GoNext();

	bool IsEnd();
	
};
	template <class T>
TList<T>::TList()
	{
		pStop = nullptr;
		pFirst = pStop, pCuer = pStop, pPrev = pStop, pLast = pStop;
		len = 0;
	}
	template <class T>
TList<T>::~TList()
{
	while (pFirst != pStop)
	{
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
	pLast = pPrev = pCuer = pStop;
	len = 0;
}
template <class T>
	bool TList<T>::IsEmpty()
	{
		return pFirst == nullptr;
	}
template <class T>
	bool TList<T>::IsFull()
	{
		return pFirst != nullptr;
	}
template <class T>
	void TList<T>::InsFirst(T value)
	{
		TNode<T>* new_node = new TNode<T>();
		new_node->val = value;
		new_node->pNext = pFirst;
		pFirst = new_node;
		len++;
		if (len == 1)
			pLast = pFirst;
	}
	template <class T>
	void TList<T>::InsLast(T value)
	{
		{
			if (len > 0)
			{
				TNode<T>* new_node = new TNode<T>();
				new_node->val = value;
				new_node->pNext = pStop;

				pLast->pNext = new_node;
				pLast = new_node;
				len++;
			}
			else
			{
				InsFirst(value);
			}
		}
		
}
	template <class T>
	void TList<T>::InsCuer(T element)
	{
		if (pCuer == pFirst)
			InsFirst(element);
		else if (pPrev == pLast)
			InsLast(element);
		else
		{
			TNode<T>* newNode = new TNode<T>();
			newNode->val = element;

			newNode->pNext = pCuer;
			pPrev->pNext = newNode;
			pCuer = newNode;
			len++;
		}
	}
	template <class T>
	void TList<T>::DelFirst()
	{
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
		len--;
	}
	template <class T>
	void TList<T>::DelCuer()
	{
		if (pFirst == pCuer)
		{
			DelFirst();
		}
		else
		{
			TNode<T>* tmp = pCuer;
			pCuer = pCuer->pNext;
			pPrev->pNext = pCuer;
			delete tmp;
			len--;
		}
	}

	template <class T>
	T TList<T>::GetCuer()
	{
		return pCuer->val;
	}

	template <class T>
	void TList<T>::Revert()
	{
		pPrev = pStop;
		pCuer = pFirst;
	}

	template <class T>
	void TList<T>::GoNext()
	{
		pPrev = pCuer;
		pCuer = pCuer->pNext;
	}
	template <class T>
bool TList<T>::IsEnd()
{
	return pCuer == pStop;
}
