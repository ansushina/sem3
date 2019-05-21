#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define OK 0
#define ERR_READ 1
#define ERR_PARAM 2
#define ERR_MEMORY 3
#define ERR_NULL 4
#define ERR_RANGE 5
#define ERR_FILE 6
#define ERR_IO 7

#define N 2000

void menu()
{
	printf("\nActions:\n");
	printf("1. add new \n");
	printf("2. delete\n");
	printf("3. printf in reverse\n");
	//printf("4. new stek \n");
	printf("4. exit\n");
}

void info()
{
	printf("This program makes operations with stek\n");
    printf("\n");
}

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__("rdtsc" : "=A" (d));
	return d;
}

struct j
{
	char i[30+1];
	struct j *next;
};

struct j *create_j(char *s)
{
	struct j *p = malloc(sizeof(struct j));
	if (p)
	{
		strcpy(p->i, s);
		p->next = NULL;
	}
	return p;
}

struct j *add_j(struct j *head, struct j *pj)
{
	
	if (!head)
		return pj;
	pj->next = head;
	return pj;
}

void free_list(struct j *head)
{
	struct j *p;
	while (head->next)
	{
		p = head;
		head = head->next;
		free(p);
	}
}

void add_m(char (**p)[30+1], char *buf)
{
	//char *p1 = *p;
	*p = *p + 1;
	strcpy(**p, buf);
}

void add_s(struct j **head, struct j **full, char *buf)
{
	struct j *head1 = *head;
	struct j *new = create_j(buf);
	if (new)
	{
	    *head = add_j(head1, new);
	}
	int i;
	for (i = 0; full[i]; i++);
	full[i] = new;
}


void read_new(char (**p)[30+1], struct j **head, struct j **full)
{
	char buf[30+1];
	long int tb, te;
	int k = 1; 
	while (k)
	{
		printf("Input word(30 signs) : ");
		if (scanf("%s", buf) == 1)
	    {
			//printf("%s\n", buf);
			if (strlen(buf) < 30)
			{
			    k = 0;
			}
			else
				printf("Too big str!\n");
		}
		else
			printf("Input Error!\n");
	}
	printf("\n");
	tb = tick();
	add_m(p, buf);
	te = tick();
	printf("time massiv: %d\n", te - tb);
	tb = tick();
	add_s(head, full, buf);
	te = tick();
	printf("time spisok: %d\n", te - tb);
	
}

void print_stack(struct j *head)
{
	printf("\nStack:\n ");
	struct j *t = head;
	while (t)
	{
		printf("%s\n", t->i);
		t = t->next;
	}
	printf("\n");
}

void pop_s(struct j **head, struct j **empty, char *buf)
{
	//char *buf = malloc(sizeof(char)*(strlen(tmp->i) + 1));
	struct j *tmp = *head;
	strcpy(buf, tmp->i);
    *head = tmp->next;
	
	int i;
	for (i = 0; empty[i]; i++);
	empty[i] = tmp;
	
    free(tmp);
    //return	buf;
}

void pop_m(char (**p)[30+1], char *buf)
{
	//char *buf = malloc(sizeof(char)*(strlen(*p) + 1));
	//printf("p %s \n", buf);
	
	strcpy(buf, **p);
	//printf("p %s \n", buf);

	*p = *p - 1;
    //return buf;
}

void print_reverse_s(struct j *head)
{
	struct j *newhead = NULL;
	char buf[31];
	struct j *empty[N] = {NULL};
	struct j *full[N] = {NULL};
	printf("\n");
	while(head)
	{
		printf("%u ", (void *) head);
		pop_s(&head, empty, buf);
		printf("%s\n", buf);
		add_s(&newhead, full, buf);
	}
	while(newhead)
	{
		pop_s(&newhead, empty, buf);
		//printf("%s\n", buf);
		add_s(&head, full, buf);
	}
    printf("\n");	
}

void print_reverse_m(char (*p)[30+1], int n)
{
	char stek2[N][31];
	char (*p2)[31];
	char buf[31];
	p2 = stek2;
	p2--;
	printf("\n");
	
	for (int i = 0; i < n; i++)
	{
		//printf("%u ", (void *) p);
		pop_m(&p, buf);
		printf("%s\n", buf);
		add_m(&p2, buf);
	}
	for (int i = 0; i < n; i++)
	{
		pop_m(&p2, buf);
		//printf("%s\n", buf);
		add_m(&p, buf);
	}
	printf("\n");
}

void t()
{
	struct j *head = NULL;
	struct j *headmax = NULL;
	long int tb, te;
	long int t1, t2;
	int action, rc;
	char buf[31];
	char *b;
	int nmax, n = 0;
	char stek1[N][31];
	char (*p)[31];
	struct j *full[N] = {NULL};
	struct j *empty[N] = {NULL};
	p = stek1;
	p--;
	
	tb = tick();
	for (int i  = 0; i < 1000; i++ )
	{
		add_m(&p, "uuuuuuuuuuuuuuuu");
	}
	te = tick();
	printf("time %d ", (te-tb));
	tb = tick();
	for (int i  = 0; i < 1000; i++ )
	{
		add_s(&head,full, "uuuuuuuuuuuuuuuu");
	}
	te = tick();
	printf("time %d ", (te-tb));
	
	tb = tick();
	for (int i  = 0; i < 1000; i++ )
	{
		pop_m(&p, buf);
	}
	te = tick();
	printf("time %d ", (te-tb)/ 1000);
	tb = tick();
	for (int i  = 0; i < 1000; i++ )
	{
		pop_s(&head, empty, buf);
	}
	te = tick();
	printf("time %d ", (te-tb)/ 1000);


}

int main()
{
	setbuf(stdout, NULL);
	srand(time(NULL));
	struct j *head = NULL;
	struct j *headmax = NULL;
	long int tb, te;
	long int t1, t2;
	int action, rc;
	char buf[31];
	char *b;
	int nmax, n = 0;
	char stek1[N][31];
	char (*p)[31];
	struct j *full[N] = {NULL};
	struct j *empty[N] = {NULL};
	p = stek1;
	p--;
	info();
	
	printf("Input number of elements: ");
	if (scanf("%d", &nmax) != 1 || nmax <= 0)
	{
		printf("Input error");
		return ERR_IO;
	}
	
	int k = 1;
	while (k)
	{
		menu();
		printf("Input action(number): ");
		if (scanf("%d", &action) == 1)
		{
			printf("\n");
            if (action == 4)
				k = 0;
			else if (action == 1)
			{
				if (p < stek1 + nmax - 1)
				{
					//printf("%u \n", (void *)p);
				    read_new(&p, &head, full);
                    //printf("%u \n", (void *)p);
					//print_stack(head);
					n++;
					
					/*for (int i = 0; i < n; i++)
						printf("mas %s\n", stek1[i]);*/
					
					printf("\nFULL: \n");
					for (int i = 0; i < N; i++)
					{
						if (full[i])
						    printf("%u \n", (void *)full[i]);
					}
					for (int i = 0; i < N; i++)
					{
					    if (empty[i] == head)	
					    {
							empty[i] = NULL;
						}
					}
				}
				else
				{
					printf("FULL STACK\n");
				}
			
			}
			else if (action == 2)
			{
				for (int i = 0; i < N; i++)
				{
					if (full[i] == head)	
					{
				    	full[i] = NULL;
				    }
				}
				
				if (head)
				{
					tb = tick();
				    pop_s(&head, empty, buf);
					te = tick();
				    printf("\nspisok delete %s\n", buf);
					printf("time spisok: %d\n", te - tb);
				}
				else 
					printf("Empty stack\n");
				if (p != stek1 - 1)
				{
					tb = tick();
				    pop_m(&p, buf);
					te = tick();
				    printf("\nmassiv delete %s\n", buf);
					printf("time massiv: %d\n", te - tb);
				}
				else
					printf("Empty stak\n");
				
				printf("\nEPMTY:\n");
				for (int i = 0; i < N; i++)
				{
					if (empty[i])	
					{
						printf("%u \n",(void *)empty[i]);
					}
				}
			}
			else if (action == 3)
			{
				printf("spisok reverse:\n ");
				
				tb = tick();
				print_reverse_s(head);
				te = tick();
				t1 = te-tb;
				
				printf("massiv reverse\n");
				tb = tick();
				print_reverse_m(p, p - stek1 + 1 );
				te = tick();
				t2 = te-tb;
				printf("time spisok: %d\ntime massiv: %d\n", t1, t2);
				long int tt = 100 * t1/t2;
				printf("Spisok time is %d of massiv time \n", tt);
				printf("Memory massiv: %d\n", sizeof(char [31])*n);
				printf("Memory spisok: %d\n", sizeof(struct j)*n);
			}
			else if (action == 4)
			{
				for (int i = 0; i < N; i++)
	            {
		            if (full[i])
			            free(full[i]);
					full[i] = NULL;
	            }
				for (int i = 0; i < N; i++)
				{
					if (empty[i])	
					{
						empty[i] = NULL;
					}
				}
				p = stek1;
	            p--;
	            struct j *head = NULL;
			}
		} 
		else 
		{
			gets(buf);
		    printf("\nInput error\n\n");
		}
	}
	
	t();
	for (int i = 0; i < N; i++)
	{
		if (full[i])
			free(full[i]);
	}
	
	return 0;
}