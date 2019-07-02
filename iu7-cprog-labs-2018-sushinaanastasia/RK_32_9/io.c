#include"io.h"
//#include"process.h"
#include<math.h>

int read_number(FILE *f, node_t **head)
{
	if (!f)
		return 1;
	node_t *begin = NULL;
	node_t *new = NULL;
	unsigned int n;
	if (fscanf(f, "%u", &n) == 1)
	{
		if (n > 0)
		{
		    int k = n;
			while (n)
			{
				k = n % 10;
				n = n / 10;
				new = create_st(k);
				if (new)
				{
				    begin = add_st(begin, new);
				}
				else
				{
					free_list(begin);
					return 2;
				}
			}
			*head = begin;
		}
		else if (n == 0)
		{
			new = create_st(n);
			if (new)
			{
			   begin = add_st(begin, new);
			}
			else
			{
				free_list(begin);
				return 2;
			}
			*head = begin;
		}
	}
	else 
		return 2;
	return 0;
}

node_t *create_st(unsigned int n)
{
	node_t *new = malloc(sizeof(node_t));
	if (new)
	{
		new->n = n;
		new->next = NULL;
	}
    return new;
}

node_t *add_st(node_t *head, node_t *newst)
{
	if (!head)
		return newst;
	
	node_t *k = head;
	while (k->next)
	{
		k = k->next;
	}
	k->next = newst;
	return head;
}

void free_list(node_t *head)
{
	node_t *k;
	if (head)
	{
		while(head)
		{
			k = head;
			head = head->next;
			free(k);
		}
	}
}

unsigned int make_number(node_t *head)
{
	int i = 0; 
	unsigned int n = 0;
	while (head)
	{
		n += pow(10, i) * (head->n);
		i++;
		head = head->next;
	}
	return n;
}

void print_st(node_t *head)
{
	while (head->next)
	{
		printf("%d -> ", head->n );
		head = head->next; 
	}
	printf("%d \n", head->n);
}