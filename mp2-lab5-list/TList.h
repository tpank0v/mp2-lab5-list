#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "TMonom.h"
using namespace std;

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
	void InsFirst(T value);
	void InsLast(T value);
	void InsCuer(T value);

	void DelFirst();
	void DelCuer();
	void GoNext();
	bool IsEnd();

	void Reset();
	T GetCuer();
	std::string ToStr() const;
};

template<class T>
TList<T>::TList()
{
	pStop = nullptr;
	pFirst = pCuer = pPrev = pLast = pStop;
	len = 0;
}

template<class T>
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

template<class T>
bool TList<T>::IsEmpty()
{
	return pFirst == nullptr;
}

template<class T>
void TList<T>::InsFirst(T value)
{
	TNode<T>* new_node = new TNode<T>;
	new_node->val = value;
	new_node->pNext = pFirst;
	pFirst = new_node;
	len++;
	if (len == 1)
	{
		pLast = pFirst;
		pCuer = pFirst;
	}
}

template<class T>
void TList<T>::InsLast(T value)
{
	if (len > 0) 
	{
		TNode<T>* new_node = new TNode<T>;
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

template<class T>
void TList<T>::InsCuer(T value)
{
	if (pCuer == pFirst) 
	{
		InsFirst(value);
	}
	else if (pCuer == pLast)
	{
		InsLast(value);
	}
	else {
		TNode<T>* new_node = new TNode<T>;
		new_node->val = value;
		new_node->pNext = pCuer;
		pCuer = new_node;
		pPrev->pNext = pCuer;
		len++;
	}
}

template<class T>
void TList<T>::DelFirst()
{
	if (IsEmpty())
	{
		throw "Empty!";
	}

	if (pCuer == pFirst)
	{
		pPrev = pStop;
		pCuer = pCuer->pNext;
	}

	TNode<T>* new_node = pFirst;
	pFirst = new_node->pNext;
	delete new_node;
	len--;
	if (pFirst == pStop) 
	{
		pLast = pStop;
	}
}

template<class T>
void TList<T>::DelCuer()
{
	if (IsEmpty())
	{
		throw "Empty!";
	}

	if (pCuer == pFirst) 
	{
		DelFirst();
	}
	else {
		TNode<T>* new_node = pCuer;
		pCuer = new_node->pNext;
		pPrev->pNext = pCuer;
		delete new_node;
		len--;
	}
}

template<class T>
void TList<T>::GoNext()
{
	pPrev = pCuer;
	pCuer = pCuer->pNext;
}

template<class T>
bool TList<T>::IsEnd()
{
	return pCuer == pStop;
}

template<class T>
T TList<T>::GetCuer()
{
	if (pCuer == pStop)
	{
		throw "Barrier!";
	}
	return pCuer->val;
}

template<class T>
void TList<T>::Reset()
{
	pPrev = pStop;
	pCuer = pFirst;
}

template <class T>
class THeadList : public TList<T>
{
protected:
	TNode<T>* pHead;
public:
	THeadList();
	~THeadList();
	void InsFirst(T elem);
	void DelFirst();
};

template<class T>
THeadList<T>::THeadList()
{
	len = 0;
	pHead = new TNode<T>;
	pHead->pNext = pHead;
	pFirst = pLast = pPrev = pCuer = pStop = pHead;
}

template<class T>
THeadList<T>::~THeadList()
{
	while (pFirst != pStop) 
	{
		TNode<T>* new_node = pFirst;
		pFirst = pFirst->pNext;
		delete new_node;
	}
	delete pHead;
}

template<class T>
void THeadList<T>::InsFirst(T elem)
{
	TList::InsFirst(elem);
	pHead->pNext = pFirst;
}

template<class T>
void THeadList<T>::DelFirst()
{
	TList::DelFirst();
	pHead->pNext = pFirst;
}
class TPolinom : public THeadList<TMonom>
{
protected:
	void Print(std::ostream& os) const;
public:
	TPolinom();
	TPolinom(TPolinom& tp);

	TPolinom& operator=(TPolinom& tp);

	void AddMonom(TMonom m);

	bool operator==(TPolinom& tp);
	bool operator!=(TPolinom& tp);

	TPolinom operator+(TPolinom& tp);
	TPolinom operator-(TPolinom& tp);

	TPolinom operator*(TPolinom& tp);
	TPolinom operator*(TMonom& tp);
	TPolinom operator*(double a);

	friend TPolinom operator*(TMonom& m,TPolinom& tp)
	{
		return tp * m;
	}

	friend TPolinom operator*(double a, TPolinom& tp)
	{
		return tp * a;
	}

	friend std::ostream& operator<<(std::ostream& os, TPolinom& tp)
	{
		tp.Print(os);
		return os;
	}
};

void TPolinom::Print(std::ostream& os) const
{
	TNode<TMonom>* _pCurr = pFirst;

	if (_pCurr == pStop)
	{
		os << "0";
		return;
	}

	TMonom m = _pCurr->val;
	double absCoeff = fabs(m.coeff);

	if (m.coeff < 0) os << "- ";

	
	if (m.IsConst())
	{
		os << absCoeff;
	}
	
	else
	{
		if (absCoeff != 1) os << absCoeff << "*";
		os << m;
	}

	_pCurr = _pCurr->pNext;

	for (; _pCurr != pStop; _pCurr = _pCurr->pNext)
	{
		TMonom m = _pCurr->val;
		double absCoeff = fabs(m.coeff);

		if (m.coeff < 0) os << " - ";
		else os << " + ";

		if (m.IsConst())
		{
			os << absCoeff;
		}
		else
		{
			if (absCoeff != 1)
				os << absCoeff << "*";
			os << m;
		}
	}
}
TPolinom::TPolinom()
{
	TMonom m(0, 0, -1);
	pHead->val = m;
}
TPolinom::TPolinom(TPolinom& tp)
{
	TMonom m(0, 0, -1);
	pHead->val = m;
	for (tp.Reset(); !tp.IsEnd(); tp.GoNext())
	{
		InsLast(tp.GetCuer());
	}
}
TPolinom& TPolinom::operator=(TPolinom& tp)
{
	while (pFirst != pStop)
	{
		DelFirst();
	}

	pFirst = pLast = pPrev = pCuer = pStop = pHead;
	len = 0;

	tp.Reset();
	while (!tp.IsEnd())
	{
		InsLast(tp.GetCuer());
		tp.GoNext();
	}
	return *this;
}
void TPolinom::AddMonom(TMonom m)
{
	if (m.coeff == 0)
		return;

	Reset();

	while (m < pCuer->val)
	{
		GoNext();
	}
	
	if (pCuer->val == m)
	{
		pCuer->val.coeff += m.coeff;
		if (pCuer->val.coeff == 0)
		{
			DelCuer();
		}
	}

	else
	{
		InsCuer(m);
	}
}

bool TPolinom::operator==(TPolinom& tp)
{
	TPolinom rtp(tp);
	rtp.Reset();
	Reset();
	while (!IsEnd())
	{
		if (!(pCuer->val == rtp.pCuer->val))
		{
			return false;
		}
		else
		{
			GoNext();
			rtp.GoNext();
		}
	}

	return true;
}
bool TPolinom::operator!=(TPolinom& tp)
{
	return !(this == &tp);
}
TPolinom TPolinom::operator+(TPolinom& tp)
{
	TPolinom res(tp);
	Reset();
	res.Reset();

	while (!IsEnd())
	{
		if (res.pCuer->val > pCuer->val)
		{
			res.GoNext();
		}
		else if (res.pCuer->val < pCuer->val)
		{
			res.InsCuer(pCuer->val);
			GoNext();
		}
		else
		{
			res.pCuer->val.coeff += pCuer->val.coeff;
			if (res.pCuer->val.coeff == 0)
			{
				res.DelCuer();
				GoNext();
			}
			else
			{
				res.GoNext();
				GoNext();
			}
		}
	}
	return res;

}
TPolinom TPolinom::operator*(TPolinom& tp)
{
	TPolinom res;

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCuer();
		TPolinom temp = m * tp;
		res = res + temp;
	}

	return res;
}
TPolinom TPolinom::operator*(TMonom& mon)
{
	TPolinom res;

	if (mon.coeff == 0) return res;

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCuer();
		res.InsLast(m * mon);
	}

	return res;
}
TPolinom TPolinom::operator*(double a)
{
	TPolinom res;

	if (a == 0) return res;

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCuer();
		m.coeff *= a;

		res.InsLast(m);
	}
	return res;
}
TPolinom TPolinom::operator-(TPolinom& tp)
{
	return operator+(tp.operator*(-1));
}