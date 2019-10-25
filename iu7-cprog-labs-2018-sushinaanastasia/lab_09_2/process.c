#include"errors.h"
#include"process.h"
#include"io.h"

/**
 * @brief is_search
 * является ли кусочек равным искомому
 * @param a [in] - указатель места поиска
 * @param b [in] - искомый кусочек
 * @param len [in] - длина искомого кусочка
 * @return  0 - если не является 1 - если является
 */
int is_search(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
		if (a[i] != b[i])
			return 0;
	return 1;
}

/**
 * @brief count_search
 * подсчитывает количество вхождений искомого кусочка
 * @param source [in] - строка, в которой ведется поиск
 * @param search [in] - искомый кусочек
 * @param len1 [in] - длина первой строки
 * @param len2 [in] - длина второй строки
 * @return количество вхождений
 */
int count_search(const char *source, const char *search, int len1, int len2)
{
	int count = 0;
	int i = 0;
	
	while (i < len1 - len2 + 1)
	{
		if (is_search(source + i, search, len2))
		{
			count++;
			i += len2;
		}
		else 
			i++;
	}
	return count;
}

/**
 * @brief insert_replace
 * вставляет в строку новый кусочек
 * @param buf [in] - указатель на место, куда вставляется элемент
 * @param replace [in] - строка с кусочком
 * @param len3 [in] - длина кусочка
 */
void insert_replace(char *buf, const char *replace, int len3)
{
	for (int i = 0; i < len3; i++)
		buf[i] = replace[i];
}

/**
 * @brief str_replace
 * заменяет все вхождения search на replace
 * @param source [in] - строка, в которой проводится поиск
 * @param search [in] - искомый кусочек
 * @param replace [in] - новый кусочек
 * @return новая строка
 */
char *str_replace(const char *source, const char *search, const char *replace)
{
	if (!source)
		return NULL;
	int len1, len2, len3;
    len1 = my_strlen(source);
	if (search)
	    len2 = my_strlen(search);
	else 
		len2 = 0;
	if (replace)
	    len3 = my_strlen(replace);
	else 
		len3 = 0;
	
	int count = count_search(source, search, len1, len2);

	if (len1 + (len3 - len2) * count + 1 == 0)
		return NULL;
	
	char *buf = malloc(len1 + (len3 - len2) * count + 1);
	
	if (buf)
	{
		int i = 0;
		int j = 0;
		while (i < len1 - len2 + 1)
	    {
		    if (is_search(source + i, search, len2))
		    {
		    	insert_replace(buf + j, replace, len3);
		    	i += len2;
				j += len3;
		    }
	        else
			{
				buf[j] = source[i];
				j++;
		    	i++;
			}
	    }
		insert_replace(buf + j, source + i, len1 - i);
		j += len1 - i;
		buf[j] = '\0';
	}
	else
		return NULL;
	return buf;
}
