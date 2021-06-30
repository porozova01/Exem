#include <iostream>
#include <clocale>
#include <windows.h>

using namespace std;

struct graph 
{
	int a, z; 
	int route; 
};

const int q = 11; 

struct graph field[q] =
{
	{0,1,2}, {0,2,4}, {0,3,10}, {1,3,11}, {1,4,5}, {2,3,3}, {2,5,1}, {3,4,8}, {3,5,7}, {4,6,6}, {5,6,9}
}; 

const int ap = 7; 

int path[ap],
	route[ap],
	routing,
	start, 
	finish,
	r_lon,
	lon;
bool found,
	inc[ap];

int seek(int a, int z) 
{
	for (int i = 0; i < q; i++)
	{
		if (field[i].a == a && field[i].z == z)
		{
			return field[i].route;
		}
	}
	return 0;
}

int move(int a, int f, int p) 
{
	int n; 
	if (a == f) 
	{
		found = true; 
		lon = r_lon; 
		routing = p; 
		for (int i = 0; i < routing; i++)
		{
			route[i] = path[i]; 
		}
	}
	else 
	{
		for (n = 0; n < ap; n++)
		{
			int d = seek(a, n); 
			if (d && !inc[n] && (lon == 0 || r_lon + d < lon)) 
			{
				path[p] = n; 
				inc[n] = true; 
				r_lon += d; 
				move(n, f, p + 1); 
				path[p] = 0;
				inc[n] = false;
				r_lon -= d;
			}
		}
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int maxim = 0;
	cout << "Программа расчёта кратчайшего пути\n\n" << "1. Расчитать кратчайший путь на графе\n" << "2. Выход\n" ;
	cin >> maxim;
	system("cls");
		switch (maxim)
		{
		case 1:
		{
			for (int i = 0; i < ap; i++)
			{
				path[i] = route[i] = 0; inc[i] = false;
			}
			lon = r_lon = routing = 0;
			start = 0;
			cout << "Введите значение, до какой вершины необходимо найти путь:" << endl;
			cin >> finish;
			finish = finish - 1;
			path[0] = start;
			inc[start] = true; 
			found = false; 
			move(start, finish, 1); 
			if (found) 
			{
				cout << "Путь: ";
				for (int i = 0; i < routing; i++)
				{
					cout << route[i] + 1 << " ";
				}
				cout << ", Длина пути: " << lon << endl;
			}
			else
			{
				cout << "Путь не найден. Повторите попытку." << endl;
			}
			break;
		}
		case 2: 
		{
			break;
		}
		}
	system("pause");
	return 0;
}