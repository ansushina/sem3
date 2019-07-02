#include"io.h"
#include"process.h"
#include<assert.h>

int reverse(double **mtr, int n, int m)
{
	double swap;
	if (n != m)
		return ERR_MTR;
	if (!mtr || !n || !m || n < 0 || m < 0)
		return ERR_NULL;
	
	for (int j = 0; j <= n / 2; j++)
	{
		for (int i = j + 1; i < n - j - 1; i++)
		{
			swap = mtr[i][n - j - 1];
			mtr[i][n - j - 1] = mtr[i][j];
			mtr[i][j] = swap;
		}
	}
	
	return OK;
}

double find_arg(double **mtr, int n, int m)
{
	assert(mtr && n && m && n> 0 && m > 0);
	assert(n = m);
	double sum = 0; 
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			sum += mtr[i][j];
			count++;
		}
	}
	return sum / count;
}

int count_num(double **mtr, int n, int m, double arg)
{
	assert(mtr && n && m && n> 0 && m > 0 && arg);
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (mtr[i][j] > arg)
			{
				count++;
				//printf(" count %d\n", count);
			}
		}
	}
	return count;
}

double *make_array(double **mtr, int n, int m, int *n2)
{
	assert(mtr && n && m && n> 0 && m > 0);
	assert(n = m);
	
	double arg = find_arg(mtr, n, m); 
	//printf("arg = %lf\n", arg);
	int count = count_num(mtr, n , m, arg);
	
	if (count == 0)
		return NULL;

	double *array = malloc(count * sizeof(double));
	if (!array)
		return NULL;
	
	int u = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (mtr[i][j] > arg)
			{
				array[u] = mtr[i][j];
				u++;
			}
		}
	}
	*n2 = count;
	return array;
}