#pragma once
#include <iostream>
using namespace std;
struct TMonom
{
	double coeff;
	int x, y, z;
	TMonom();
	TMonom(int x, int y, int z)
	{

	}
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

	void Reset();
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
	void TList<T>::Reset()
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



template <class T>
class THeadList:public TList<T>
{
protected:
	TNode <T>* pHead;
public:
	THeadList();
	~THeadList();
	void InsFirst(T el);
	void DelFirst(T el);
};

template <class T>
THeadList<T>::THeadList()
{
	pHead = new TNode<T>;
	pHerad->pNext = pHead;
	len = 0;
	pStop = pPrev = pCuer = pHead;
}
template <class T>
THeadList<T>::~THeadList()
{
	while (pFirst != pStop)
	{
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
	delete pHead;
}
template <class T>
void THeadList<T>::InsFirst(T el)
{
	TList::InsFirst(el);
	pHead ->pNext = pFirst;
}
template <class T>
void THeadList<T>::DelFirst(T el)
{
	TList::DelFirst(el);
	pHead->pNext = pFirst;
}


class TPolinom :public THeadList<TMonom>
{
public:
	TPolinom():THeadList<TMonom>()
	{
		TMonom m;
		m.x = 0; m.y = 0; m.y = -1;
		pHead->val = m;
	}

	TPolinom(TPolinom& cp)
	{
		TMonom m(0, 0, -1);
		pHead->val = m;
		for (cp.Reset(); !cp.IsEnd(); cp.GoNext())
		{
			InsLast(cp.GetCuer());
		}
	}
	void AddMonom(TMonom mon) 
	{
		Reset();
		while (pCuer->val > mon)
		{
			GoNext();
			if (pCuer->val == mon)
			{
				pCuer->val.coeff += mon.coeff;
				if (pCuer->val.coeff == 0)
					DelCuer;
			}
			else
				InsCuer(mon);
		}
	}


