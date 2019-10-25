#include"process.h"

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
 * @brief my_strcspn
 * Функция вычисляет длину первого участка, не содержащего символов
 * из строки sym (индекс первого вхождения символа из sym)
 * @param str [in] - указатель на строку,в которой осуществяется определеие длины
 * @param sym [in] - строка с набором символов, которые не должны входить в участок
 * @return длина участка
 */
size_t my_strcspn(const char *str, const char *sym)
{
	size_t buf = 0;
	
	if (str == NULL)
		return 0;
	
	if (sym == NULL)
		return my_strlen(str);
	
	int i = 0, j;
	int flag = 0;
	while (str[i] != '\0' && !flag)
	{
		j = 0;
		while (sym[j] != '\0')
		{
			if (str[i] == sym[j])
				flag = 1;
			j++;
		}
		if (!flag)
		    buf++;
		i++;
	}
	
	return buf;
}

/*
Аргументы:

str – указатель на дублируемую строку.

Возвращаемое значение:

NULL – если не удалость выделить память под новую строку или 
скопировать строку на которую указывает аргумент str.
Указатель на дублирующую строку.

Описание:

Функция strdup дублирует строку, на которую указывает аргумент str. 
Память под дубликат строки выделяется с помощью функции malloc, и 
по окончанию работы с дубликатом должна быть очищена с помощью функции free.
*/
 
/**
 * @brief my_strdup
 * Создает дубликат строки(требуетс освобождение памяти после вызова)
 * @param str [in] - строка
 * @return новая строка
 */
char *my_strdup(const char *str)
{
	if (str == NULL)
		return NULL;
	
	int n = my_strlen(str);
	
	char *new = malloc((n + 1) * sizeof(char));
	
	if (!new)
		return NULL;
	
	for (int j = 0; j < n + 1; j++)
	{
		new[j] = str[j];
	}
	
	return new;
}
 
