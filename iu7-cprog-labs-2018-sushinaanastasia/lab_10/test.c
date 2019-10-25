#include"errors.h"
#include"process.h"
#include"io.h"

int cmp1(const void *a1, const void *b1)
{
	const struct b *a = a1;
	const struct b *b = b1;
	//printf("compare\n");
	
	return strcmp(a->author,b->author) + strcmp(a->name,b->name) ;
}

int compare_struct(node_t *head1, node_t *head2)
{
	if (!head1 && !head2)
		return 0;
	if (!head1 || !head2)
		return 1;
	int n1 = count(head1);
	int n2 = count(head2);
	
	if (n1 != n2)
	{
		//printf("not here");
		return 1;
	}
	for(int i = 0; i < n1; i++)
	{
		if (cmp1(head1->data, head2->data))
		{
			//printf("here");
			return 1;
		}
		head1 = head1->next;
		head2 = head2->next;
	}
	return 0;
}

void test_pop_front()
{
	printf("TEST POP FRONT\n");
	//несколько элементов
	{
		FILE *f, *f1; 
	    node_t *head;
	    struct b *data;
		f = fopen("test/in_1_p.txt", "r");
		read_data_from_file(f, &head, &data);
		fclose(f);
		
		node_t *head1;
	    struct b *data1;
		f1 = fopen("test/out_1_p.txt", "r");
		read_data_from_file(f1, &head1, &data1);
		fclose(f1);
		
		
		pop_front(&head);
		//print_h(head1);
		//print_h(head);
		
		printf("TEST1: ");
		if (!compare_struct(head, head1))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free_list(head);
		free(data);
		free_list(head1);
		free(data1);
	}
	//один элемент
	{
		FILE *f, *f1; 
	    node_t *head;
	    struct b *data;
		f = fopen("test/in_2_p.txt", "r");
		read_data_from_file(f, &head, &data);
		fclose(f);
		
		node_t *head1;
	    struct b *data1;
		f1 = fopen("test/out_2_p.txt", "r");
		read_data_from_file(f1, &head1, &data1);
		fclose(f1);
		
		
		pop_front(&head);
		//print_h(head1);
		//print_h(head);
		
		printf("TEST2: ");
		if (!compare_struct(head, head1))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free(data);
	}

}


void test_sort()
{
	printf("TEST SORT\n");
	//один элемент
	{
		FILE *f, *f1; 
	    node_t *head;
	    struct b *data;
		f = fopen("test/in_1_s.txt", "r");
		read_data_from_file(f, &head, &data);
		fclose(f);
		
		node_t *head1;
	    struct b *data1;
		f1 = fopen("test/out_1_s.txt", "r");
		read_data_from_file(f1, &head1, &data1);
		fclose(f1);
		
		
		head = sort(head, cmp_structs);
		//print_h(head1);
		//print_h(head);
		
		printf("TEST1: ");
		if (!compare_struct(head, head1))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free_list(head);
		free(data);
		free_list(head1);
		free(data1);
	}
	//два элемента
	{
		FILE *f, *f1; 
	    node_t *head;
	    struct b *data;
		f = fopen("test/in_2_s.txt", "r");
		read_data_from_file(f, &head, &data);
		fclose(f);
		
		node_t *head1;
	    struct b *data1;
		f1 = fopen("test/out_2_s.txt", "r");
		read_data_from_file(f1, &head1, &data1);
		fclose(f1);
		
		
		head = sort(head, cmp_structs);
		//print_h(head1);
		//print_h(head);
		
		printf("TEST2: ");
		if (!compare_struct(head, head1))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free_list(head);
		free(data);
		free_list(head1);
		free(data1);
	}
	//много элементов
	{
		FILE *f, *f1; 
	    node_t *head;
	    struct b *data;
		f = fopen("test/in_3_s.txt", "r");
		read_data_from_file(f, &head, &data);
		fclose(f);
		
		node_t *head1;
	    struct b *data1;
		f1 = fopen("test/out_3_s.txt", "r");
		read_data_from_file(f1, &head1, &data1);
		fclose(f1);
		
		
		head = sort(head, cmp_structs);
		//print_h(head1);
		//print_h(head);
		
		printf("TEST3: ");
		if (!compare_struct(head, head1))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free_list(head);
		free(data);
		free_list(head1);
		free(data1);
	}
}

void test_reverce()
{
	printf("TEST REVERSE\n");
	//один элемент
	{
		FILE *f, *f1; 
	    node_t *head;
	    struct b *data;
		f = fopen("test/in_1_r.txt", "r");
		read_data_from_file(f, &head, &data);
		fclose(f);
		
		node_t *head1;
	    struct b *data1;
		f1 = fopen("test/out_1_r.txt", "r");
		read_data_from_file(f1, &head1, &data1);
		fclose(f1);
		
		
		head = reverse(head);
		//print_to_file(stdout, head1);
		//print_to_file(stdout, head);
		
		printf("TEST1: ");
		if (!compare_struct(head, head1))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free_list(head);
		free(data);
		free_list(head1);
		free(data1);
	}
	//два элемента
	{
		FILE *f, *f1; 
	    node_t *head;
	    struct b *data;
		f = fopen("test/in_2_r.txt", "r");
		read_data_from_file(f, &head, &data);
		fclose(f);
		
		node_t *head1;
	    struct b *data1;
		f1 = fopen("test/out_2_r.txt", "r");
		read_data_from_file(f1, &head1, &data1);
		fclose(f1);
		
		
		head = reverse(head);
		//print_to_file(stdout, head1);
///print_to_file(stdout, head);
		//print_h(head1);
		//print_h(head);
		
		printf("TEST2: ");
		if (!compare_struct(head, head1))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free_list(head);
		free(data);
		free_list(head1);
		free(data1);
	}
	//несколько элементов
	{
		FILE *f, *f1; 
	    node_t *head;
	    struct b *data;
		f = fopen("test/in_3_r.txt", "r");
		read_data_from_file(f, &head, &data);
		fclose(f);
		
		node_t *head1;
	    struct b *data1;
		f1 = fopen("test/out_3_r.txt", "r");
		read_data_from_file(f1, &head1, &data1);
		fclose(f1);
		
		
		head = reverse(head);
		//print_to_file(stdout, head1);
		//print_to_file(stdout, head);
		//print_h(head1);
		//./print_h(head);
		
		printf("TEST3: ");
		if (!compare_struct(head, head1))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free_list(head);
		free(data);
		free_list(head1);
		free(data1);
	}
}

void test_insert()
{
	printf("TEST INSERT\n");
	{
		FILE *f, *f1; 
	    node_t *head;
	    struct b *data;
		f = fopen("test/in_1_r.txt", "r");
		read_data_from_file(f, &head, &data);
		fclose(f);
		
		node_t *head1;
	    struct b *data1;
		f1 = fopen("test/out_1_r.txt", "r");
		read_data_from_file(f1, &head1, &data1);
		fclose(f1);
		
		
		struct b new;
		int u = 2;
		strcpy(new.name, "book4");
		strcpy(new.author, "author4");
		
		node_t *n = create_struct(&new);
	
		int i = 0;
		node_t *h = head;
		while (h && i != u)
		{
			h = h->next;
			i++;
		}
    		
		if (h)
		{
			insert(&head, n, h);
		}
		
		printf("TEST1: ");
		if (!compare_struct(head, head1))
		{
			printf("OK\n");
		}
		else
			printf("FAIL\n");
		free(n);
		free_list(head);
		free(data);
		free_list(head1);
		free(data1);
	}
}
int main()
{
	setbuf(stdout, NULL);
	//printf("TEST1: ");
	test_pop_front();
	test_sort();
	test_reverce();
	test_insert();
	return 0;
}
