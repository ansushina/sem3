#include<stdio.h>
#include<stdlib.h>
#include"errors.h"
#include"filter.h"
#include"process.h"
#include"io.h"

#define NO 0
#define YES 1

int is_array(const void *a, size_t na, const void *b, size_t nb, size_t size)
{
	const char *ac = a;
	const char *bc = b;
	
	if (na != nb)
		return NO;
	const char *pj = bc;
	for (const char *pi = ac; pi < ac + na * size; pi += size)
	{
		if (*pi != *pj)
			return NO;
		pj += size;
	}
	return YES;
}

void test_mysort()
{
	printf("TEST MYSORT:\n");
	printf("INT TESTS: \n");
	// по возрастанию
	{
		int a[] = { 1,2,3,4,5 };
		int b[] = { 1,2,3,4,5 };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(int), cmp_int);
		printf("TEST 1: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// по убыванию
	{
		int a[] = { 5,4,3,2,1 };
		int b[] = { 1,2,3,4,5 };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(int), cmp_int);
		printf("TEST 2: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// рандомно
	{
		int a[] = { 4,3,5,1,2 };
		int b[] = { 1,2,3,4,5 };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(int), cmp_int);
		printf("TEST 3: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// повторяющиеся элементы
	{
		int a[] = { 5,1,1,2,1,2,3 };
		int b[] = { 1,1,1,2,2,3,5 };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(int), cmp_int);
		printf("TEST 4: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// два элемента и убывание
	{
		int a[] = { 5,4 };
		int b[] = { 4,5 };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(int), cmp_int);
		printf("TEST 5: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// два элемента и возрастание
	{
		int a[] = { 1,2 };
		int b[] = { 1,2 };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(int), cmp_int);
		printf("TEST 6: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// один элемент 
	{
		int a[] = { 5 };
		int b[] = { 5 };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(int), cmp_int);
		printf("TEST 7: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	printf("CHAR TESTS:\n");
	// символы по возрастанию
	{
		char a[] = { 'a','b','c','d' };
		char b[] = { 'a','b','c','d' };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(char), cmp_char);
		printf("TEST 1: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(char)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// символы по убыванию
	{
		char a[] = { 'd','c','b','a' };
		char b[] = { 'a','b','c','d' };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(char), cmp_char);
		printf("TEST 2: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(char)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// рандомно
	{
		char a[] = { 'b','c','a','d' };
		char b[] = { 'a','b','c','d' };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(char), cmp_char);
		printf("TEST 3: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(char)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// повторяющиеся
	{
		char a[] = { 'c','b','c','c' };
		char b[] = { 'b','c','c','c' };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(char), cmp_char);
		printf("TEST 4: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(char)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// два по убыванию
	{
		char a[] = { 'c','b' };
		char b[] = { 'b','c' };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(char), cmp_char);
		printf("TEST 5: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(char)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// два по возрастанию
	{
		char a[] = { 'b','c' };
		char b[] = { 'b','c' };
				
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(char), cmp_char);
		printf("TEST 6: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(char)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// один элемент 
	{
		char a[] = { 'c' };
		char b[] = { 'c' };
		
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(char), cmp_char);
		printf("TEST 7: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(char)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	printf("DOUBLE TESTS:\n");
	// вещественные по возрастанию
	{
		double a[] = { 1.1,1.2,1.3,1.4 };
		double b[] = { 1.1,1.2,1.3,1.4 };
		
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(double), cmp_float);
		printf("TEST 1: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(double)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// вещественные по убыванию
	{
		double a[] = { 1.4,1.3,1.2,1.1 };
		double b[] = { 1.1,1.2,1.3,1.4 };
		
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(double), cmp_float);
		printf("TEST 2: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(double)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// рандомно
	{
		double a[] = { 1.1,1.4,1.2,1.3 };
		double b[] = { 1.1,1.2,1.3,1.4 };
		
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(double), cmp_float);
		printf("TEST 3: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(double)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// повторяющиеся
	{
		double a[] = { 1.1,1.2,1.1,1.1 };
		double b[] = { 1.1,1.1,1.1,1.2 };
		
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(double), cmp_float);
		printf("TEST 4: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(double)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// два по возрастанию
	{
		double a[] = { 1.1,1.2 };
		double b[] = { 1.1,1.2 };
		
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(double), cmp_float);
		printf("TEST 5: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(double)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	//два по убыванию
	{
		double a[] = { 1.2,1.1 };
		double b[] = { 1.1,1.2 };
		
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(double), cmp_float);
		printf("TEST 6: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(double)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
	// один 
	{
		double a[] = { 1.1 };
		double b[] = { 1.1 };
		
		mysort(a, sizeof(a) / sizeof(a[0]), sizeof(double), cmp_float);
		printf("TEST 7: ");
		if (is_array(a, sizeof(a) / sizeof(a[0]), b, sizeof(b) / sizeof(b[0]), 
		    sizeof(double)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
	}
}

void test_key()
{
	printf("TEST KEY:\n");
	// нет отрицательных
	{
		int a[] = { 1,2,3,4,5 };
		int b[] = { 1,2,3,4,5 };
		int *cb, *ce;
		
		key(a, a + sizeof(a) / sizeof(a[0]), &cb, &ce);
		printf("TEST 1: ");
		if (is_array(cb, ce - cb, b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free(cb);
	}
	// есть отрицатлеьное
	{
		int a[] = { 1,2,-3,4,5 };
		int b[] = { 1,2 };
		int *cb, *ce;
		
		key(a, a + sizeof(a) / sizeof(a[0]), &cb, &ce);
		printf("TEST 2: ");
		if (is_array(cb, ce - cb, b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free(cb);
	}
	// первое отрицательное
	/*{
		int a[] = { -1,2,3,4,5 };
		int b[] = { -1 };
		int *cb, *ce;
		
		key(a, a + sizeof(a) / sizeof(a[0]), &cb, &ce);
		printf("TEST 3: ");
		if (is_array(cb, ce - cb, b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free(cb);
	}*/
	// несколько отрицательных
	{
		int a[] = { 1,-2,3,-4,5 };
		int b[] = { 1,-2,3 };
		int *cb, *ce;
		
		key(a, a + sizeof(a) / sizeof(a[0]), &cb, &ce);
		printf("TEST 4: ");
		if (is_array(cb, ce - cb, b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free(cb);
	}
	// все отрицатлеьные
	{
		int a[] = { -1,-2,-3,-4,-5 };
		int b[] = { -1,-2,-3,-4 };
		int *cb, *ce;
		
		key(a, a + sizeof(a) / sizeof(a[0]), &cb, &ce);
		printf("TEST 5: ");
		if (is_array(cb, ce - cb, b, sizeof(b) / sizeof(b[0]), 
		    sizeof(int)))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free(cb);
	}
}

int main()
{
	test_mysort();
	test_key();
	return 0;
}