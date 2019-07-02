#include "sum.h"
#include "io.h"

#define YES 1
#define NO 0

int is_eq(const int *a, int n1, const int *b, int n2)
{
	if (n1 != n2)
		return NO;
	for (int i = 0; i < n1; i++)
	{
		if (a[i] != b[i])
			return NO;
	}
    return YES;	
}

void test_read_array_new(void)
{
	printf("TEST READ ARRAY NEW\n");
	
	//Позитивные тесты
	printf("Positive: \n");
	{
		int x[N];
        int *pend;
        FILE *f;
		int rc;
		
        f = fopen("in_1.txt", "r");
		assert(f != NULL);
		
		printf("TEST1:");
		rc = read_array_new(f, x, &pend);
        if (rc == OK)
		{
			if (pend - x == 0)
				printf("OK\n");
			else
				printf("FAIL(array)\n");
		}
		else
			printf("FAIL(%d)\n",rc);
            
		fclose(f);
	}
	
    {
		int x[N];
        int *pend;
        FILE *f;
		int rc;
		int x1[] = {1,2,3,4,5};
		
        f = fopen("in_2.txt", "r");
		assert(f != NULL);
		
		printf("TEST2:");
		rc = read_array_new(f, x, &pend);
        if (rc == OK)
		{
			if (is_eq(x, pend - x, x1, sizeof(x1)/sizeof(x1[0])))
				printf("OK\n");
			else
				printf("FAIL(array)\n");
		}
		else
			printf("FAIL(%d)\n",rc);
            
		fclose(f);
	}
	
	{
        int x[N];
        int *pend;
		int rc;
        FILE *f;
		int x1[] = {1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1};
		
        f = fopen("in_3.txt", "r");
		assert(f != NULL);
		
		printf("TEST3:");
		rc = read_array_new(f, x, &pend);
        if (rc == ERR_RANGE)
		{
			if (is_eq(x, pend - x, x1, sizeof(x1)/sizeof(x1[0])))
				printf("OK\n");
			else
				printf("FAIL(array)\n");
		}
		else
			printf("FAIL(%d)\n",rc);
            
		fclose(f);
    }
}

void test_get_sum(void)
{
	printf("TEST GET SUM\n");
	
	//Позитивные тесты
	printf("Positive: \n");
	//Сумма равна нулю
    {
        int a[] = {0,1,2,3,4};
		int sum1 = 0;
        int sum;

		printf("TEST1:");
		get_sum(a, a + sizeof(a) / sizeof(a[0]), &sum);
        if (sum == sum1)
            printf("OK\n");
		else
			printf("FAIL\n");
    }
	//Нет отрицательных элементов
	{
        int a[] = {1,2,3,4};
		int sum1 = 33;
        int sum;

		printf("TEST2:");
		get_sum(a, a + sizeof(a) / sizeof(a[0]), &sum);
        if (sum == sum1)
            printf("OK\n");
		else
			printf("FAIL\n");
    }
	// Есть отрицательные элементы
	{
        int a[] = {1,2,-2,-2};
		int sum1 = -1;
        int sum;

		printf("TEST3:");
		get_sum(a, a + sizeof(a) / sizeof(a[0]), &sum);
        if (sum == sum1)
            printf("OK\n");
		else
			printf("FAIL\n");
    }
	//Первый элемент отрицательный
	{
        int a[] = {-1,-1,-2,-2};
		int sum1 = -1;
        int sum;

		printf("TEST4:");
		get_sum(a, a + sizeof(a) / sizeof(a[0]), &sum);
        if (sum == sum1)
            printf("OK\n");
		else
			printf("FAIL\n");
    }
	//Один элемент 
	{
        int a[] = {1};
		int sum1 = 1;
        int sum;

		printf("TEST5:");
		get_sum(a, a + sizeof(a) / sizeof(a[0]), &sum);
        if (sum == sum1)
            printf("OK\n");
		else
			printf("FAIL\n");
    }
	//N элементов
	{
        int a[] = {1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1};
		int sum1 = 100;
        int sum;

		printf("TEST6:");
		get_sum(a, a + sizeof(a) / sizeof(a[0]), &sum);
        if (sum == sum1)
            printf("OK\n");
		else
			printf("FAIL\n");
    }
    
}

int main(void)
{
    test_get_sum();
    test_read_array_new();
    return 0;
}

