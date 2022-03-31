#pragma once
#pragma once
#include <iostream>
using namespace std;
struct TMonom
{
	double coeff;
	int x, y, z;


	TMonom(double _coeff = 0, int _x = 0, int _y = 0, int _z = 0)
	{
		coeff = _coeff;
		x = _x;
		y = _y;
		z = _z;
	}
	bool IsConst() const {
		return x == 0 && y == 0 && z == 0;
	}

	bool operator==(const TMonom& tm) {
		return (x == tm.x) && (y == tm.y) && (z == tm.z);
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
	friend std::ostream& operator<<(std::ostream& os, TMonom& m)
	{
		if (m.x != 0)
		{
			os << "x";
			if (m.x != 1)
				os << m.x;
		}
		if (m.y != 0)
		{
			os << "y";
			if (m.y != 1)
				os << m.y;
		}
		if (m.z != 0)
		{
			os << "z";
			if (m.z != 1)
				os << m.z;
		}
		return os;
	}
	TMonom operator*(const TMonom& t)
	{
		TMonom res;
		res.coeff = coeff * t.coeff;
		res.x = x + t.x;
		res.y = y + t.y;
		res.z = z + t.z;
		return res;
	}
};

template <class T>
struct TNode
{
	T val;
	TNode* pNext;
};
