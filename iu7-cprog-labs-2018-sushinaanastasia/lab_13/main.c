#include"process.h"
#include"io.h"
#include"errors.h"

/**
 * @brief menu
 * Печатает меню программы
 */
void menu()
{
	printf("\n1. load from file\n");
	printf("2. add record\n");
	printf("3. Del record by name\n");
	printf("4. Change data\n");
	printf("5. print sorted\n");
	printf("6. print filter\n");
	printf("7. print normal\n");
	printf("8. exit\n\n");
}

int main()
{
	setbuf(stdout, NULL);
	int rc = OK;
	int a; 
	char buf[N + 1];
	film_st *head = NULL;
	film_st *sort_head[MAX_SORT_INDX] = {NULL};
	film_st *head_filter[MAX_FILTER_INDX] = {NULL};
	film_st *new;
	char *title = NULL; 
	char *author = NULL; 
	unsigned short year; 
	char *country = NULL;
	
	int k = 1;
	while(k)
	{
		menu();
		printf("Input action: ");
		if (scanf("%d", &a) == 1)
		{
			gets(buf);
			if (a == 1)
			{
				rc = read_filename(buf);
				if (rc == OK)
				{
					FILE *f = fopen(buf, "r");
					//printf("%s", buf);
					if (f)
				    {
					    rc  =  read_data_from_file(f, &head, sort_head, head_filter);
					    fclose(f);
					    if (rc == OK)
					    {
						    print_normal(stdout, head);
					    }
						else
							printf("Memory error!\n");
					}
					else
					{
						printf("can't open file!\n");
					}
				}
				else 
				{
					printf("Input error!\n");
				}
			}
			else if (a == 2)
			{
				printf("Input data(title;author;country;year): ");
				if (read_data(stdin,&title, &author, &year, &country) == OK)
				{
					new  = create_struct(title, author, year, country);
		            if (new)
	               	{
		            	head = add(head, new, sort_head, head_filter);
	              	}
					else 
						printf("memory error!\n");
				}
				else 
    				printf("Input error!\n");
			}
			else if (a == 8)
			{
				k = 0;
			}
			else if (a == 5)
			{
				print_sort(stdout, sort_head[0], 0);
	            print_sort(stdout, sort_head[1], 1);
	            print_sort(stdout, sort_head[2], 2);
			}
			else if (a == 6)
			{
				print_filter(stdout, head_filter[0], 0);
	            print_filter(stdout, head_filter[1], 1);
			}
			else if (a == 7)
			{
				print_normal(stdout, head);
			}
			else if (a == 3)
			{
				if (!head)
				{
					printf("Nothing to del!\n");
					continue;
				}
				printf("Input title you want do del: ");
				if (scanf("%s", buf) == 1)
				{
				    head = del_st(head, buf, sort_head, head_filter);
				}
				else 
				{
					printf("Input error\n");
				}
			}
			else if (a == 4)
			{
				if (!head)
				{
					printf("Nothing to change!\n");
					continue;
				}
				change_data(head, sort_head, head_filter);
			}
		}
		else 
		{
			gets(buf);
			printf("Input error!\n");
		}
	}
	free_list(head);
	return rc;
}
