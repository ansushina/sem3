#include"io.h"
#include"process.h"

node_t *sum(node_t *head1, node_t *head2)
{
	if (!head1 && !head2)
	{
		return NULL;
	}
	if (!head1)
		return head2;
	if (!head2)
		return head1;
	unsigned int k = 0;
	unsigned int u = 0;
	node_t *head = NULL;
	node_t *new = NULL;
	while (head1 || head2)
	{
		if (!head2)
		{
			k += (head1->n);
		    head1 = head1->next;
		}
		else if (!head1)
		{
			k += (head2->n);
		    head2 = head2->next;
		}
		else 
		{
		    k += (head1->n) + (head2->n);
		    head1 = head1->next;
		    head2 = head2->next;
		}
		u = k % 10;
		k = k / 10;
		new = create_st(u);
		if (new)
		{
		    head = add_st(head, new);
		}
		else
		{
			free_list(head);
			return NULL;
		}
	}
	if (k)
	{
		new = create_st(k);
		if (new)
		{
		    head = add_st(head, new);
		}
		else
		{
			free_list(head);
			return NULL;
		}
	}
	return head;
	
}