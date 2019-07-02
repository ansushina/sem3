#include"errors.h"
#include"process.h"
#include"io.h"

int count(node_t *head)
{
	int n = 0;
	node_t *t2 = head;
	while (t2->next)
	{
		t2 = t2->next;
		n++;
	}
	n++;
	return n;
}


/**
 * @brief pop_front
 * удаляет первый элемент
 * @param head [in] - список
 * @return указатель на первый элемент
 */
void *pop_front(node_t **head)
{
	if (!head || !(*head))
		return NULL;
	node_t *k = *head;
	void *p = k->data;
	*head = k->next;
	free(k);
	return p;
}

/**
 * @brief insert
 * вставляет элемент перед before
 * @param head [in] - список
 * @param elem [in] - элемент
 * @param before [in ] - элемент перед которым нужно встаивть
 */
void insert(node_t **head, node_t *elem, node_t *before)
{
	node_t *c = *head;
	//printf("insert \n");
	
	if (c == before)
	{
		elem->next = before;
		*head = elem;
		return;
	}
	while (c)
	{
		//printf("i");
		if(c->next == before)
		{
	        elem->next = before;
	        c->next = elem;
			break;
		}
		//print_h(c);
		c = c->next;
	}
}

/**
 * @brief reverse
 * переворачивает список с помощью трех указателей
 * @param head [список]
 * @return указатель на первый элемет списка
 */
/*node_t *reverse(node_t *head)
{
	if (!head)
		return NULL;
	if (!(head->next))
		return head;
	node_t *t1,*t2,*t3, *t4;
	t4 = head;
	
	t1 = head;
	t2 = head->next;
	t3 = head->next->next;
	int i = 0;
	//printf("%d ", n);
	while (t4)
	{
		
		//printf("%d ", i);
		t2->next = t1;
		t1->next = t3;
		head = t2;
		t1 = head;
		t2 = head->next;
		t3 = head->next->next;
		//printf("1\n");
		//print_h(t1);
		//printf("\n");
		//for(int j = 0; j < n-2-i; j++)
		t4 = t3;
	    for (int j = 0; j < i; j++)
		   t4 = t4->next;
		while(t4)
		{
			t1->next = t3;
			t2->next = t3->next;
			t3->next = t2;
			
			//printf("2\n");
		    //print_h(t1);
		    //printf("\n");
			t1 = t3;
			t3 = t2->next;
			t4 = t3;
	        for (int j = 0; j < i; j++)
		        t4 = t4->next;
		}
		//printf("3\n");
		//print_h(head);
		//printf("\n");
		t1 = head;
	    t2 = head->next;
	    t3 = head->next->next;
	    i++;
		t4 = t2;
		for (int j = 0; j < i; j++)
		   t4 = t4->next;
	}
    return head;
}*/

node_t *reverse(node_t *head)
{
	if (!head)
		return NULL;
	if (!(head->next))
		return head;
	
	node_t *t1,*t2,*t3; 
	
	t1 = NULL;
	t2 = head;
	t3 = head->next;
	while(t3)
	{
		t2->next = t1;
		
		t1 = t2;
		t2 = t3;
		t3 = t3->next;
	}
	t2->next = t1;
	return t2;
}


/**
 * @brief cmp_books
 * компоратор для сортировки книг по автору
 * @param a1 [in] указатель на первую структуру
 * @param b1 [in] указатель на вторую структуру
 * @return результат сравнения
 */
int cmp_structs(const void *a1, const void *b1)
{
	const struct b *a = a1;
	const struct b *b = b1;
	//printf("compare\n");
	
	return (strcmp(a->author, b->author));
}

/**
 * @brief front_back_split
 * делит список на два примерно равной длины
 * @param head [in] список
 * @param back [out] указатель на вторую часть
 */
void front_back_split(node_t *head, node_t **back)
{
	if (!head || !back)
		return;
	
	node_t *b = head;
	
	int i = 0;
	//printf("iteration");
	while(head->next && head->next->next)
	{
		//printf("%d\n", i);
		b = b->next;
		head = head->next->next;
		i++;
	}
	
	*back = b->next;
	b->next = NULL;
	
}

/**
 * @brief sorted_merge
 * слияние двух списков в один отсорированный
 * @param head_a [in] первый список
 * @param head_b [in] второй список
 * @return отсортированный список
 */
node_t *sorted_merge(node_t **head_a, node_t **head_b,
    int (*comparator)(const void *, const void *))
{
	if (!comparator)
	{
	    return NULL;
	}
	
	if (!head_a || !head_b)
		return NULL;
		
	node_t *a = *head_a, *b = *head_b, *c, *head = NULL;
	
	if (a || b)
	{
	    if (!b || (a && comparator(a->data, b->data) < 0))
		{
			head = a;
			c = head;
			a = a->next;
		}
		else if (b)
		{
			head = b;
			c = head;
			b = b->next;
		}
	}
		
	
	while(a && b)
	{
		if (comparator(a->data, b->data) < 0)
		{
			c->next = a;
		    c = c->next;
			a = a->next;
		}
		else 
		{
			c->next = b;
		    c = b;
			b = b->next;
		}
	}
	while (a)
	{
		c->next = a;
	    c = c->next;
		a = a->next;
	}
	while (b)
	{
		c->next = b;
	    c = b;    
		b = b->next;
	}
	*head_b = NULL;
	*head_a = NULL;
	return head;
}

/**
 * @brief sort
 * сортировка слиянием
 * @param head [in] список
 * @return отсортированный список
 */
node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
	if (!head)
		return head;
	if (!comparator)
		return 0;
	node_t *a, *b, *back, *new;
	//int n = count(head);
	if (!head || !head->next)
	    return head;
	front_back_split(head, &back);
	a = sort(head, comparator);
	b = sort(back, comparator);
	new = sorted_merge(&a, &b, comparator);
	return new;
}
