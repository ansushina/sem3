#include"process.h"
#include"string.h"
#include"z.h"

/**
 * @brief is_eq
 * Сравнение строк
 * @param a [in] - первая строка
 * @param b [in] - вторая строка
 * @return равны или нет
 */
int is_eq(const char *a, const char *b)
{
	if (!a && !b)
		return 1;
	if (!a || !b)
		return 0;
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0')
	{
		if (a[i] != b[i])
			return 0;
		i++;
	}
    if (a[i] != '\0' || b[i] != '\0')
		return 0;
	return 1;
}

void test_my_strcspn()
{
	printf("TEST MY STRCSPN:\n");
	//длина участка любая
	{
		char str[] = "fffff123";
		char sym[] = "1234567890";
		size_t n, n1 = 5;
		
		printf("TEST1: ");
		
		n = my_strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
		printf("TEST1(string.h): ");
		n = strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	//длина участка 1
	{
		char str[] = "f00006";
		char sym[] = "1234567890";
		size_t n, n1 = 1;
		
		printf("TEST2: ");
		
		n = my_strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
		printf("TEST2(string.h): ");
		n = strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	// первый символ подходящий
	{
		char str[] = "12342323322";
		char sym[] = "1234567890";
		size_t n, n1 = 0;
		
		printf("TEST3: ");
		
		n = my_strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
		printf("TEST3(string.h): ");
		n = strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	// вся строка подходит
	{
		char str[] = "fffff";
		char sym[] = "1234567890";
		size_t n, n1 = 5;
		
		printf("TEST4: ");
		
		n = my_strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
		printf("TEST4(string.h): ");
		n = strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	// один символ подходит
	{
		char str[] = "4";
		char sym[] = "1234567890";
		size_t n, n1 = 0;
		
		printf("TEST5: ");
		
		n = my_strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
		printf("TEST5(string.h): ");
		n = strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	//один символ не подходит
	{
		char str[] = "y";
		char sym[] = "1234567890";
		size_t n, n1 = 1;
		
		printf("TEST6: ");
		
		n = my_strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
		printf("TEST6(string.h): ");
		n = strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	//строка символов из одного элемента
	{
		char str[] = "yy1yyyyy";
		char sym[] = "1";
		size_t n, n1 = 2;
		
		printf("TEST7: ");
		
		n = my_strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
		printf("TEST7(string.h): ");
		n = strcspn(str, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	//пустая строка
	{
		//char str[] = "4567t7tt47f84ii8pp84";
		char sym[] = "1234567890";
		size_t n, n1 = 0;
		
		printf("TEST8: ");
		
		n = my_strcspn(NULL, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
		/*printf("TEST8(string.h): ");
		n = strcspn(NULL, sym);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
		*/ 
		// null argument where non-null required (argument 1)
	}
	//пустой поиск
	{
		char str[] = "456";
		//char sym[] = "1234567890";
		size_t n, n1 = 3;
		
		printf("TEST9: ");
		
		n = my_strcspn(str, NULL);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
		/*printf("TEST9(string.h): ");
		n = strcspn(str, NULL);
		if (n == n1)
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");*/
		//null argument where non-null required (argument 2)
	}
}

void test_my_strdup()
{
	printf("TEST MY STRDUP:\n");
	//любая строка
	{
		char str[] = "1234";
		char *new;
		
		printf("TEST1: ");
		new = my_strdup(str);
		if (new)
		{
		    if (is_eq(str, new))
			    printf("OK\n");
		    else
			    printf("FAIL\n");
		    free(new);
		}
		else
			printf("FAIL\n");
		
		printf("TEST1(string.h): ");
		new = strdup(str);
		if (new)
		{
		    if (is_eq(str, new))
			    printf("OK\n");
		    else
			    printf("FAIL\n");
		    free(new);
		}
		else
			printf("FAIL\n");
	}
	// один элемент
	{
		char str[] = "r";
		char *new;
		
		printf("TEST2: ");
		new = my_strdup(str);
		if (new)
		{
			//printf(" %s ", new);
		    if (is_eq(str, new))
			    printf("OK\n");
		    else
			    printf("FAIL\n");
		    free(new);
		}
		else
			printf("FAIL\n");
		printf("TEST2(string.h): ");
		new = strdup(str);
		if (new)
		{
		    if (is_eq(str, new))
			    printf("OK\n");
		    else
			    printf("FAIL\n");
		    free(new);
		}
		else
			printf("FAIL\n");
	}
	//пустой ввод
	{
		char *new;
		
		printf("TEST3: ");
		new = my_strdup(NULL);
		if (new)
		{
			printf("FAIL\n");
			free(new);
		}
		else
			printf("OK\n");
		/*printf("TEST3(string.h): ");
		new = strdup(NULL);
		if (new)
		{
			printf("FAIL\n");
		}
		else
			printf("OK\n");*/
		//error: null argument where non-null required (argument 1) 
	}
}

void test_change_spaces()
{
	printf("TEST CHANGE SPACES:\n");
	//несколько пробелов в начале, в конце и между словами
	{
		char str[] = "   yyy    yyy    ";
		char str1[] = "yyy yyy";
		
		change_spaces(str);
		
		printf("Test1: ");
		//printf("%s ", str);
		if (is_eq(str, str1))
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	//нет пробелов в начале
	{
		char str[] = "yyy    yyy  ";
		char str1[] = "yyy yyy";
		
		change_spaces(str);
		
		printf("Test2: ");
		//printf("%s ", str);
		if (is_eq(str, str1))
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	//нет пробелов в конце
	{
		char str[] = "   yyy    yyy";
		char str1[] = "yyy yyy";
		
		change_spaces(str);
		
		printf("Test3: ");
		//printf("%s ", str);
		if (is_eq(str, str1))
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	// нет пробелов в середине
    {
		char str[] = "   yyyyyyo     ";
		char str1[] = "yyyyyyo";
		
		change_spaces(str);
		
		printf("Test4: ");
		//printf("%s ", str);
		if (is_eq(str, str1))
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}	
	// несколько промежуткой в середине где нужно убрать пробелы
	{
		char str[] = "   yyy    yyy     ppp    ooo  ";
		char str1[] = "yyy yyy ppp ooo";
		
		change_spaces(str);
		
		printf("Test5: ");
		//printf("%s ", str);
		if (is_eq(str, str1))
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	//не нужно изменять строку вообще
	{
		char str[] = "yyyyyy";
		char str1[] = "yyyyyy";
		
		change_spaces(str);
		
		printf("Test6: ");
		//printf("%s ", str);
		if (is_eq(str, str1))
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	// не нужно изменять пробелы в середине 
	{
		char str[] = "yyy yyy";
		char str1[] = "yyy yyy";
		
		change_spaces(str);
		
		printf("Test7: ");
		//printf("%s ", str);
		if (is_eq(str, str1))
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	//NULL
	{
		//char str[] = "yyy yyy";
		//char str1[] = "yyy yyy";
		char *str = NULL;
		change_spaces(str);
		
		printf("Test8: ");
		//printf("%s ", str);
		if (is_eq(str, NULL))
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	{
		char str[1];
		str[0] = '\0';
		char str1[1];
		str1[0] = '\0';
		
		change_spaces(str);
		
		printf("Test9: ");
		//printf("%s ", str);
		if (is_eq(str, str1))
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
	{
		char str[] = "     ";
		char str1[1];
		str1[0] = '\0';
		
		change_spaces(str);
		
		printf("Test10: ");
		//printf("%s ", str);
		if (is_eq(str, str1))
		{
			printf("OK\n");
		}
		else 
			printf("FAIL\n");
	}
}

int main()
{
	test_my_strcspn();
	test_my_strdup();
	test_change_spaces();
	return 0;
}
