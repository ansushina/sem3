//вариант 9
#include"io.h"
#include"process.h"

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);
	int rc;
	node_t *head1, *head2, *summa;
	
	if (argc != 3)
	{
		printf("app.exe in_1.txt in_2.txt");
		return 1;
	}
	
	FILE *f1 = fopen(argv[1], "r");
	if (f1)
	{
		rc = read_number(f1, &head1);
		if (rc == 0)
		{
		    printf("Number 1:\n");
		    print_st(head1);
	    	FILE *f2 = fopen(argv[2], "r");
	     	if (f2)
		    {
		    	rc = read_number(f2, &head2);
				if (rc == 0)
				{
		            printf("Number 2:\n");
		            print_st(head2);
					summa = sum(head1, head2);
					if (summa)
					{
						printf("SUM:\n");
		                print_st(summa);
						printf("ANSWER: %u\n", make_number(summa));
						
						printf("%u + %u = %u", make_number(head1), make_number(head2), make_number(summa));
			
						free_list(summa);
					}
					free_list(head2);
				}
				else
				{
					printf("MEMORY ERROR\n");
				}
	    	}
	     	else
		    {
		    	printf("file 2 can't be open\n");
		        rc = 1;
		    }
			free_list(head1);
		}
		else 
		{
			printf("ERR_MEMORY\n");
		}
		fclose(f1);
	}
	else 
	{
		printf("file 1 can't be open\n");
		rc = 1;
	}
	
	return rc;
}