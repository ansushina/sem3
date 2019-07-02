/*
Программа работает с базой данных, содержащей название книги и имя автора.
Выполняет следующие функции: удаление первого элемента, переворот, сортировку слиянием о имени автора,
 вставку элемента перед определеныым. 
*/


#include"errors.h"
#include"process.h"
#include"io.h"

int main(int argc, char *argv[])
{
	FILE *f, *f2; 
	node_t *head;
	struct b *data, *data1;
	int rc;
	
	setbuf(stdout, NULL);
	
	if (argc != 4 && argc != 7)
	{
		printf("./app.exe in.txt out.txt -action\n");
		printf("actions: \n -p pop_front\n -r reverse\n -s sort\n");
		printf(" -i <name> <author> <i-before>");
		return ERR_PARAM;
	}
	
	if (strcmp(argv[3], "-p") == 0)
	{
		f = fopen(argv[1], "r");
		if (f)
		{
			f2 = fopen(argv[2], "w");
			if (f2)
			{
		        rc = read_data_from_file(f, &head, &data);
		    	if (rc == OK)
		    	{
		    	    print_to_file(stdout, head);
		    		data1 = pop_front(&head);
		    		print_to_file(stdout, head);
					print_to_file(f2, head);
		    		printf("%s %s \n", data1->name, data1->author);
					free_list(head);
					free(data);
		    	}
		    	else if (rc == ERR_NULL)
		    	{
		    		printf("Empty file!\n");
		    	}
			    else
		    	{
		    		printf("Memory error!\n");
		    	}
				fclose(f2);
			}
			else 
			{
				printf("file 2 can't be open!\n");
			    rc = ERR_IO;
			}
			fclose(f);
		}
		else 
		{
			printf("file can't be open!\n");
			rc = ERR_IO;
		}
	}
	else if (strcmp(argv[3], "-r") == 0)
	{
		f = fopen(argv[1], "r");
		if (f)
		{
			f2 = fopen(argv[2], "w");
			if (f2)
			{
		        rc = read_data_from_file(f, &head, &data);
			    if (rc == OK)
			    {
			        print_to_file(stdout, head);
				 
				    head = reverse(head);
				
				    print_to_file(stdout, head);
					print_to_file(f2, head);
					
				    free_list(head);
				    free(data);
			    }
			    else if (rc == ERR_NULL)
			    {
			    	printf("Empty file!\n");
			    }
			    else
			    {
			    	printf("Memory error!\n");
			    }
			    
				fclose(f2);
			}
			else 
			{
				printf("file 2 can't be open!\n");
			    rc = ERR_IO;
			}
			fclose(f);
		}
		else 
		{
			printf("file can't be open!\n");
			rc = ERR_IO;
		}
	}
	else if (strcmp(argv[3], "-s") == 0)
	{
		f = fopen(argv[1], "r");
		if (f)
		{
			f2 = fopen(argv[2], "w");
			if (f2)
			{
		        rc = read_data_from_file(f, &head, &data);
			    if (rc == OK)
			    {
			        print_to_file(stdout, head);
				
			    	head = sort(head, cmp_structs);
				
			        print_to_file(stdout, head);
					print_to_file(f2, head);
					
					free_list(head);
			    	free(data);
			    }
			    else if (rc == ERR_NULL)
			    {
			    	printf("Empty file!\n");
			    }
			    else
			    {
			    	printf("Memory error!\n");
			    }
			    fclose(f2);
			}
			else 
			{
				printf("file 2 can't be open!\n");
			    rc = ERR_IO;
			}
			fclose(f);
		}
		else 
		{
			printf("file can't be open!\n");
			rc = ERR_IO;
		}
	}
	else if (argc == 7 && strcmp(argv[3], "-i") == 0)
	{
		f = fopen(argv[1], "r");
		if (f)
		{
			f2 = fopen(argv[2], "w");
			if (f2)
			{
		        rc = read_data_from_file(f, &head, &data);
		    	if (rc == OK)
		    	{
		    		if (atoi(argv[6]) != 0 || strcmp(argv[6], "0") == 0)
		    		{
		    	        struct b new;
		    			int u = atoi(argv[6]);
		    			//printf("%d ", u);
			    		strcpy(new.name, argv[4]);
			    		strcpy(new.author, argv[5]);
			    		
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
			    	        print_to_file(stdout, head);
						    print_to_file(f2, head);
			    		}
		    			else 
		    			{
		    				printf("too big last parametr\n");
		    			    rc = ERR_PARAM;
		    			}
		    		}
		    		else 
		    		{
		    			printf("last parametr must be int\n");
		    			rc = ERR_PARAM;
			    	}
					free_list(head);
		    		free(data);
		    	}
		    	else if (rc == ERR_NULL)
		    	{
		    		printf("Empty file!\n");
	    		}
	    		else
			    {
			    	printf("Memory error!\n");
			    }
			    fclose(f2);
			}
			else 
			{
				printf("file 2 can't be open!\n");
			    rc = ERR_IO;
			}
			fclose(f);
		}
		else 
		{
			printf("file can't be open!\n");
			rc = ERR_IO;
		}
	}
	else 
	{
		printf("./app.exe in.txt out.txt -action");
		printf("actions: \n -p pop_front\n -r reverse\n -s sort\n");
		printf(" -i <name> <author> <i-before>");
		rc = ERR_PARAM;
	}
	return rc;
}