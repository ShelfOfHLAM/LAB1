// Лаб 1.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "omp.h"
#include <windows.h>
using namespace std;

int numthreads = 10;

void task1() {
#pragma omp parallel num_threads(numthreads)
	{
		printf("Hello world\n");
	}
}

void task2() {
	double dynamictime1;
	double dynamictime2;
	double dynamictime3;
	double statictime1;
	double statictime2;
	double statictime3;
	double guidedtime1;
	double guidedtime2;
	double guidedtime3;
	double runtimetime1;
	double runtimetime2;
	double runtimetime3;
	double starttime = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1)

	for (int i = 0; i < numthreads; i++) {

		Sleep(1000);

	}
	dynamictime1 = omp_get_wtime() - starttime;


	starttime = omp_get_wtime();
#pragma omp parallel for schedule(dynamic,1)



	for (int i = 0; i < numthreads; i++)
	{
		if (i % 2 == 0)
			Sleep(1000);
		else
			Sleep(2000);

	}
	dynamictime2 = omp_get_wtime() - starttime;


	starttime = omp_get_wtime();

#pragma omp parallel for schedule(dynamic,1)


	for (int i = 0; i < numthreads; i++)
	{
		if (i > numthreads / 2)
			Sleep(1000);
		else
			Sleep(2000);

	}
	dynamictime3 = omp_get_wtime() - starttime;

	starttime = omp_get_wtime();
#pragma omp parallel for schedule(static, 1)


	for (int i = 0; i < numthreads; i++) {

		Sleep(1000);

	}
	statictime1 = omp_get_wtime() - starttime;


	starttime = omp_get_wtime();
#pragma omp parallel for schedule(static,1)



	for (int i = 0; i < numthreads; i++)
	{
		if (i % 2 == 0)
			Sleep(1000);
		else
			Sleep(2000);

	}
	statictime2 = omp_get_wtime() - starttime;


	starttime = omp_get_wtime();

#pragma omp parallel for schedule(static,1)


	for (int i = 0; i < numthreads; i++)
	{
		if (i > numthreads / 2)
			Sleep(1000);
		else
			Sleep(2000);

	}
	statictime3 = omp_get_wtime() - starttime;

	starttime = omp_get_wtime();
#pragma omp parallel for schedule(runtime)


	for (int i = 0; i < numthreads; i++) {

		Sleep(1000);

	}
	runtimetime1 = omp_get_wtime() - starttime;


	starttime = omp_get_wtime();
#pragma omp parallel for schedule(runtime)



	for (int i = 0; i < numthreads; i++)
	{
		if (i % 2 == 0)
			Sleep(1000);
		else
			Sleep(2000);

	}
	runtimetime2 = omp_get_wtime() - starttime;


	starttime = omp_get_wtime();

#pragma omp parallel for schedule(runtime)


	for (int i = 0; i < numthreads; i++)
	{
		if (i > numthreads / 2)
			Sleep(1000);
		else
			Sleep(2000);

	}
	runtimetime3 = omp_get_wtime() - starttime;

	starttime = omp_get_wtime();
#pragma omp parallel for schedule(guided)


	for (int i = 0; i < numthreads; i++) {

		Sleep(1000);

	}
	guidedtime1 = omp_get_wtime() - starttime;


	starttime = omp_get_wtime();

#pragma omp parallel for schedule(guided)

	for (int i = 0; i < numthreads; i++)
	{
		if (i % 2 == 0)
			Sleep(1000);
		else
			Sleep(2000);

	}
	guidedtime2 = omp_get_wtime() - starttime;

	starttime = omp_get_wtime();
#pragma omp parallel for schedule(guided)


	for (int i = 0; i < numthreads; i++)
	{
		if (i > numthreads / 2)
			Sleep(1000);
		else
			Sleep(2000);

	}
	guidedtime3 = omp_get_wtime() - starttime;

	cout << "Dynamic Time" << " " << "Static time" << " " << "Guided Time" << "Runtime time" << " " << endl;
	cout.precision(1);
	cout << dynamictime1 << " " << statictime1 << " " << guidedtime1 << " " << runtimetime1 << " " << endl;
	cout << dynamictime2 << " " << statictime2 << " " << guidedtime2 << " " << runtimetime2 << " " << endl;
	cout << dynamictime3 << " " << statictime3 << " " << guidedtime3 << " " << runtimetime3 << " " << endl;
}

void task3()
{

	int array[1000];

	for (int i = 0; i < 1000; i++)
		array[i] = i;

	double starttime1 = omp_get_wtime();
	int sum = 0;
#pragma omp parallel for 
	for (int i = 0; i < 1000; i++) {
#pragma omp critical
		sum += array[i];
	}
	cout << "Sum is " << sum << endl;
	cout << "Critica time is " << omp_get_wtime() - starttime1 << endl;

	double starttime2

		= omp_get_wtime();
	int sum2 = 0;
#pragma omp parallel for reduction (+: sum2)
	for (int i = 0; i < 1000; i++) {
		sum2 += array[i];
	}
	cout << "Sum is " << sum2 << endl;
	cout << "Reduction time is " << omp_get_wtime() - starttime2 << endl;

}

void task4()
{
	int a[5], i;

#pragma omp parallel
	{

#pragma omp for
		for (i = 0; i < 5; i++)
			a[i] = i * i;

#pragma omp master
		for (i = 0; i < 5; i++)
			printf_s("a[%d] = %d\n", i, a[i]);


#pragma omp barrier

#pragma omp for
		for (i = 0; i < 5; i++)
			a[i] += i;

	}

#pragma omp master
	for (i = 0; i < 5; i++)
		printf_s("a[%d] = %d\n", i, a[i]);

}

void task5()
{
	const int N = 501;
	double time = 0;
	int a[N][N] = { 0 };
	int u = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			a[i][j] = i + j;

		}

	}

	time = omp_get_wtime();

	omp_set_num_threads(2);

	for (int i = 2; i < N; i++)
	{
		
//#pragma omp parallel for
		for (int j = 2 + u; j < N; j++)
		{
			a[i][j] = a[i - 2][j] + a[i][j - 2];
			a[j][i] = a[i - 2][j] + a[i][j - 2];
		
		}
//#pragma omp barrier
		u++;

	}

	time = omp_get_wtime() - time;

	//cout.precision(2);
	cout.setf(std::ios::fixed);
	cout << time << endl;

/*	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << a[i][j] << " ";

		}

		cout << endl;

	}*/

}

int _tmain(int argc, _TCHAR* argv[])
{
	int a = 0;

	while (true)
	{
		cin >> a;

		switch (a)
		{
		case 1:
			task1();
			break;

		case 2:
			task2();
			break;

		case 3:
			task3();
			break;

		case 4:
			task4();
			break;

		case 5:
			task5();
			break;

		default:
			a = 0;

		}

		if (a == 0)
		{
			break;

		}

		system("pause");
		system("cls");
		
	}

	return 0;
}
