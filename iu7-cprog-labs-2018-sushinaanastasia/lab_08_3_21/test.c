#include"errors.h"
#include"io.h"
#include"sum.h"
#include"multiply.h"
#include"process.h"
#include"sum.h"
#include"matrix.h"
#include <math.h>
//int sum(double **a, int n1, int m1, double **b, int n2, int m2, double ***c)

int is_eq(double **a, double **b, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (fabs(a[i][j] - b[i][j]) > EPS)
				return 0;
	return 1;
}

void test_addition()
{
	printf("TEST ADDITION\n");
	// Сложение простых матриц
	{
		int rc;
		double a1[][3] = { { 0, 1, 2 },{ 3, 4, 5 } };
		int n1 = 2;
		int m1 = 3;
		double b1[][3] = { { 0,1,2 },{ 3,4,5 } };
		int n2 = 2;
		int m2 = 3;
		double d1[][3] = { { 0,2,4 },{ 6,8,10 } };
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		double *d[sizeof(d1) / sizeof(d1[0])];
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
		for (int i = 0; i < sizeof(d1) / sizeof(d1[0]); i++)
			d[i] = d1[i];
	
	    printf("TEST1: ");
		rc = sum(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			if (is_eq(c, d, n1, m1))
				printf("OK\n");
			else 
				printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("FAIL(param)\n");
	}
	// сложение матриц из одного элемента
	{
		int rc;
		double a1[][1] = { { 1 } };
		int n1 = 1;
		int m1 = 1;
		double b1[][1] = { { 1 } };
		int n2 = 1;
		int m2 = 1;
		double d1[][1] = { { 2 } };
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		double *d[sizeof(d1) / sizeof(d1[0])];
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
		for (int i = 0; i < sizeof(d1) / sizeof(d1[0]); i++)
			d[i] = d1[i];
	
	    printf("TEST2: ");
		rc = sum(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			if (is_eq(c, d, n1, m1))
				printf("OK\n");
			else 
				printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("FAIL(param)\n");
	}
	//сложение матриц с нулевыми полями
	{
		int rc;
		double a1[][3] = { { 1, 0, 0 },{ 3, 0, 5 } };
		int n1 = 2;
		int m1 = 3;
		double b1[][3] = { { 0,0,0 },{ 0,4,0 } };
		int n2 = 2;
		int m2 = 3;
		double d1[][3] = { { 1,0,0 },{ 3,4,5 } };
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		double *d[sizeof(d1) / sizeof(d1[0])];
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
		for (int i = 0; i < sizeof(d1) / sizeof(d1[0]); i++)
			d[i] = d1[i];
	
	    printf("TEST3: ");
		rc = sum(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			if (is_eq(c, d, n1, m1))
				printf("OK\n");
			else 
				printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("FAIL(param)\n");
	}
	//сложение с нулевой матрицей
	{
		int rc;
		double a1[2][3] = { { 0 } };
		int n1 = 2;
		int m1 = 3;
		double b1[][3] = { { 0,2,3 },{ 0,4,0 } };
		int n2 = 2;
		int m2 = 3;
		double d1[][3] = { { 0,2,3 },{ 0,4,0 } };
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		double *d[sizeof(d1) / sizeof(d1[0])];
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
		for (int i = 0; i < sizeof(d1) / sizeof(d1[0]); i++)
			d[i] = d1[i];
	
	    printf("TEST4: ");
		rc = sum(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			if (is_eq(c, d, n1, m1))
				printf("OK\n");
			else 
				printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("FAIL(param)\n");
	}
	// разная размерность матриц
	{
		int rc;
		double a1[][3] = { { 1, 0, 0 },{ 3, 0, 5 },{ 1,2,0 } };
		int n1 = 3;
		int m1 = 3;
		double b1[][3] = { { 0,0,0 },{ 0,4,0 } };
		int n2 = 2;
		int m2 = 3;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
	
	    printf("TEST5: ");
		rc = sum(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(MEM)\n");
		else 
			printf("OK\n");
	}
	// нулевая размерность матриц
	{
		int rc;
		double a1[][3] = { { 1, 0, 0 },{ 3, 0, 5 } };
		int n1 = 2;
		int m1 = 3;
		double b1[][3] = { { 0,0,0 },{ 0,4,0 } };
		int n2 = 0;
		int m2 = 3;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
	
	    printf("TEST6: ");
		rc = sum(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("OK\n");
	}
}

void test_multiply()
{
	printf("TEST MULTIPLY\n");
	// простое умножение
	{
		int rc;
		double a1[][3] = { { 0, 1, 2 },{ 3, 4, 5 } };
		int n1 = 2;
		int m1 = 3;
		double b1[][2] = { { 0,1 },{ 2,3 },{ 4,5 } };
		int n2 = 3;
		int m2 = 2;
		double d1[][2] = { { 10,13 },{ 28,40 } };
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		double *d[sizeof(d1) / sizeof(d1[0])];
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
		for (int i = 0; i < sizeof(d1) / sizeof(d1[0]); i++)
			d[i] = d1[i];
	
	    printf("TEST1: ");
		rc = multiply(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			if (is_eq(c, d, n1, m2))
				printf("OK\n");
			else 
				printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("FAIL(param)\n");
	}
	// умножение матриц из одного элемента
	{
		int rc;
		double a1[][1] = { { 1 } };
		int n1 = 1;
		int m1 = 1;
		double b1[][1] = { { 1 } };
		int n2 = 1;
		int m2 = 1;
		double d1[][1] = { { 1 } };
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		double *d[sizeof(d1) / sizeof(d1[0])];
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
		for (int i = 0; i < sizeof(d1) / sizeof(d1[0]); i++)
			d[i] = d1[i];
	
	    printf("TEST2: ");
		rc = multiply(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			if (is_eq(c, d, n1, m2))
				printf("OK\n");
			else 
				printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("FAIL(param)\n");
	}
	// нулевая размерность
	{
		int rc;
		double a1[][3] = { { 0, 1, 2 },{ 3, 4, 5 } };
		int n1 = 2;
		int m1 = 3;
		double b1[][2] = { { 0,1 },{ 2,3 },{ 4,5 } };
		int n2 = 0;
		int m2 = 2;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
	
	    printf("TEST3: ");
		rc = multiply(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("OK\n");
	}
	// размерность, не подходящая для умножения
	{
		int rc;
		double a1[][3] = { { 0, 1, 2 },{ 3, 4, 5 } };
		int n1 = 2;
		int m1 = 3;
		double b1[][3] = { { 0, 1, 2 },{ 3, 4, 5 } };
		int n2 = 2;
		int m2 = 3;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
	
	    printf("TEST4: ");
		rc = multiply(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("OK\n");
	}
	// умножение на единичную матрицу
	{
		int rc;
		double a1[][3] = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
		int n1 = 3;
		int m1 = 3;
		double b1[][3] = { { 1 },{ 0,1 },{ 0,0,1 } };
		int n2 = 3;
		int m2 = 3;
		double d1[][3] = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])];
		double *b[sizeof(b1) / sizeof(b1[0])]; 
		double *d[sizeof(d1) / sizeof(d1[0])];
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(b1) / sizeof(b1[0]); i++)
			b[i] = b1[i];
		for (int i = 0; i < sizeof(d1) / sizeof(d1[0]); i++)
			d[i] = d1[i];
	
	    printf("TEST5: ");
		rc = multiply(a, n1, m1, b, n2, m2, &c);
		if (rc == OK)
		{
			if (is_eq(c, d, n1, m2))
				printf("OK\n");
			else 
				printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("FAIL(param)\n");
	}
}

//int do_gauss(double **a, int n, int m, double ***b)
void test_process()
{
	printf("TEST PROCESS\n");
	// обычный метод гаусса
	{
		int rc;
		double a1[][4] = { { 0, 1, 2, 3 },{ 3, 4, 5, 6 },{ 1, 2 , 0, 4 } };
		int n1 = 3;
		int m1 = 4;
		double d1[][1] = { { -2 },{ 3 },{ 0 } };
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])]; 
		double *d[sizeof(d1) / sizeof(d1[0])];
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(d1) / sizeof(d1[0]); i++)
			d[i] = d1[i];
	
	    printf("TEST1: ");
		rc = do_gauss(a, n1, m1, &c);
		if (rc == OK)
		{
			if (is_eq(c, d, n1, 1))
				printf("OK\n");
			else 
				printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("FAIL(param)\n");
	}
	// неподходящая размерность матрицы
	{
		int rc;
		double a1[][4] = { { 0, 1, 2 },{ 3, 4, 5 } };
		int n1 = 2;
		int m1 = 4;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
	
	    printf("TEST2: ");
		rc = do_gauss(a, n1, m1, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("OK\n");
	}
	// нулевая размерность матрицы
	{
		int rc;
		double a1[][4] = { { 0, 1, 2 },{ 3, 4, 5 } };
		int n1 = 0;
		int m1 = 4;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
	
	    printf("TEST3: ");
		rc = do_gauss(a, n1, m1, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("OK\n");
	}
	// нулевая матрица
	{
		int rc;
		double a1[3][4] = { { 0 } };
		int n1 = 3;
		int m1 = 4;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
	
	    printf("TEST4: ");
		rc = do_gauss(a, n1, m1, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("OK\n");
	}
	// матрица с одним значащим элементом(невозможно найти столбец решений)
	{
		int rc;
		double a1[3][4] = { { 1 } };
		int n1 = 3;
		int m1 = 4;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
	
	    printf("TEST5: ");
		rc = do_gauss(a, n1, m1, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("OK\n");
	}
	// матрица с пустыми столбцами и строками 
	{
		int rc;
		double a1[3][4] = { { 1 },{ 1 } };
		int n1 = 3;
		int m1 = 4;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
	
	    printf("TEST6: ");
		rc = do_gauss(a, n1, m1, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("OK\n");
	}
	// нулевая размерность по столбцам
	{
		int rc;
		double a1[3][4] = { { 0 } };
		int n1 = 3;
		int m1 = 0;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
	
	    printf("TEST7: ");
		rc = do_gauss(a, n1, m1, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("OK\n");
	}
	// матрица с одинаковыми строками 
	{
		int rc;
		double a1[3][4] = { { 1,2,3 },{ 1,2,3 } };
		int n1 = 3;
		int m1 = 4;
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])]; 
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
	
	    printf("TEST8: ");
		rc = do_gauss(a, n1, m1, &c);
		if (rc == OK)
		{
			printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("OK\n");
	}
	// однородная СЛАУ
	{
		int rc;
		double a1[][4] = { { 0, 1, 2 },{ 3, 4, 5 },{ 1, 2 , 0 } };
		int n1 = 3;
		int m1 = 4;
		double d1[][1] = { { 0 },{ 0 },{ 0 } };
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])]; 
		double *d[sizeof(d1) / sizeof(d1[0])];
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(d1) / sizeof(d1[0]); i++)
			d[i] = d1[i];
	
	    printf("TEST9: ");
		rc = do_gauss(a, n1, m1, &c);
		if (rc == OK)
		{
			if (is_eq(c, d, n1, 1))
				printf("OK\n");
			else 
				printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("FAIL(param)\n");
	}
	// Пример с дробным ответом
	{
		int rc;
		double a1[2][3] = { { 0, 1 },{ 3, 0, 5 } };
		int n1 = 2;
		int m1 = 3;
		double d1[][1] = { { 1.6666666666 },{ 0 } };
		double **c;
		double *a[sizeof(a1) / sizeof(a1[0])]; 
		double *d[sizeof(d1) / sizeof(d1[0])];
		
		for (int i = 0; i < sizeof(a1) / sizeof(a1[0]); i++)
			a[i] = a1[i];
		for (int i = 0; i < sizeof(d1) / sizeof(d1[0]); i++)
			d[i] = d1[i];
	
	    printf("TEST10: ");
		rc = do_gauss(a, n1, m1, &c);
		if (rc == OK)
		{
			if (is_eq(c, d, n1, 1))
				printf("OK\n");
			else 
				printf("FAIL(matrix)\n");
			free_matrix(c, n1);
		}
		else if (rc == ERR_MEMORY)
			printf("FAIL(Memory)\n");
		else 
			printf("FAIL(param)\n");
	}
}

int main()
{
	test_addition();
	test_multiply();
	test_process();
	return 0;
}