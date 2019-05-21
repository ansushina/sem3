
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define ERR_READ 1
#define ERR_PARAM 2
#define ERR_MEMORY 3
#define ERR_NULL 4
#define ERR_RANGE 5
#define ERR_FILE 6
#define ERR_IO 7
#define ERR_MULT 8

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__("rdtsc" : "=A" (d));
	return d;
}

struct j
{
	int i;
	struct j *next;
};

void zero_matrix(int **a, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
            a[i][j] = 0;			
}

void free_matrix(int **data, int n)
{
	//assert(data != NULL);
	//assert(n != 0);
	for (int i = 0; i < n; i++)
		free(data[i]);
	free(data);
}

int **allocate_normal_matrix(int n, int m)
{
	if (n == 0 || m == 0)
		return NULL;
	int **data = calloc(n, sizeof(int*));
	if (!data)
		return NULL;
	
	for (int i = 0; i < n; i++)
	{
		data[i] = calloc(m, sizeof(int));
		
		if (!data[i])
		{
			free_matrix(data, n);
			
			return NULL;
		}
	}
	
	return data;
}

void get_mul(int **a, int **b, int **c, int n, int m, int n2)
{
	zero_matrix(c, n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for (int r = 0; r < n2; r++)
				c[i][j] += a[i][r] * b[r][j];
}

int multiply_simple(int **a, int n1, int m1, int **b, int n2, int m2, int ***c)
{
	if (a == NULL || b == NULL)
		return ERR_NULL;
	if (n2 <= 0 || n1 <= 0 || m2 <= 0)
		return ERR_NULL;
	
	if (n2 == m1)
	{
		int **buf = allocate_normal_matrix(n1, m2);
		if (buf)
		{
			*c = buf;
			get_mul(a, b, *c, n1, m2, n2);
		}
		else
			return ERR_MEMORY;
	}
	else
		return ERR_MULT;
	return OK;
}

int multiply(int *b, int *bi, int n2, int count2, int *a, int *ai, struct j *head, int n, int m, int count, int **new)
{
    if (n2 != n)
		return 2;
	int h = 0, h1;
	int *d = malloc(m * sizeof(int));
	int *c = calloc(n, sizeof(int));
	for (int i = 0; i < m; i++)
	{
		d[i] = 0;
		h1 = h;
		for (int j = h; j < count && h < head->next->i; j++)
		{
			c[ai[j]] = h + 1;
			h++;
		}
		//for (int j = 0; j < n; j++)
			//printf("c - %d", c[j]);
		//printf("\n");
		
		for (int j = 0; j < count2; j++)
		{
			if (c[bi[j]] != 0)
				d[i] += b[j]*a[c[bi[j]] - 1];
			
		}
		for (int j = h1; j < count && h1 < head->next->i; j++)
		{
			c[ai[j]] = 0;
			h1++;
		}
		head = head->next;
		//printf("%d ", d[i]);
	}
	
	*new = d;
	free(c);
	return 0;
}

struct j *create_j(int i)
{
	struct j *p = malloc(sizeof(struct j));
	if (p)
	{
		p->i = i;
		p->next = NULL;
	}
	return p;
}

struct j *add_j(struct j *head, struct j *pj)
{
	
	if (!head)
		return pj;
	struct j *beg = head;
	while (head->next)
	{
		//printf("%p ", (void *) head->next);
		head = head->next;
	}
	head->next = pj;
	return beg;
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

void make_matrix(int **b, int n, int m, int count, int **a, int **ai, struct j **head)
{
	struct j *buf;
	int flag = 0;
	*ai = malloc(count * sizeof(int));
	*a = malloc(count * sizeof(int));
	*head = NULL;
	int h = 0 ;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (b[j][i] != 0)
			{
				(*a)[h] = b[j][i];
				(*ai)[h] = j;
				if (!flag)
				{
				    buf = create_j(h);
					*head = add_j(*head, buf);
					flag = 1;
				}
				h++;
			}
		}
		if(!flag)
		{
			buf = create_j(h);
			*head = add_j(*head, buf);
		}
		flag = 0;
	}
	buf = create_j(h);
	*head = add_j(*head, buf);
}

void make_line(int *b, int n, int count, int **a, int **ai)
{
	*ai = malloc(count * sizeof(int));
	*a = malloc(count * sizeof(int));
	int h = 0 ;
	for (int i = 0; i < n; i++)
	{
		if (b[i] != 0)
		{
			(*a)[h] = b[i];
			(*ai)[h] = i;
			h++;
		}
	}
}

int read_matrix(int ***a, int *n, int *m, int *count)
{
	int u, i, j, k;
	int rc = OK;
	int **buf;
	printf("Input n(>0): ");
	if (scanf("%d", n) == 1 && *n > 0)
	{
		printf("Input m(>0): ");
		if(scanf("%d", m) == 1 && *m > 0)
		{
			printf("Input number of not-zero elements(<= %d): ", *n * *m);
			if(scanf("%d", count) == 1 && *count >= 0 && *count <= *n * *m)
			{
				buf = allocate_normal_matrix(*n, *m);
				if (buf)
				{
				    u = 0;
					printf("Input elements\n i (0..%d) j (0..%d) element - int\n(i j element): \n", *n - 1, *m-1);
					while (u < *count && rc == OK)
					{
						if (scanf( "%d %d %d", &i, &j, &k) == 3)
						{
							if (i < *n && j < *m && i >= 0 && j >= 0)
							{
							    buf[i][j] = k;
								u++;
							}
							else
							{
								printf("Uncorrect i, j or element\n");
								rc = ERR_READ;
							}
						}
						else 
						{
							printf("Uncorrect i, j or element\n");
							rc = ERR_READ;
						}
					}
					if (rc != OK)
					    free_matrix(buf, *n);
				    else 
					    *a = buf;
				}
				else 
					rc = ERR_MEMORY;
			}
			else 
			{
				printf("Uncorrent count\n");
				rc = ERR_IO;
			}
		}
		else
		{
			printf("Uncorrect m\n");
			rc = ERR_IO;
		}
	}
	else
	{
		printf("Uncorrect n\n");
		rc = ERR_IO;
	}
	return rc;
}

int read_line(int **a, int *n, int *count)
{
	int u, i, k;
	int rc = OK;
	int *buf;
	printf("Input n(>0): ");
	if (scanf("%d", n) == 1 && *n > 0)
	{
		printf("Input number of not-zero elements(<= %d): ", *n);
		if(scanf("%d", count) == 1 && *count >= 0 && *count <= *n)
		{
			buf = calloc(*n, sizeof(int));
			if (buf)
			{
			    u = 0;
				printf("Input elements\n i (0..%d)\n element - int\n(i element): \n", *n-1);
				while (u < *count && rc == OK)
				{
					if (scanf( "%d %d", &i, &k) == 2)
					{
						if (i < *n && i >= 0)
						{
						    buf[i] = k;
							u++;
						}
						else
						{
							printf("Uncorrect i or element\n");
							rc = ERR_READ;
						}
					}
					else 
					{
						printf("Uncorrect i or element\n");
						rc = ERR_READ;
					}
				}
				if (rc != OK)
				    free(buf);
			    else 
				    *a = buf;
			}
			else 
				rc = ERR_MEMORY;
		}
		else 
		{
			printf("Uncorrent count\n");
			rc = ERR_IO;
		}
	}
	else
	{
		printf("Uncorrect n\n");
		rc = ERR_IO;
	}
	return rc;
}

int read_line_from_file(char *filename, int **a, int *n, int *count)
{
	int u, i, k;
	int rc = OK;
	int *buf;
	
	FILE *f = fopen(filename, "r");
	if (f)
	{
		if (fscanf(f, "%d", n) == 1 && *n > 0)
		{
			if(fscanf(f, "%d", count) == 1 && *count >= 0 && *count <= *n)
			{
				buf = calloc(*n, sizeof(int));
				if (buf)
				{
				    u = 0;
					while (u < *count && rc == OK)
					{
						if (fscanf(f, "%d %d", &i, &k) == 2)
						{
							if (i <= *n && i > 0)
							{
							    buf[i-1] = k;
								u++;
							}
							else
							{
								printf("Uncorrect i, j or element\n");
								rc = ERR_READ;
							}
						}
						else 
						{
							printf("Uncorrect i, j or element\n");
							rc = ERR_READ;
						}
					}
					if (rc != OK)
				        free(buf);
			        else 
				        *a = buf;
				}
				else 
					rc = ERR_MEMORY;
			}
			else 
			{
				printf("Uncorrent count\n");
				rc = ERR_IO;
			}
		}
		else
		{
			printf("Uncorrect n\n");
			rc = ERR_IO;
		}
	}
	else
		rc = ERR_FILE;
	return rc;
}

int read_matrix_from_file(const char *fname, int ***a, int *n, int *m, int *count)
{
	FILE *f;
	//int count;
	int **buf;
	int i, j; 
	int k;
	int rc = OK, u;
	
	f = fopen(fname, "r");
	
	if (!f)
		return ERR_FILE;
	
	if (fscanf(f, "%d %d %d", n, m, count) == 3)
	{
		if (*n > 0 && *m > 0 && *count >= 0 && *count <= *n * *m)
		{
			buf = allocate_normal_matrix(*n, *m);
			if (buf)
			{
				//zero_matrix(buf, *n, *m);
				u = 0;
				while (u < *count && rc == OK)
				{
					if (fscanf(f, "%d %d %d", &i, &j, &k) == 3)
					{
						if (i <= *n && j <= *m && i > 0 && j > 0)
						{
							if (buf[i - 1][j - 1] == 0)
							{
						        buf[i - 1][j - 1] = k;
								u++;
							}
						}
						else
						{
							printf("Uncorrect i, j\n");
							rc = ERR_READ;
						}
					}
					else 
					{
						printf("Uncorrect i, j or element\n");
						rc = ERR_READ;
					}
				}
				if (rc != OK)
				    free_matrix(buf, *n);
			    else 
				    *a = buf;
			}
			else 
				rc = ERR_MEMORY;
		}
		else 
		{
			printf("Uncorrent n, m or count\n");
			rc = ERR_IO;
		}
	}
	else 
	{
		printf("Uncorrent n, m or count\n");
		rc = ERR_IO;
	}
		
		
	fclose(f);
	return rc;
}

void print_matrix(int *a, int *ai, struct j *head, int count, int n, int m)
{
	 int h = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ( h < head->next->i && j == ai[h])
			{
				printf("%d ", a[h]);
				h++;
			}
			else 
				printf("0 ");
		}
		head = head->next;
		printf("\n");
	}
}

int rand_line(int **a, int *n, int *count)
{
	int p;
	int u, i, k;
	int rc = OK;
	int *buf;
	printf("Input n(>0): ");
	if (scanf("%d", n) == 1 && *n > 0 )
	{
		printf("Input procent(0 .. 100): ");
		if(scanf("%d", &p) == 1 && p >= 0 && p <= 100)
		{
			buf = calloc(*n, sizeof(int));
			if (buf)
			{
				*count = *n * p / 100;
			    u = 0;
				//printf("Input elements(i element): \n");
				while (u < *count)
				{
					i = rand()% *n;
					k = rand()% 1000;
					if (buf[i] == 0)
					{
					    buf[i] = k;
					    u++;
					}
				}
				
				*a = buf;
			}
			else 
				rc = ERR_MEMORY;
		}
		else
		{
			printf("uncorrect procent\n");
			rc = ERR_IO;
		}
	}
	else
	{
		printf("Uncorrect n\n");
		rc = ERR_IO;
	}
	return rc;
	
}

int rand_matrix(int ***a, int *n, int *m, int *count)
{
	int p;
	int u, i, j, k;
	int rc = OK;
	int **buf;
	printf("Input n(>0): ");
	if (scanf("%d", n) == 1 && *n > 0)
	{
		printf("Input m(>0): ");
		if(scanf("%d", m) == 1 && *m > 0)
		{
			printf("Input procent(0-100):");
			if(scanf("%d", &p) == 1 && p >= 0 && p <= 100)
			{
				buf = allocate_normal_matrix(*n, *m);
				if (buf)
				{
					*count = *n * *m * p / 100;
				    u = 0;
					//printf("Input elements(i j element): \n");
					while (u < *count && rc == OK)
					{
						i = rand()% *n;
						j = rand()% *m;
					    k = rand()% 1000;
						if (buf[i][j] == 0)
						{
							///rintf();
					        buf[i][j] = k;
					        u++;
						}
					}
					*a = buf;
				}
				else 
					rc = ERR_MEMORY;
			}
			else 
				rc = ERR_IO;
		}
		else
			rc = ERR_IO;
	}
	else
		rc = ERR_IO;
	return rc;
}

void menu()
{
	printf("\nActions:\n");
	//printf("new - to create new file\n");
	printf("1. input data\n");
	printf("2. read from file\n");
	printf("3. random \n");
	printf("4. exit\n");
	//printf("4. find - to find elemets by flag\n");
	//printf("5. sort - to sort table\n");
	///printf("6. end - to end program\n\n");
}

void info()
{
	printf("This program makes multiply line * matrix.\n");
    printf("\n");
}

int rand_line1(int **a, int *n, int *count, int p)
{
	//int p;
	int u, i, k;
	int rc = OK;
	int *buf;
	*n = 100;
	if ( *n > 0 )
	{
	    //printf("Input procent(0 .. 100): ");
		if(p >= 0 && p <= 100)
		{
			buf = calloc(*n, sizeof(int));
			if (buf)
			{
				*count = *n * p / 100;
			    u = 0;
				//printf("Input elements(i element): \n");
				while (u < *count)
				{
					i = rand()% *n;
					k = rand()% 1000;
					if (buf[i] == 0)
					{
					    buf[i] = k;
					    u++;
					}
				}
				
				*a = buf;
			}
			else 
				rc = ERR_MEMORY;
		}
		else
		{
			printf("uncorrect procent\n");
			rc = ERR_IO;
		}
	}
	else
	{
		printf("Uncorrect n\n");
		rc = ERR_IO;
	}
	return rc;
	
}


int rand_matrix1(int ***a, int *n, int *m, int *count, int p)
{
	//int p;
	int u, i, j, k;
	int rc = OK;
	int **buf;
	*n = 100;
	*m = 100;
	//printf("Input n(>0): ");
	if ( *n > 0)
	{
		//printf("Input m(>0): ");
		if( *m > 0)
		{
			//printf("Input procent(0-100):");
			if(p >= 0 && p <= 100)
			{
				buf = allocate_normal_matrix(*n, *m);
				if (buf)
				{
					*count = *n * *m * p / 100;
				    u = 0;
					//printf("Input elements(i j element): \n");
					while (u < *count && rc == OK)
					{
						i = rand()% *n;
						j = rand()% *m;
					    k = rand()% 1000;
						if (buf[i][j] == 0)
						{
							///rintf();
					        buf[i][j] = k;
					        u++;
						}
					}
					*a = buf;
				}
				else 
					rc = ERR_MEMORY;
			}
			else 
				rc = ERR_IO;
		}
		else
			rc = ERR_IO;
	}
	else
		rc = ERR_IO;
	return rc;
}
void make_table()
{
	int **matrix;
	int n, m, count, n1, count1;
	int *a, *ai, *b, *bi;
	struct j *head;
	int action;
	char filename[30 + 1];
	char buf[30+1];
	int rc;
	int *line;
	int *c;
	long int tb, te;
	long int t1, t2;
	FILE *f = fopen("output.txt", "w");
	fprintf(f," p  t1     t2     tt     m1     m2    mm\n");
	for (int i = 0; i <= 100; i++)
	{
		rand_line1(&line, &n1, &count1,i);
		rand_matrix1(&matrix, &n, &m, &count,i);
		make_line(line, n1, count1, &b, &bi);
		make_matrix(matrix, n, m, count, &a, &ai, &head);
		tb = tick();
	    rc = multiply(b,bi,n1,count1,a,ai,head,n,m,count,&c);
	    te = tick();
	    t1 = te-tb;
		
		int *l1[1];
	    int **c2;
	    l1[0] = line;
		
	    tb = tick();
	    multiply_simple(l1,1, n1, matrix, n, m, &c2);
	    te = tick();
	    t2 = te-tb;
	
	    int m2 = sizeof(int)*n*m + sizeof(int)*n1 + 3*sizeof(int) + m*sizeof(int);
	    int m1 = sizeof(int)*count*2 + sizeof(struct j)*m + sizeof(int) * 5 +  sizeof(int)*count1*2 + n*sizeof(int) +m*sizeof(int);
	    int mm = (m2 - m1)*100/m2;
	    long int tt = 100 * (t2-t1)/t2 ;
		fprintf(f, "%3d %6d %6d %6d %6d %6d %6d\n",i, t1,t2,tt,m1,m2,mm);
		//free_list(head);
	    //free(a);
	    //free(ai);
	    //free(b);
	    //free(bi);
	    //free(c);
	    //free(c2);
	    //free_matrix(matrix, n);
	}		
	fclose(f);
}

int main()
{
	setbuf(stdout, NULL);
	int **matrix;
	int n, m, count, n1, count1;
	int *a, *ai, *b, *bi;
	struct j *head;
	int action;
	char filename[30 + 1];
	char buf[30+1];
	int rc;
	int *line;
	int *c;
	long int tb, te;
	long int t1, t2;
	
	srand(time(NULL));

	
	info();
	
	printf("Input line: \n  ");
	
	menu();
	printf("Choose method of input data(1,2,3,4): ");
	if (scanf("%d", &action) == 1)
	{
		if (action == 1)
		{
			rc = read_line(&line, &n1, &count1);
			if (rc == ERR_READ || rc == ERR_IO)
			{
				printf("Input error!\n");
				return ERR_READ;
			}
			else if (rc == ERR_MEMORY)
			{
				printf("Memory error!\n");
				return ERR_MEMORY;
			}
			//printf("%d %d\n", n1, count1);
	       
		}
		else if (action == 2)
		{
			printf("Input name of file(30 signs): ");
			if (scanf("%s", filename) == 1) 
			{
				rc = read_line_from_file(filename, &line, &n1, &count1);
				if (rc == ERR_FILE)
				{
					printf("File can't be open!\n");
					return rc;
				}
				else if (rc == ERR_READ)
				{
					printf("Input error()!\n");
					return rc;
				}
				else if (rc == ERR_MEMORY)
				{
					printf("Memory error!\n");
					return rc;
				}
				
				//printf("%d %d\n", n1 , count1);
			}
			else 
			{
				printf("Input error !\n");
				return 1;
			}
	    }
		else if (action == 3)
		{
			rc = rand_line(&line, &n1, &count1);
			if (rc == ERR_READ || rc == ERR_IO)
			{
				printf("Input error!\n");
				return ERR_READ;
			}
			else if (rc == ERR_MEMORY)
			{
				printf("Memory error!\n");
				return ERR_MEMORY;
			}
		}
		else if (action == 4)
		{
			return OK;
		}
		else 
    	{
		    gets(buf);
	        printf("\nInput error\n\n");
		    return ERR_IO;
	    }
	}
	else 
	{
		gets(buf);
	    printf("\nInput error\n\n");
		return ERR_IO;
	}
	
	printf("\nInput matrix: \n  ");
	
	menu();
	printf("Choose method of input data(1,2,3,4): ");
	if (scanf("%d", &action) == 1)
	{
		if (action == 1)
		{
			rc = read_matrix(&matrix, &n, &m, &count);
			if (rc == ERR_READ || rc == ERR_IO)
			{
				printf("Input error!\n");
				return ERR_READ;
			}
			else if (rc == ERR_MEMORY)
			{
				printf("Memory error!\n");
				return ERR_MEMORY;
			}
		}
		else if (action == 2)
		{
			printf("Input name of file(30 signs): ");
			if (scanf("%s", filename) == 1) 
			{
				rc = read_matrix_from_file(filename, &matrix, &n, &m, &count);
				if (rc == ERR_FILE)
				{
					printf("File can't be open!\n");
					return rc;
				}
				else if (rc == ERR_READ)
				{
					printf("Input error!\n");
					return rc;
				}
				else if (rc == ERR_MEMORY)
				{
					printf("Memory error!\n");
					return rc;
				}
				
			}
			else 
			{
				printf("Input error !\n");
				return 1;
			}
	    }
		else if (action == 3)
		{
			rc = rand_matrix(&matrix, &n, &m, &count);
			if (rc == ERR_READ || rc == ERR_IO)
			{
				printf("Input error!\n");
				return ERR_READ;
			}
			else if (rc == ERR_MEMORY)
			{
				printf("Memory error!\n");
				return ERR_MEMORY;
			}
			
		}
		else if (action == 4)
		{
			return OK;
		}
		else 
    	{
		    gets(buf);
	        printf("\nInput error\n\n");
		    return ERR_IO;
	    }
	}
	else 
	{
		gets(buf);
	    printf("\nInput error\n\n");
		return ERR_IO;
	}
	
	make_line(line, n1, count1, &b, &bi);
	
    
	if (n1 <= 10)
	{
	    printf("\n Line :\n");
	    for (int i = 0; i < n1; i++)
	    	printf("%4d ", line[i]);
	    printf("\n");
		printf("B = ");
	    for (int i = 0; i < count1; i++)
	    	printf("%d ", b[i] );
    	printf("\n");
    	printf("Bi = ");
	    for (int i = 0; i < count1; i++)
	    	printf("%d ", bi[i] );
	    printf("\n");
	}

	
	make_matrix(matrix, n, m, count, &a, &ai, &head);
	
	if (n <= 10 && m <= 10)
	{
		printf("\n Matrix :\n");
	    printf("n = %d\nm = %d\ncount = %d\n", n , m , count);
	    for (int i = 0; i < n; i++)
	    {
	    	for(int j = 0; j < m; j++)
	    	{
	    		printf("%5d ", matrix[i][j]);
	    	}
	     	printf("\n");
	    }
	    printf("\n");
		 printf("A = ");
	    for (int i = 0; i < count; i++)
	    	printf("%d ", a[i] );
	    printf("\n");
	    printf("Ai = ");
	    for (int i = 0; i < count; i++)
	    	printf("%d ", ai[i] );
	    printf("\n");
	    printf("Aj = ");
	    struct j *k = head;
	    for (int i = 0; i < m+1; i++)
	    {
	    	printf(" %d ",k->i );
	    	k = k->next;
	    }
	    printf("\n");
	}
	
	
	int p1 = count*100/n/m;
	printf("percent matrix : %d \n", p1);
	
	int p2 = count1*100/n1;
	printf("percent  line : %d \n", p2);
	
	//multiply(line,n1,a,ai,head,n,m,count,&c);
	tb = tick();
	rc = multiply(b,bi,n1,count1,a,ai,head,n,m,count,&c);
	te = tick();
	t1 = te-tb;
	
	if (rc != OK)
	{
		printf("Can't make multiply!\n");
		return rc;
	}
	printf("\n Answer :\n");
	if (m < 10)
	{
	    for (int i = 0; i < m; i++)
		    printf("%d ", c[i]);
	    printf("\n");
	    printf(" time :%ld \n", t1);
	}
	else 
	{
		 for (int i = 0; i < m; i++)
		 {
			if (c[i] != 0)
		        printf("%d %d \n", i, c[i]);
		 }
	    printf("\n");
	    printf(" time :%ld \n", t1);
	}
	
	int *l1[1];
	int **c2;
	l1[0] = line;
	
	tb = tick();
	multiply_simple(l1,1, n1, matrix, n, m, &c2);
	te = tick();
	t2 = te-tb;
	
	long int tt = 100 * (t2-t1)/t2 ;
	
		printf("\n Answer2 :\n");
	if (m < 10)
	{
	    for (int i = 0; i < m; i++)
		    printf("%d ", c2[0][i]);
	    printf("\n");
	    printf(" time :%ld \n", t2);
	}
	else 
	{
		for (int i = 0; i < m; i++)
		{
	    	if (c2[0][i] != 0)
		        printf("%d %d \n", i, c2[0][i]);
		}
	    printf("\n");
	    printf(" time :%ld \n", t2);
	}
	
	printf("Time difference: %d ", tt);
	
	int m2 = sizeof(int)*n*m + sizeof(int)*n1 + 3*sizeof(int) + m*sizeof(int);
	int m1 = sizeof(int)*count*2 + sizeof(struct j)*m + sizeof(int) * 5 +  sizeof(int)*count1*2 + n*sizeof(int) +m*sizeof(int);
	int mm = (m2 - m1)*100/m2;
	
	printf("\nmem1(razrez): %d\nmem2(simple): %d \nmem difference:%d \n", m1, m2, mm);
	free_list(head);
	free(a);
	free(ai);
	free(b);
	free(bi);
	free(c);
	free(c2);
	free_matrix(matrix, n);
	
	make_table();
	
	return 0;
	
}