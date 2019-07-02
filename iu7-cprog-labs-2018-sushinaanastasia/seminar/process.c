#include"io.h"
#include"process.h"
#include<assert.h>

double calc_avg(const double *a, int n)
{
    //assert
	assert(n > 0);
	assert(a);
	
	double s = 0;
	for (int i = 0; i < n; i++)
		s += a[i];
	return s/n; 
}

void sort(double **mtr, int n, int m)
{
	if (!mtr || n <= 0 || m <= 0)
		return;
	double s1, s2, *swap;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n -1; j++)
		{
		    s1 = calc_avg(mtr[j], m);
		    s2 = calc_avg(mtr[j+1], m);
			if (s1 > s2)
			{
				swap = mtr[j];
				mtr[j] = mtr[j+1];
				mtr[j+1] = swap;
			}
		}
	}
}

int find_first_zero(const double *a, int n)
{
	int index = -1;
	
	if (!a || n < 0)
		return index;
	
	for (int i = 0; i < n; i++)
	{
		if (a[i] < EPS)
		{
			index = i;
			break;
		}
	}
	return index;
}

int find_last_ucg(const double *a, int n)
{
	int index = -1;
	
	for (int i = 0; i < n; i++)
	{
		if (a[i] < 0)
		{
			index = i;
		}
	}
	return index;
}

void change(double **mtr, int n, int m)
{
	if (!mtr || n <= 0 || m <= 0)
		return;
	int z, u;
	double swap;
	for (int i = 0; i < n; i++)
	{
		z = find_first_zero(mtr[i], m);
		u = find_last_ucg(mtr[i], m);
		
		if (u >= 0 && z >= 0)
		{
			swap = mtr[i][z];
			mtr[i][z] = mtr[i][u];
			mtr[i][u] = swap;
		}
	}
}