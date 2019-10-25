#include"errors.h"
#include"process.h"
#include"io.h"

void test_str_replace()
{
	printf("TEST STR REPLACE");
	// простые вхождения
	{
		char a[] = "aaaa";
        char *b;
        char b1[] = "bbbbbb";
        char s[] = "aa";
		char r[] = "bbb";
		
		printf("TEST1: ");
		b = str_replace(a, s, r);
		
		if (my_strcmp(b, b1) == 0)
			printf("OK\n");
		else 
			printf("FAIL\n");
		if (b)
			free(b);
	}
	//вхождение с начала строки
	{
		char a[] = "aayyy";
        char *b;
        char b1[] = "bbbyyy";
        char s[] = "aa";
		char r[] = "bbb";
		
		printf("TEST2: ");
		b = str_replace(a, s, r);
		
		if (my_strcmp(b, b1) == 0)
			printf("OK\n");
		else 
			printf("FAIL\n");
		if (b)
			free(b);
	}
	// вхождение в конце строки
	{
		char a[] = "yyaa";
        char *b;
        char b1[] = "yybbb";
        char s[] = "aa";
		char r[] = "bbb";
		
		printf("TEST3: ");
		b = str_replace(a, s, r);
		
		if (my_strcmp(b, b1) == 0)
			printf("OK\n");
		else 
			printf("FAIL\n");
		if (b)
			free(b);
	}
	//вхождение в центре строки
	{
		char a[] = "yyaaooaa";
        char *b;
        char b1[] = "yybbboobbb";
        char s[] = "aa";
		char r[] = "bbb";
		
		printf("TEST4: ");
		b = str_replace(a, s, r);
		
		if (my_strcmp(b, b1) == 0)
			printf("OK\n");
		else 
			printf("FAIL\n");
		if (b)
			free(b);
	}
	// уменьшение длины строки
	{
		char a[] = "yyaaaaaa";
        char *b;
        char b1[] = "yybb";
        char s[] = "aaa";
		char r[] = "b";
		
		printf("TEST5: ");
		b = str_replace(a, s, r);
		
		if (my_strcmp(b, b1) == 0)
			printf("OK\n");
		else 
			printf("FAIL\n");
		if (b)
			free(b);
	}
	// длина строки остается прежней
	{
		char a[] = "yyaaii";
        char *b;
        char b1[] = "yybbii";
        char s[] = "aa";
		char r[] = "bb";
		
		printf("TEST6: ");
		b = str_replace(a, s, r);
		
		if (my_strcmp(b, b1) == 0)
			printf("OK\n");
		else 
			printf("FAIL\n");
		if (b)
			free(b);
	}
	//нет вхождений
	{
		char a[] = "yyuu";
        char *b;
        char b1[] = "yyuu";
        char s[] = "aa";
		char r[] = "bbb";
		
		printf("TEST7: ");
		b = str_replace(a, s, r);
		
		if (my_strcmp(b, b1) == 0)
			printf("OK\n");
		else 
			printf("FAIL\n");
		if (b)
			free(b);
	}
	//длина строки поиска боольше длины самой строки
	{
		char a[] = "yyaa";
        char *b;
        char b1[] = "yyaa";
        char s[] = "aaaaaaa";
		char r[] = "bbb";
		
		printf("TEST8: ");
		b = str_replace(a, s, r);
		
		if (my_strcmp(b, b1) == 0)
			printf("OK\n");
		else 
			printf("FAIL\n");
		if (b)
			free(b);
	}
	//есть символ из строки поиска, но не она сама
	{
		char a[] = "yyaoo";
        char *b;
        char b1[] = "yyaoo";
        char s[] = "aa";
		char r[] = "bbb";
		
		printf("TEST9: ");
		b = str_replace(a, s, r);
		
		if (my_strcmp(b, b1) == 0)
			printf("OK\n");
		else 
			printf("FAIL\n");
		if (b)
			free(b);
	}
	// есть несколько вариантов вхождения, меняется только первое
	{
		char a[] = "yyaaa";
        char *b;
        char b1[] = "yybbba";
        char s[] = "aa";
		char r[] = "bbb";
		
		printf("TEST10: ");
		b = str_replace(a, s, r);
		
		if (my_strcmp(b, b1) == 0)
			printf("OK\n");
		else 
			printf("FAIL\n");
		if (b)
			free(b);
	}
}


int main()
{
	test_str_replace();
	return 0;
}