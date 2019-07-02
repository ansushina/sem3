#include "process.h"
#include <stdio.h>
#include <limits.h>

#define N 50

int my_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i] )
			return -1;
		i++;
	}
	if (s1[i] != '\0' || s2[i] != '\0')
		return -1;
	return 0;
}


void test_my_snprintf()
{
	printf("TEST MY SNPRINTF\n");
	// Три разных аргумента в одной строке, все аргументы соответсвуют своим спецификациям. 
	// Проверка правильности работы с несколькими разными аргументами
	{
		char s[N];
		int count;
		
		char s1[N] = "123 ddd 10";
		int count1 = 10;
		
		char str[] = "ddd";
		long long int i = 123;
		int k = 16;
		char f[] = "%lld %s %x";
		
		printf("TEST 1:");
		count = my_snprintf(s, N, f, i, str, k);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, i, str, k);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	// В строке формат только спецификация %lld, проверка работы с данной спецификацией
	{
		char s[N];
		int count;
		
		char s1[N] = "123";
		int count1 = 3;
		
		//char str[] = "ddd";
		long long int i = 123;
		//int k = 16;
		char f[] = "%lld";
		
		printf("TEST 2:");
		count = my_snprintf(s, N, f, i);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, i);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 2(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	// В строке только спецификатор %s, проверка работы данной спецификации 
	{
		char s[N];
		int count;
		
		char s1[N] = "ddd";
		int count1 = 3;
		
		char str[] = "ddd";
		//long long int i = 123;
		//int k = 16;
		char f[] = "%s";
		
		printf("TEST 3:");
		count = my_snprintf(s, N, f, str);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, str);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 3(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	// В строке только спецификатор %x, проверка работы этого спецификатора. 
	{
		char s[N];
		int count;
		
		char s1[N] = "abe0";
		int count1 = 4;
		
		//char str[] = "ddd";
		//long long int i = 123;
		int k = 44000;
		char f[] = "%x";
		
		printf("TEST 4:");
		count = my_snprintf(s, N, f, k);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, k);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 4(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	// В строке помимо спецификаторов содержатся другие символы. Проверка обработки других символов.
	{
		char s[N];
		int count;
		
		char s1[N] = "lld 123 s ddd x 10";
		int count1 = 18;
		
		char str[] = "ddd";
		long long int i = 123;
		int k = 16;
		char f[] = "lld %lld s %s x %x";
		
		printf("TEST 5:");
		count = my_snprintf(s, N, f, i, str, k);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, i, str, k);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 5(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	// В функцию передается длина, которой не хватит. Проверка обработки ошибочной ситуации.
    {
		char s[N];
		int count;
		
		//char s1[N] = "lld 12";
		int count1 = 18;
		
		char str[] = "ddd";
		long long int i = 123;
		int k = 16;
		char f[] = "lld %lld s %s x %x";
		
		printf("TEST 6:");
		count = my_snprintf(s, 0, f, i, str, k);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			printf("OK\n");
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, 7, f, i, str, k);
		
		/*//printf("%d \n %s \n", count, s);
		printf("TEST 6(std):");
		if (count == count1)
		{
			printf("OK\n"); 
		}
		else
		{
			printf("FAIL(count)\n");
		}*/
	}
	// Спецификатору %x ставится в соответсвие отрицательное число. Проверка обработки отрицательного этим спецификатором
	{
		char s[N];
		int count;
		
		char s1[N] = "lld 123 s ddd x fffffff0";
		int count1 = 24;
		
		char str[] = "ddd";
		long long int i = 123;
		int k = -16;
		char f[] = "lld %lld s %s x %x";
		
		printf("TEST 7:");
		count = my_snprintf(s, N, f, i, str, k);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, i, str, k);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 7(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	// Проверка обработки строки
	{
		char s[N];
		int count;
		
		char s1[N] = "lld 123 s ddd123eee x 10";
		int count1 = 24;
		
		char str[] = "ddd123eee";
		long long int i = 123;
		int k = 16;
		char f[] = "lld %lld s %s x %x";
		
		printf("TEST 8:");
		count = my_snprintf(s, N, f, i, str, k);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, i, str, k);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 8(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	
	
	printf("MORE TESTS:\n\n");
	// ТЕСТЫ ДЛЯ ЗАЩИТЫ 
	
    // знаковые МИН
	{
		char s[N];
		int count;
		
		char s1[N] = "-9223372036854775808";
		int count1 = 20;
		
		//char str[] = "ddd";
		long long int i = LLONG_MIN;
		//int k = 16;
		char f[] = "%lld";
		
		printf("TEST 9:");
		count = my_snprintf(s, N, f, i);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, i);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	//знаковое МАХ
	{
		char s[N];
		int count;
		
		char s1[N] = "9223372036854775807";
		int count1 = 19;
		
		//char str[] = "ddd";
		long long int i = LLONG_MAX;
		//int k = 16;
		char f[] = "%lld";
		
		printf("TEST 10:");
		count = my_snprintf(s, N, f, i);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, i);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	//знаковое 0
	{
		char s[N];
		int count;
		
		char s1[N] = "0";
		int count1 = 1;
		
		//char str[] = "ddd";
		long long int i =0;
		//int k = 16;
		char f[] = "%lld";
		
		printf("TEST 11:");
		count = my_snprintf(s, N, f, i);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, i);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	//знаковое -1
	{
		char s[N];
		int count;
		
		char s1[N] = "-1";
		int count1 = 2;
		
		//char str[] = "ddd";
		long long int i = -1;
		//int k = 16;
		char f[] = "%lld";
		
		printf("TEST 12:");
		count = my_snprintf(s, N, f, i);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, i);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	//беззнаковое MAX
	{
		char s[N];
		int count;
		
		char s1[N] = "7fffffff";
		int count1 = 8;
		
		//char str[] = "ddd";
		//long long int i = LLONG_MAX;
		int k = INT_MAX;
		char f[] = "%x";
		
		printf("TEST 13:");
		count = my_snprintf(s, N, f, k);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, k);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	// беззнаковое 0
	{
		char s[N];
		int count;
		
		char s1[N] = "0";
		int count1 = 1;
		
		//char str[] = "ddd";
		//long long int i = LLONG_MAX;
		int k = 0;
		char f[] = "%x";
		
		printf("TEST 14:");
		count = my_snprintf(s, N, f, k);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, k);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	//отрицательное 
	{
		char s[N];
		int count;
		
		char s1[N] ="ffffffff";
		int count1 = 8;
		
		//char str[] = "ddd";
		//long long int i = LLONG_MAX;
		int k = -1;
		char f[] = "%x";
		
		printf("TEST 15:");
		count = my_snprintf(s, N, f, k);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, k);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	//строка буфер достаточной длины
	{
		char s[N];
		int count;
		
		char s1[N] = "My name is 'Nastya'. I was born in 1999.";
		int count1 = 40;
		
		char str[] = "Nastya";
		long long int i = 1999;
		//int k = INT_MAX;
		char f[] = "My name is '%s'. I was born in %lld.";
		
		printf("TEST 16:");
		count = my_snprintf(s, N, f, str, i);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, str, i);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
	// строка буфер нулевой длины 
	{
		char s[N];
		int count;
		
		char s1[N] = "My name is 'Nastya'. I was born in 1999.";
		int count1 = 40;
		
		char str[] = "Nastya";
		long long int i = 1999;
		//int k = INT_MAX;
		char f[] = "My name is '%s'. I was born in %lld.";
		
		printf("TEST 17:");
		count = my_snprintf(s, 0, f, str, i);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		//count = snprintf(s, 0, f, str, i);
		
		//printf("%d \n %s \n", count, s);
		/*printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}*/
	}
	//строка недостаточный буфер по s
	{
		char s[N];
		int count;
		
		char s1[N] = "My name is 'Na";
		int count1 = 40;
		
		char str[] = "Nastya";
		long long int i = 1999;
		//int k = INT_MAX;
		char f[] = "My name is '%s'. I was born in %lld.";
		
		printf("TEST 18:");
		count = my_snprintf(s, 15, f, str, i);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		/*count = snprintf(s, 15, f, str, i);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}*/
	}
	//недостаточный по d
	{
		char s[N];
		int count;
		
		char s1[N] = "My name is 'Nastya'. I was born in 19";
		int count1 = 40;
		
		char str[] = "Nastya";
		long long int i = 1999;
		//int k = INT_MAX;
		char f[] = "My name is '%s'. I was born in %lld.";
		
		printf("TEST 19:");
		count = my_snprintf(s, 38, f, str, i);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		/*count = snprintf(s, 38, f, str, i);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}*/
	}
	//пустая строк акак параметр
		{
		char s[N];
		int count;
		
		char s1[N] = "My name is ''. I was born in 1999.";
		int count1 = 34;
		
		//char str[] = "Nastya";
		long long int i = 1999;
		//int k = INT_MAX;
		char f[] = "My name is '%s'. I was born in %lld.";
		
		printf("TEST 20:");
		count = my_snprintf(s, N, f, "", i);
		
		//printf("%d \n %s \n", count, s);
		
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n");
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
		count = snprintf(s, N, f, "", i);
		
		//printf("%d \n %s \n", count, s);
		printf("TEST 1(std):");
		if (count == count1)
		{
			if (my_strcmp(s, s1) == 0)
			{
				printf("OK\n"); 
			}
			else 
			{
				printf("FAIL(str)\n");
			}
		}
		else
		{
			printf("FAIL(count)\n");
		}
	}
}

int main()
{
	setbuf(stdout, NULL);
	test_my_snprintf();
	return 0;
}