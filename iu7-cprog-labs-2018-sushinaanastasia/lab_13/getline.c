#include"getline.h"

#define BUF_SIZE 128


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
 * @brief my_strcmp
 * Сравнение строк
 * @param a [in] - первая строка
 * @param b [in] - вторая строка
 * @return 0 - если равны 1 - не равны
 */
int my_strcmp(const char *a, const char *b)
{
	int len1 = my_strlen(a);
	int len2 = my_strlen(b);
	
	if (len1 != len2)
		return 1;
	for (int i = 0 ; i < len1; i++)
		if (a[i] != b[i])
			return 1;
	return 0;
}

/**
 * @brief my_strcpy
 * Копирует строки
 * @param str1 [in] - строка 1
 * @param str2 [in] - строка 2
 */

void my_strcpy(char *str1, char *str2)
{
	if (!str2 || !str1)
		return;
	int len = my_strlen(str2);
	for (int i = 0; i <= len ; i++)
		str1[i] = str2[i];
}

/**
 * @brief my_getline
 * считывает строку из файла
 * @param lineptr [out] - считанная строка
 * @param n [out] - количество символов
 * @param stream [in] - файл
 * @return
 */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	if (!lineptr)
		return -1;
	
	int size = 0;
	int len = 0;
	char *b = NULL;
	char buf[BUF_SIZE + 1];
	//char *string = NULL;
    char *string = *lineptr;
	
	
	if (!stream || !n || ferror(stream) || feof(stream))
	{
		//if (*lineptr)
		    //free(*lineptr);
		return -1;
	}
	
	while (fgets(buf, BUF_SIZE + 1, stream))
	{
		len = my_strlen(buf);
		if (!len)
			break;
		size += len;
		
		// если длина строки больше переданной или передан пустой буфер
		if (size > *n || string == NULL)
		{
			b = realloc(string, size + 1);
		    if (!b)
		    {
		    	if (string)
		    	    free(string);
	    		return -1;
	    	}
		    string = b;
		}
		
		my_strcpy(string + size - len, buf);
		if (string[size - 1] == '\n')
		{
			break;
		}
	}
	
    if (!size)
	{
		if (string)
		    free(string);
        return -1;
	}
	string[size] = '\0';
	*lineptr = string;
	*n = size;
	return size;
}
