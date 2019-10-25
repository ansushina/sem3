#include "process.h"
#include <stdio.h>
#include <math.h>

/**
 * @brief my_strlen
 * Вычисляет длину строки
 * @param str [in] - строка
 * @return длина строки
 */

size_t my_strlen(const char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}


/**
 * @brief count_in_system
 * считает количество символов в числе в какой-либо системе счисления
 * @param x [in] - число
 * @param s [in] - систма счисления
 * @return кол-во символов
 */
int count_in_system(long long int x, int s)
{
	int n = 0;
	while (x)
	{
		x /= s;
		//printf("n %d", n);
		n++;
	}
	return n;
}

/**
 * @brief in_sixteen
 * переводит цифру в 16ую систему
 * @param x [in] - число
 * @return символ в 16ой системе
 */
char in_sixteen(int x)
{
    char a;
	if (x < 10)
        a = x + '0';
	else if (x == 10)
        a = 'a';
    else if (x == 11)
        a = 'b';
    else if (x == 12)
        a = 'c';
    else if (x == 13)
        a = 'd';
    else if (x == 14)
        a = 'e';
	else if (x == 15)
        a = 'f';
    return a;
}

/**
 * @brief ten_to_sixteen
 * Переводит число из 10ой системы счисления в 16ричную и записывает в строку
 * @param str [in] - строка
 * @param x [in] - число в десятичной ситсеме счисления
 * @param j [in, out] - номер, с которого можно начинать вставлять элементы
 * @param n [in] - длина буфера
 */
int ten_to_sixteen(char *str, unsigned int x, int n)
{
	int n1 = count_in_system(x, 16);
	int num[n1];
	
	for (int i = 0; i < n1; i++)
	{
		num[n1 - i - 1] = x % 16;
		x /= 16;
		//printf("%d \n",num[n1-i -1]);
	}
	int i;
	for (i = 0; i < n1 && i < n - 1; i++)
	{
		str[i] = in_sixteen(num[i]);
	}
	if (i == n - 1 && i < n1)
		return 1;
	return 0;
}

/**
 * @brief int_to_char
 * Переводит лонг лонг инт число в строку и записывает в буфер
 * @param s [in] - строка
 * @param d [in] - число
 * @param j [in, out] - номер, с которого можно начинать вставлять элементы
 * @param n [in] - длина буфера
 */
int int_to_char(char *s, long long int d, int n)
{
	int n1 = count_in_system(d, 10);
	//printf("\n n1 %d d %d\n", n1, (int)d);
   
	int num[n1];
	for (int i = 0; i < n1; i++)
	{
		num[n1 - i - 1] = fabs(d % 10);
		d /= 10;
		//printf("%d \n",num[n1-i -1] );
	}
	int i;
	for (i = 0; i < n1 && i < n - 1; i++)
	{
		s[i] = num[i] + '0';
	}
	if (i == n - 1 && i < n1)
		return 1;
	return 0;
}

/**
 * @brief my_copy_string
 * Копирует строку в буфер
 * @param s [in] - буфер
 * @param str [in] - строка
 * @param j [in, out] - номер, с которого можно начинать вставлять элементы
 * @param n [in] - длина буфера
 */
int my_copy_string(char *s, const char *str, int n)
{
	int u;
	for (u = 0; str[u] != '\0' && u < n - 1; u++)
	{
		s[u] = str[u];
	}
	if (u == n - 1 && str[u] != '\0')
		return 1;
	return 0;
}

/**
 * @brief my_snprintf
 * Записывает в буфер значения в соотвествении с форматом
 * @param s [in] - буфер
 * @param n [in] - длина буфера
 * @param format [in] - строка форматирования
 * @return кол-во записанных символов
 */
int my_snprintf(char *restrict s, size_t n,
    const char *restrict format, ...)
{
	va_list v1;
	
	va_start(v1, format);
	
	if ( !format)
	{
		va_end(v1);
		return -1;
	}
	
	
	int j = 0;
	int i;
	int rc = 0; 
	if (n == 0 || !s)
		rc = 1;
	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == 's')
			{
				char *str; 
				str = va_arg(v1, char *);
				if (!str)
				{
					i++;
				}
				else
				{
				    int n1 = my_strlen(str);
				    if (!rc)
				        rc = my_copy_string(s + j, str, n - j);
				    j += n1;
			    	i++;
				}
			}
			else if (format[i + 1] == 'l' && format[i + 2] == 'l' && format[i + 3] == 'd')
			{
				
				long long int d = 0;
				
				d = va_arg(v1, long long int);
				if (d == 0)
				{
					if (!rc)
					    s[j] = '0';
					j++;
					i += 3;
				}
				else
				{
				    if (d < 0)
				    {
						if (!rc)
					        s[j] = '-';
					    j++;
				    }
		
				    //printf("d %d\n", (int)d);
				    int n1 = count_in_system(d, 10);
				    if (!rc)
				        rc = int_to_char(s + j, d, n - j);
				    j += n1;
				    i += 3;
				}
			}
			else if (format[i + 1] == 'x')
			{
				unsigned int x = 0;
				
				x = va_arg(v1, unsigned int);
				
				if (x == 0)
				{
					if (!rc)
					    s[j] = '0';
					j++;
					i += 1;
					continue;
				}
				
				//printf("x %d\n", (int)x);
				int n1 = count_in_system(x, 16);
				if (!rc)
				    rc = ten_to_sixteen(s + j, x, n - j);
				j += n1;
				i++;
			}
			else
			{
				if (j >= n - 1)
				    rc = 1;
				if (!rc)
				    s[j] = format[i];
			    j++;
			}
		}
		else
		{
			if (j >= n - 1)
				rc = 1;
			if (!rc)
			    s[j] = format[i];
			j++;
		}
	}
	if (!rc)
	{
	    s[j] = '\0';
	}
	else 
    {
		if (n != 0 && s)
            s[n - 1] = '\0';
    }
	va_end(v1);
	return j;
}  
