#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF 1234567

void free_matrix(int **data, int n)
{
	//assert(data != NULL);
	//(n != 0);
	for (int i = 0; i < n; i++)
		free(data[i]);
	free(data);
}

void zero_matrix(int **a, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i == j)
			{
			    a[i][j] = 0;
			}
			else 
			{
				a[i][j] = INF;
			}
		}
    }		
}

int **allocate_matrix(int n, int m)
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



int read(FILE *f, int *i, int *j, int *p, int max)
{
	if (!f)
		return 1;
	if (fscanf(f, "%d %d %d", i, j, p) == 3 && *i > 0 && *j > 0 && *p > 0 
	&& *i <= max && *j <= max)
	{
		return 0;
	}
	return 1;
}

int read_from_file(FILE *f, int ***matrix, int *n)
{
	int i, j, p;
	if (!f)
		return 1; 
    if (fscanf(f, "%d", n) != 1 || *n <= 0)
    {
		return 1;
	}
	//printf("%d ", *n);
	int **mt = allocate_matrix(*n, *n);
	if (mt)
	{
		zero_matrix(mt, *n,*n);
		while (!read(f,&i,&j,&p, *n))
		{
			mt[i - 1][j - 1] = p;
			mt[j - 1][i - 1] = p;
			//printf(" %d %d %d  ", i, j, p );
		}
		*matrix = mt;
		return 0;
	}
	return 1;
}

void print_graph(int **matrix, int n)
{
	FILE *f = fopen("graph.gv", "w");
	fprintf(f, "digraph n1 {");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++ )
		{
			if (matrix[i][j] != 0 && matrix[i][j] != INF)
			{
				fprintf(f, "%d->%d [label=%d];\n", i+1, j+1, matrix[i][j]);
			}
		}
	}
	fprintf(f,"}");
	fclose(f);
}

int minimum(int i, int j)
{
	if (i < j)
		return i;
	return j;
}

void floid(int **w, int n)
{	
    //printf("floid");
    for (int k = 0; k < n; k++)
	{
		//printf("1");
		for (int i = 0; i < n; i++)
		{
			//printf("2");
			for (int j = 0; j < n; j++)
			{
				//printf("3");
				if (w[i][j] == 0)
					continue;
				if (w[i][j] != INF && w[i][k] != INF && w[k][j] != INF)
				{
					w[i][j] = minimum(w[i][j], w[i][k] + w[k][j]);
				}
				else if (w[i][k] != INF && w[k][j] != INF)
				{
					w[i][j] = w[i][k] + w[k][j];
				}
			}
		}
	}
}

#define APP "mspaint.exe"
#define DOT "C:\\Graphviz2.38\\bin\\dot.exe"
#define ME "C:\\c_prog\\TiSD\\7\\1"

int main()
{
	setbuf(stdout, NULL);
	int **matrix;
	int n, rc;
	FILE *f;
	char fname[31];
	
	printf("Input filename:");
	if (scanf("%s", fname) != 1)
	{
		printf("Input error\n");
		return 1;
	}
	f = fopen(fname, "r");
	if (!f)
	{
		printf("Cant't open file\n");
		return 1;
	}
	rc = read_from_file(f, &matrix, &n);
	//printf("%d", rc);
	print_graph(matrix, n);
	system(DOT " -Tpng " ME "\\graph.gv -o" ME "\\graph.png");
    system("start " APP " " ME "\\graph.png");
	fclose(f);
	
	floid(matrix, n);
	printf("     ");
	for (int i = 0; i < n; i++)
	{
		printf("%4d ", i+1);
	}
	printf("\n");
	
	for (int i = 0; i < n; i++)
	{
		printf("%2d - ", i+1);
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == INF)
				printf("none ");
			else 
				printf("%4d ", matrix[i][j]);
		}
		printf("\n");
	}
	int min = 0; 
	int ind = 1;
	for (int i = 0; i < n; i++)
	{
		min += matrix[0][i];
	}
    int sum;	
	for (int i = 0; i < n; i++)
	{
		sum = 0;
		for (int j = 0; j < n; j++)
		{
			sum += matrix[i][j];
		}
		printf("sum %d = %d\n", i+1, sum);
		if (sum < min)
		{
			ind = i+1;
			min = sum;
		}
	}
	
	printf("Minimum is %d string. Sum is %d", ind, min);
	
	/*int r = search_Dijkstra(matrix, n, 1, 2);
	int **new  = allocate_matrix(n, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			new[i][j] = search_Dijkstra(matrix, n, i+1, j+1);
		}
	}
	printf("    ");
	for (int i = 0; i < n; i++)
	{
		printf("%4d ", i);
	}
	printf("\n");
	
	for (int i = 0; i < n; i++)
	{
		printf("%d - ", i);
		for (int j = 0; j < n; j++)
		{
			if (new[i][j] == 1000)
				printf("none ");
			else 
				printf("%4d ", new[i][j]);
		}
		printf("\n");
	}*/
	//printf("Длина из 1 в 2 %d\n", r);
	//printf("%d", rc);
	//rc = find(matrix, n);
	
	//dekstra(matrix, n, 0);
	//printf("%d", rc);
	return rc;
}
