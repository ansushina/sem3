#include"process.h"
#include"io.h"
#include"errors.h"
#include"getline.h"

/**
 * @brief read_filename
 * считывает имя файла
 * @param filename [in] - имя файла
 * @return 0 - если все хорошо
 * 1 - если произошла ошибка
 */
int read_filename(char *filename)
{
	printf("Input filename[30signs]: ");
	if (scanf("%30s", filename) == 1)
	{
		//printf("%s", filename);
		return 0;
	}
	return 1;
}

/**
 * @brief read_data
 * ситывает данные из одной строки
 * @param f [in]
 * @param title [out] - название
 * @param author [out] - автор
 * @param year [out] - год
 * @param country [out] - страна
 * @return 1 - произошла ошибка
 * 0 - все верно
 */
int read_data(FILE *f,  char **title, char **author, unsigned short *year, char **country)
{
	char *line = NULL;
	size_t n = 0;
	my_getline(&line, &n, f);

	//printf("%s", line);
	
	char *p = strtok(line, ";");
	if (!p)
		return 1;
	*title = p;
	p = strtok(NULL, ";");
	if (!p)
		return 1;
	*author = p;
	p = strtok(NULL, ";");
	if (!p)
		return 1;
	*country = p;
	p = strtok(NULL, ";");
	if (!p)
		return 1;
	*year = atoi(p);
	
	return 0;
}

/**
 * @brief read_data_from_file
 * ситывает данные из файла
 * @param f [in] - файл
 * @param head [out] - голова списка
 * @param sort_head [in] - массив голов сортировок
 * @param head_filter [in] - массив голов фильтров
 * @return OK - все верно
 * ERR_IO - ошибка ввода
 * ERR_MEMORY - ошибка памяти
 */
int read_data_from_file(FILE *f, film_st **head, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX])
{
	//printf("Lets read! ");
	if (!f)
		return ERR_IO;
	char *title = NULL; 
	char *author = NULL; 
	unsigned short year; 
	char *country = NULL;
	*head = NULL;
	film_st *new = NULL;
	int rc = OK;
	while(read_data(f, &title, &author, &year, &country) == OK)
	{
		//printf("Read one %d\n", year);
		new  = create_struct(title, author, year, country);
		if (new)
		{
			
			*head = add(*head, new, sort_head, head_filter);
			
		}
		else
		{
			free_list(*head);
			rc = ERR_MEMORY;
			break;
		}
	}
	return rc;
}

/**
 * @brief print_normal
 * печатает список в нормальном виде
 * @param f [in] - файл
 * @param head [in] - голова списка
 */
void print_normal(FILE *f, film_st *head)
{
	if (!f || !head)
	{
		printf("No elements in struct\n");
		return;
	}
	fprintf(f, "\nNORMAL STRUCT\n");
	while(head)
	{
		//printf("\n%p\n", (void*)head);
	    fprintf(f, "%10s %10s %5d %10s \n", head->title, head->author, head->year, head->country);
		head = head->next;
	}
}

/**
 * @brief print_sort
 * печатает отсортированный список
 * @param f [in] - файл
 * @param head [in] - голова списка
 * @param i [in] - номер сортировки
 */
void print_sort(FILE *f, film_st *head, int i)
{
	if (!head)
	{
		printf("No elements in sort %d\n", i);
        return;
    }
	film_st *item = head;
    struct list_head *iter;
	printf("SORTED STRUCT sort %d\n", i+1);
    //printf("\n%p\n", (void*)head);
	//printf("[LIST] %d\n", item->year);
	fprintf(f, "%10s %10s %5d %10s \n", item->title, item->author, item->year, item->country);
    list_for_each(iter, &(head->sort[i]))
    {
		//printf("\n%p\n", (void*)item);
		item = list_entry(iter, film_st, sort[i]);
		fprintf(f, "%10s %10s %5d %10s \n", item->title, item->author, item->year, item->country);
    }
	printf("\n");
}

/**
 * @brief print_filter
 * Печатает список после применения фильтра
 * @param f [in] - файл
 * @param head [in] - голова списка
 * @param i [in] - номер фильтра
 */
void print_filter(FILE *f, film_st *head, int i)
{
	if (!head)
	{
		printf("No elements in filter %d\n", i);
        return;
	}
	film_st *item = head;
    struct list_head *iter;
	printf("FILTER	STRUCT filter %d\n", i+1);
    //printf("\n%p\n", (void*)head);
	///printf("[LIST] %d\n", item->year);
	fprintf(f, "%10s %10s %5d %10s \n", item->title, item->author, item->year, item->country);
    list_for_each(iter, &(head->filter[i]))
    {
		//printf("\n%p\n", (void*)item);
		item = list_entry(iter, film_st, filter[i]);
		fprintf(f, "%10s %10s %5d %10s \n", item->title, item->author, item->year, item->country);
    }
	printf("\n");
}

