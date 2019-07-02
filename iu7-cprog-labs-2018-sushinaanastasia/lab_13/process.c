#include"process.h"
#include"io.h"
#include"errors.h"

/**
 * @brief cmp_year
 * Сравнени двух структур по году
 * @param right [in] - правая структура
 * @param left [in] - левая структура
 * @return <0 , если r < l
 * >0 иначе
 * 0 если равны
 */
int cmp_year(const void *right, const void *left)
{
	const film_st *r = right;
	const film_st *l = left;
	
	return r->year - l->year;
}

/**
 * @brief cmp_country
 * Сравнени двух структур по кстране производителю
 * @param right [in] - правая структура
 * @param left [in] - левая структура
 * @return <0 , если r < l
 * >0 иначе
 * 0 если равны
 */
int cmp_country(const void *right, const void *left)
{
	const film_st *r = right;
	const film_st *l = left;
	
	return strcmp(r->country, l->country);
}

/**
 * @brief cmp_title
 * Сравнени двух структур по названию
 * @param right [in] - правая структура
 * @param left [in] - левая структура
 * @return <0 , если r < l
 * >0 иначе
 * 0 если равны
 */
int cmp_title(const void *right, const void *left)
{
	const film_st *r = right;
	const film_st *l = left;
	
	return strcmp(r->title, l->title);
}

/**
 * @brief filter1
 * фильтр, год больше 100
 * @param el[in]
 * @return 1 - удовлетворяет фильтру
 * 0 - не удовлетворяет фильтру
 */
int filter1(const void *el)
{
	const film_st *p = el;
	
	return (p->year > 100); 
}

/**
 * @brief filter2
 * фильтр, год больше 100
 * @param el[in]
 * @return 1 - удовлетворяет фильтру
 * 0 - не удовлетворяет фильтру
 */
int filter2(const void *el)
{
	const film_st *p = el;
	
	return (p->year >= 3000); 
}

/**
 * @brief create_struct
 * выделяет память под структуру и заполняет ее переданными значениями
 * @param title [in] - название
 * @param author [in] - имя автора
 * @param year [in] - год выпуска
 * @param country [in] -  страна
 * @return адрес новой структуры
 */
film_st *create_struct(char *title, char *author, unsigned short year, char *country)
{
	if (!title || !author || !year || !country)
		return NULL;
	film_st *new = malloc(sizeof(film_st));
	if (new)
	{
		new->title = title;
        //printf("%s ", title);
		new->author = author;
	    //printf("%s ", author);
		new->country = country;
		//printf("%s ", country);
		new->year = year;
		for (int i = 0; i < MAX_SORT_INDX; i++)
		{
			INIT_LIST_HEAD(&(new->sort[i]));
		}
		for (int i = 0; i < MAX_FILTER_INDX; i++)
		{
			INIT_LIST_HEAD(&(new->filter[i]));
		}
		new->next = NULL;
	}
	return new; 
}

/**
 * @brief add_sort
 * добавление в списки сортировки
 * @param head [in] - голова
 * @param new [in] - новая структура
 * @param i [in] - номер сортировки
 * @return голову списка
 */
film_st *add_sort(film_st *head, film_st *new, int i, int (*compar)(const void*, const void*))
{
	//printf("add sort\n");
	struct list_head *iter = &(head->sort[i]);
	film_st *item = head;
	
	if (!head)
		return NULL;
	int flag = 0;
	if (iter->prev == iter)
	{
		flag = 1;
		item = list_entry(iter, film_st, sort[i]);
	    //printf("pppp[LIST] %d\n", item->year);
		if (compar(item, new) > 0)
		{
			list_add(&(new->sort[i]), iter->prev);
			head = new;
			//printf("new head\n");
		}
		else 
		{
			list_add(&(new->sort[i]), iter);
		}
		return head;
	}
	iter = &(head->sort[i]);
	
	if (compar(item, new) > 0)
	{
		list_add(&(new->sort[i]), iter->prev);
		head = new;
		//printf("new head 3\n");
		return head;
	}

    list_for_each(iter, &(head->sort[i]))
	{
		item = list_entry(iter, film_st, sort[i]);
		//printf("[LIST] %d\n", item->year);
	    if (compar(item, new) > 0)
		{
			flag = 1;
			//printf("\n%d %d\n", item->year, new->year);
		    list_add(&(new->sort[i]), iter->prev);
			if (item == head)
			{
				head = new;
				//printf("new head 2");
			}
            break;			
		}
	}
	item = list_entry(iter, film_st, sort[i]);
	if (!flag)
		list_add(&(new->sort[i]), iter->prev);
	
	return head;	
}

/**
 * @brief add_filter
 * добавляет элемент в список фильтр если он ему удовлетворяет
 * @param head [in] - голова
 * @param new [in] - новая структура
 * @param i [in] - номер фильтра
 * @return голову списка
 */
film_st *add_filter(film_st *head, film_st *new, int i, int (*f)(const void*))
{
	//printf("add filter\n");
	
	//printf("%d ", new->year);
	if (f(new))
	{
		if (!head)
			head = new;
		struct list_head *iter = &(head->filter[i]);
		list_add(&(new->filter[i]), iter->prev);
		
	}
	return head;	
}

/**
 * @brief add_in_list
 * добавляет элемент во все списки сортировки и фильтры
 * @param new [in] - новая структура
 * @param sort_head [in] - массив голов сортировок
 * @param head_filter [in] - массив голов фильтров
 */
void add_in_list(film_st *new, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX])
{
	sort_head[0] = add_sort(sort_head[0], new, 0, cmp_year);
	sort_head[1] = add_sort(sort_head[1], new, 1, cmp_country);
	sort_head[2] = add_sort(sort_head[2], new, 2, cmp_title);
	head_filter[0] = add_filter(head_filter[0], new, 0, filter1);
	head_filter[1] = add_filter(head_filter[1], new, 1, filter2);
}

/**
 * @brief add
 * добавляет структуру и вставляет ее в отсортированные структуры и фильтры
 * @param head [in] - голова списка
 * @param new [in] - новая структура
 * @param sort_head [in] - массив голов сортировок
 * @param head_filter [in] - массив голов фильтров
 * @return голову списка
 */
film_st *add(film_st *head, film_st *new, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX])
{
	if (!head)
	{
        head = new;
		
        for (int i = 0; i < MAX_SORT_INDX; i++)
		{
			sort_head[i] = new;
		}
		head_filter[0] = add_filter(head_filter[0], new, 0, filter1);
		head_filter[1] = add_filter(head_filter[1], new, 1, filter2);	
	}
	else
	{
		add_in_list(new, sort_head, head_filter);
		head = add_st(head, new);
	}
	return head;
}
/**
 * @brief add_st
 * добавляет структуру в нужное место односвязного списка
 * @param head [in] - голова списка
 * @param new [in] - новый элемент
 * @return голову списка
 */
film_st *add_st(film_st *head, film_st *new)
{
	if (!head)
	{
		return new;
	}
	
	film_st *beg = head;
	while (head->next)
	{
		head = head->next;
	}
	head->next = new;
	return beg;
}

/**
 * @brief del_from_list
 * Удаляет элемент из всех фильтров и сортировок
 * @param p [in] - элемент на удаление
 * @param sort_head [in] - массив голов сортировок
 * @param head_filter [in] - массив голов фильтров
 */
void del_from_list(film_st *p, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX])
{
	film_st *item;
	for (int i = 0; i < MAX_SORT_INDX; i++)
	{
		struct list_head *iter = (&(p->sort[i]))->next;
		if (sort_head[i] == p)
		{
			item = list_entry(iter, film_st, sort[i]);
			sort_head[i] = item;
		}
		list_del(&(p->sort[i]));
	}
	//printf("Sort complited ");
	for (int i = 0; i < MAX_FILTER_INDX; i++)
	{
		struct list_head *iter = (&(p->filter[i]))->next;
		if (head_filter[i] == p)
		{
			item = list_entry(iter, film_st, filter[i]);
			head_filter[i] = item;
		}
		list_del(&(p->filter[i]));
	}
	//printf("filter complited ");
}

/**
 * @brief del_st
 * Удаление из односвязного списка и всех списков беркли
 * @param head [in] - голова списка
 * @param title [in] - название удаляемого элемента
 * @param sort_head [in] - массив голов сортировок
 * @param head_filter [in] - массив голов фильтров
 * @return голова списка
 */
film_st *del_st(film_st *head, char *title, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX])
{
	if (!head)
		return NULL;
    film_st *p = head;
	film_st *prev = NULL;
	
	if (strcmp(head->title, title) == 0)
	{
		head = head->next;
	}
	//printf("here    ");
	while (p && strcmp(p->title, title) != 0)
	{
		prev = p;
		p = p->next;
	}
	//printf("find p %p", (void *)p);
	if (p)
	{
		del_from_list(p, sort_head, head_filter);
		if (prev)
		{
			prev->next = p->next;
		}
		free(p->title);
		free(p);
		//printf("free complited ");
	}
	else
	{
		printf("No element!\n");
	}
	return head;
}

/**
 * @brief free_list
 * освобождает память
 * @param head [in] - голова списка
 */
void free_list(film_st *head)
{
	film_st *p;
	while (head)
	{
		p = head;
		head = head->next;
		free(p->title);
		free(p);
	}
}

/**
 * @brief change
 * изменение данных об элементе
 * @param head [in] - голова списка
 * @param sort_head [in] - массив голов сортировок
 * @param head_filter [in] - массив голов фильтров
 * @param title [in] - название
 * @param author [in] - имя автора
 * @param year [in] - год выпуска
 * @param country [in] -  страна
 */
void change(film_st *head, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX],
	char *title, char *author, unsigned short year, char *country)
{
	free(head->title);
	head->title = title;
	head->author = author;
	head->year = year;
	head->country = country;
	
	del_from_list(head, sort_head, head_filter);
    add_in_list(head, sort_head, head_filter);
}

/**
 * @brief change_data
 * изменение данных об элементе(с вводом новых данных)
 * @param head [in] - голова списка
 * @param sort_head [in] - массив голов сортировок
 * @param head_filter [in] - массив голов фильтров
 */
void change_data(film_st *head, film_st *sort_head[MAX_SORT_INDX], 
    film_st *head_filter[MAX_FILTER_INDX])
{
	char *title = NULL; 
	char *author = NULL; 
	unsigned short year; 
	char *country = NULL;
	char buf[N];
	
	printf("Input title of changed data: ");
	if (scanf("%30s", buf) == 1)
	{
		while(head && strcmp(head->title, buf) != 0)
		{
			head = head->next;
		}
		if (!head)
		{
			printf("no element with this title!\n");
			return;
		}
		printf("Input new data:(title;author;country;year):");
		gets(buf);
		if (read_data(stdin, &title, &author, &year, &country) == OK)
		{
			change(head, sort_head, head_filter, title, author, year, country);
		}
		else 
		{
			printf("Input error\n");
		}
	}
	else 
	{
		printf("Input error\n");
	}
}
