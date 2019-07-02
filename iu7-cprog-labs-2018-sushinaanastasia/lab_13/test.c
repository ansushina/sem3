#include"process.h"
#include"io.h"
#include"errors.h"

// стравним структуры по данным
int cmp_st(film_st *h1, film_st*h2)
{
	if (!h1 && !h2)
		return 1;
	if (!h1 || !h2)
		return 0;
	if (strcmp(h1->title, h2->title) != 0)
		return 0;
	if (strcmp(h1->author, h2->author) != 0)
		return 0;
	if (strcmp(h1->country, h2->country) != 0)
		return 0;
	if (h1->year != h2->year)
		return 0;
	return 1;
}
// сравнение по сортировкам 
int cmp_sort(film_st *head, int i, film_st *h2)
{
    if (!head && !h2)
		return 1;
	if (!head || !h2)
		return 0;
	film_st *item = head;
    struct list_head *iter;
    film_st *mas[10]; //пусть тут хранятся указатели на структуры 1 списка
	int j = 1;
	if (!cmp_st(head, h2))
		return 0;

    list_for_each(iter, &(head->sort[i])) // найдем и запишем все структуры
    {
		item = list_entry(iter, film_st, sort[i]);
		mas[j] = item;
		j++;
    }
    j = 1;
	
	list_for_each(iter, &(h2->sort[i])) // сравним структуры с структурами второго списка
    {
		item = list_entry(iter, film_st, sort[i]);
		
		if (!cmp_st(item, mas[j]))
			return 0;
		j++;
    }
	
	return 1;
}
int cmp_filter(film_st *head, int i, film_st *h2)
{
    if (!head && !h2)
		return 1;
	if (!head || !h2)
		return 0;
	film_st *item = head;
    struct list_head *iter;
    film_st *mas[10]; //пусть тут хранятся указатели на структуры 1 списка
	int j = 1;
    //printf("8");
	if (!cmp_st(head, h2))
		return 0;
    //printf("9");
    list_for_each(iter, &(head->filter[i])) // найдем и запишем все структуры
    {
		item = list_entry(iter, film_st, filter[i]);
		mas[j] = item;
		j++;
    }
    j = 1;
	
	list_for_each(iter, &(h2->filter[i])) // сравним структуры с структурами второго списка
    {
		item = list_entry(iter, film_st, filter[i]);
		
		if (!cmp_st(item, mas[j]))
			return 0;
		j++;
    }
	
	return 1;
}

int is_eq(film_st *h1, film_st *h2, film_st *sort_head[MAX_SORT_INDX],
	film_st *head_filter[MAX_FILTER_INDX], film_st *s_head[MAX_SORT_INDX],
	    film_st *head_f[MAX_FILTER_INDX])
{
	if (!h1 && !h2)
		return 1;
	if (!h1 || !h2)
		return 0;
	while (h1 && h2)//сначала сравним обычные списки
	{
		if (!cmp_st(h1, h2))
		    return 0;
		h1 = h1->next;
		h2 = h2->next;
	}
	//printf("1");
	for (int i = 0; i < 3; i++) // сравним по отстортированности
	{
		if (!cmp_sort(sort_head[i], i, s_head[i]))
			return 0;
	}
	//printf("2");
	for (int i = 0; i < MAX_FILTER_INDX; i++)
	{
		if (!cmp_filter(head_filter[i], i, head_f[i]))
			return 0;
	}
	return 1;
}

void test_add()
{
	// так как функция add ипользуется при считывании их файла, достаточно проверить,
	// что после считывания все сортировки и фильтры будут правильными
	// в этой функции тестируются сразу все три сортировки, два фильтра,
	// а так же правильность считывания и добавляения элемента в структуру
	printf("TEST ADD:\n");
	{
		film_st *head = NULL;
	    film_st *sort_head[MAX_SORT_INDX] = {NULL};
	    film_st *head_filter[MAX_FILTER_INDX] = {NULL};
		
		char t[30][30] = {"a","b","f"}; //названия
	    char a[30][30] = {"b","f","a"}; //авторы
		char c[30][30] = {"f","a","b"}; //страны
		unsigned short y[30] = {1000,6000,300}; //года
		int n = 3;
		//структура с которой будем сравнивать
		film_st *h = NULL;
	    film_st *s_head[MAX_SORT_INDX] = {NULL};
	    film_st *head_f[MAX_FILTER_INDX] = {NULL}; 
		
		film_st *p = h;
		film_st *mas[3]; //пусть тут хранятся указатели на все три структуры
		// заполняем обычный список и запоминаем все элементы 
		for (int i = 0; i < n ; i++)
		{
			film_st *new = create_struct(t[i], a[i], y[i], c[i]);
			if (!p)
			{
				p = new;
				h = new;
			}
			else
			{
			    p->next = new;
			    p = new;
			}
			mas[i] = new;
		}
		//год страна автор
		s_head[0] = mas[2];s_head[1] = mas[1];s_head[2] = mas[0];head_f[0]=mas[0];head_f[1]=mas[1];
        // заполняем первую сортировку
		list_add(&(mas[0]->sort[0]), &(mas[2]->sort[0]));
		list_add(&(mas[1]->sort[0]), &(mas[0]->sort[0]));
        // вторая сортировка
		list_add(&(mas[2]->sort[1]), &(mas[1]->sort[1]));
		list_add(&(mas[0]->sort[1]), &(mas[2]->sort[1]));
		// треться ссортировка
		list_add(&(mas[1]->sort[2]), &(mas[0]->sort[2]));
		list_add(&(mas[2]->sort[2]), &(mas[1]->sort[2]));
		// первый фильтр 
		list_add(&(mas[1]->filter[0]), &(mas[0]->filter[0]));
		list_add(&(mas[2]->filter[0]), &(mas[1]->filter[0]));
		// второй фильтр
		//list_add(&(mas[0]->filter[0]), &(mas[1]->filter[0]));
        //print_filter(stdout,head_f[1], 1);
		 
		//print_normal(stdout,h);
		FILE *f = fopen("test1.txt","r");
	    read_data_from_file(f, &head, sort_head, head_filter);
	 	fclose(f);
		//print_filter(stdout,head_filter[1], 1);
		//print_sort(stdout,sort_head[0], 0);
		//print_normal(stdout,head);
		printf("TEST 1: ");
		if (is_eq(head, h, sort_head, head_filter, s_head, head_f))
			printf("OK\n");
		else
			printf("FAIL\n");
		free_list(head);

	    while (h)
	    {
	    	p = h;
	    	h = h->next;
	    	free(p);
	    }
	}
}


void test_del()
{
	printf("TEST DELETE: \n");
	{
		film_st *head = NULL;
	    film_st *sort_head[MAX_SORT_INDX] = {NULL};
	    film_st *head_filter[MAX_FILTER_INDX] = {NULL};
		FILE *f = fopen("test2.txt","r");
	    read_data_from_file(f, &head, sort_head, head_filter);
	 	fclose(f);
		
		film_st *head1 = NULL;
	    film_st *sort_head1[MAX_SORT_INDX] = {NULL};
	    film_st *head_filter1[MAX_FILTER_INDX] = {NULL};
		FILE *f1 = fopen("res2.txt","r");
	    read_data_from_file(f1, &head1, sort_head1, head_filter1);
	 	fclose(f1);
		
		head = del_st(head, "b", sort_head, head_filter);
		
		//print_normal(stdout,head);
		//print_filter(stdout,head_filter[1], 1);
		//print_filter(stdout,head_filter1[1], 1);
		//print_normal(stdout,head1);
		printf("TEST 1: ");
		if (is_eq(head, head1, sort_head, head_filter, sort_head1, head_filter1))
			printf("OK\n");
		else 
			printf("FAIL\n");
		free_list(head);
		free_list(head1);
	}
	//удаляем голову
	{
		film_st *head = NULL;
	    film_st *sort_head[MAX_SORT_INDX] = {NULL};
	    film_st *head_filter[MAX_FILTER_INDX] = {NULL};
		FILE *f = fopen("test4.txt","r");
	    read_data_from_file(f, &head, sort_head, head_filter);
	 	fclose(f);
		
		film_st *head1 = NULL;
	    film_st *sort_head1[MAX_SORT_INDX] = {NULL};
	    film_st *head_filter1[MAX_FILTER_INDX] = {NULL};
		FILE *f1 = fopen("res4.txt","r");
	    read_data_from_file(f1, &head1, sort_head1, head_filter1);
	 	fclose(f1);
		
		head = del_st(head, "a", sort_head, head_filter);
		
		//print_normal(stdout,head);
		//print_filter(stdout,head_filter[1], 1);
		//print_filter(stdout,head_filter1[1], 1);
		//print_normal(stdout,head1);
		printf("TEST 2: ");
		if (is_eq(head, head1, sort_head, head_filter, sort_head1, head_filter1))
			printf("OK\n");
		else 
			printf("FAIL\n");
		free_list(head);
		free_list(head1);
	}
}

void test_change()
{
	printf("TEST CHANGE: \n");
	{
		film_st *head = NULL;
	    film_st *sort_head[MAX_SORT_INDX] = {NULL};
	    film_st *head_filter[MAX_FILTER_INDX] = {NULL};
		FILE *f = fopen("test3.txt","r");
	    read_data_from_file(f, &head, sort_head, head_filter);
	 	fclose(f);
		
		film_st *head1 = NULL;
	    film_st *sort_head1[MAX_SORT_INDX] = {NULL};
	    film_st *head_filter1[MAX_FILTER_INDX] = {NULL};
		FILE *f1 = fopen("res3.txt","r");
	    read_data_from_file(f1, &head1, sort_head1, head_filter1);
	 	fclose(f1);
		
		film_st * h = head;
		while(h && strcmp(h->title, "b") != 0)
		{
			h = head->next;
		}
		change(h, sort_head, head_filter, "o", "o",122, "o");
		
		print_normal(stdout,head);
		print_filter(stdout,head_filter[0], 0);
		print_filter(stdout,head_filter1[0], 0);
		print_normal(stdout,head1);
		print_sort(stdout,sort_head[1], 1);
		print_sort(stdout,sort_head1[1], 1);
		printf("TEST 1: ");
		if (is_eq(head, head1, sort_head, head_filter, sort_head1, head_filter1))
			printf("OK\n");
		else 
			printf("FAIL\n");
		free_list(head);
		free_list(head1);
	}
}


int main()
{
	setbuf(stdout, NULL);
	test_add();
	test_del();
	test_change();
	return 0;
}