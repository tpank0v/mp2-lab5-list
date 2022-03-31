#include <iostream>
#include "TList.h"
#include "TMonom.h"

using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");
	TPolinom tp1, tp2;
	int n1, n2;
	cout << "Число мономов: ";

	cin >> n1;
	cout << "\n Введите степени и коэф монома: ";
	for (int i = 0; i < n1; i++)
	{
		double coeff;
		int x, y, z;
		cin >> x >> y >> z >> coeff;
		TMonom tm(x, y, z, coeff);
	    tp1.AddMonom(tm);
	}

	cout << "Итак, полином: " << tp1 << '\n';
	
	int k;
	cout << "Введите число: ";
	cin >> k;
	cout << "Умножение полининома на " << k << " :" << tp1 * k << '\n';

	cout << "Введите параметры монома: ";
	double coeff1;
	int x1, y1, z1;
	cin >> x1 >> y1 >> z1 >> coeff1;
	TMonom tm(x1, y1, z1, coeff1);

	cout << "Умножение полинома на моном:" << tp1 * tm << '\n';
	
	cout << "Введите второй моном. Число мономов в нем: ";
	cin >> n2;
	cout << "\nВведите степени и коэф полинома №2: \n";
	for (int i = 0; i < n2; i++)
	{
		double coeff;
		int x, y, z;
		cin >> x >> y >> z >> coeff;
		TMonom tm(x, y, z, coeff);
		tp2.AddMonom(tm);
	}
	
	cout << "Второй полином: " << tp2 << '\n';
	cout << "Сумма двух полиносов:" << tp1 + tp2 << '\n';

	cout << "Произведение:" << tp1 * tp2 << '\n';
}
