#include <iostream>
#include "TList.h"

using namespace std;

void main()
{
	TList<int> l;
	l.InsFirst(3);
	l.InsFirst(2);
	l.InsFirst(1);
	for (l.Reset(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCuer() << ' ';
	}
	cout << "\n";
	l.InsLast(4);
	for (l.Reset(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCuer() << ' ';
	}
	cout << "\n";
	l.Reset();
	l.InsCuer(0);
	for (l.Reset(); !l.IsEnd(); l.GoNext())
	{
		cout << l.GetCuer() << ' ';
	}
	cout << "\n";
}