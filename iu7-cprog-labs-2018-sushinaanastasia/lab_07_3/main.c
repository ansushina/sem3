/*
Написать программу, которая сортирует массив. Данные в массив считываются
из текстового файла. Количество элементов в файле не указано. Память выделяется
динамически. Число элментов в массиве определяется в первом проходе по текстовому
файлу, во времявторого прохода числа считываются в массив. 
Полученный после сортировки массив записывается в другой файл. 
возможно, что еред сортировкой элементы массивы могут быть отфильтрованы 
с помощью функции-фильтра.  
*/


#include<string.h>
#include<stdlib.h>

#include"io.h"
#include"process.h"
#include"filter.h"
#include"errors.h"

/**
Обработка ошибочных ситуаций
argc - количество параметров
argv - параметры
f_in, f_out - файлы
rc - код ошибки
ab - указатель на первый элемент массива а
ae - указатель на запоследний элемент массива а
bb - указатель на первый элемент массива б 
be - указатель на запоследний элемент массива б 
*/
int main(int argc, char **argv)
{
	FILE *f_in;
	FILE *f_out;
	int rc;
	int *ab = NULL;
	int *ae = NULL;
	
	if (argc != 3 && argc != 4)
	{
		printf("main.exe in_file out_file [f]");
		return ERR_PARAM;
	}
	if (argc == 4 && strcmp(argv[3], "f") != 0)
	{
		printf("main.exe in_file out_file [f]\n");
		return ERR_PARAM;
	}
	
	f_in = fopen(argv[1], "r");
	if (f_in)
	{
		f_out = fopen(argv[2], "w");
	    if (f_out)
		{
		    rc = read_a(f_in, &ab, &ae);
			if (rc == OK)
			{
				int *bb = ab;
				int *be = ae;
				
	            if (argc == 4)
		        {
					rc = key(ab, ae, &bb, &be);
					if (rc == OK)
						free(ab);
				}
				if (rc == OK)
				{
					mysort(bb, be - bb, sizeof(int), cmp_int);
					print_array(f_out, bb, be);
					printf("Array was sorted");
				}
				else if (rc == ERR_MEMORY)
					printf("Memory error!\n");
				else if (rc == ERR_FILTER)
					printf("Zero elements after filter!\n");
				else 
					printf("KEY ERRORS\n");
		        free(bb);
			}
			else if (rc == ERR_EMPTY)
				printf("Empty massiv!\n");
			else 
				printf("Memory error!\n");
			fclose(f_out);
		}
		else 
		{
			printf("f_out can't be open!\n");
			rc = ERR_IO;
		}
	    fclose(f_in);
	}
	else
	{
		printf("f_in can't be open!\n");
		rc = ERR_IO;
	}
		
	return rc;
}