#include"process.h"
#include"io.h"
#include<string.h>

int read_all(char * filename, struct country *all, int *n)
{
	int rc = 0;
    *n = 0;
	FILE *f = fopen(filename,"r");
	while (rc == 0 && *n < M)
	{
		rc = read_txt(f, &all[*n]);
		*n += 1;
	}
	*n -= 1;
	fclose(f);
	return 0;
}

void find(char *filename, char *mainland, char *turism)
{
	struct country a;
	int rc = 0;
	int n = 0;
	int count = 0;
	FILE *f = fopen(filename,"r");
	
	printf("\n");
	p();

	while (rc == 0 && n < M)
	{
		rc = read_txt(f, &a);
		//print_a(a);
		if (rc == 0 && strcmp(a.mainland, mainland) == 0 && strcmp(a.turism, turism) == 0)
		{
			print_a(a);
			count++;
		}
		n++;
	}
	
	if (count == 0)
	{
		printf("No elemets\n");
	}		
	
	fclose(f);
}

int delete(char *filename)
{
    struct country all[M];
	int n;
	read_all(filename, all, &n);
	int g;
	int y;
	struct country new[M];
	
	printf("n   ");
	p();
	for (int i = 0; i < n; i++)
	{
		printf("%3d ", i);
		print_a(all[i]);
	}
	
	printf("Input index: ");
	if (scanf("%d", &g) == 1)
	{
		if (g < n && g >= 0)
		{
			y = 0;
			for (int j = 0; j < n; j++)
			{
				if ( y != g)
				{
				    new[y] = all[j];
				    y++;
				}
			}
			FILE *f = fopen(filename, "w");
	        fclose(f);
        
			for (int h = 0; h < n; h++)
			{
				save_txt(filename, new[h]);
			}
		}
		else 
			printf("Input error\n");
	}
	else
	    printf("Input error\n");
	return 0;
	
	/*printf("Input search key(name, people, capital, mainland, turism):");
	if (scanf("%s", buf1) == 1)
	{
		if (strcmp(buf1, "name") == 0)
		{
			printf("Input name of country: ");
			if (scanf("%s", buf) == 1)
			{
				printf("\n");
		    	for (int i = 0; i < n; i++)
				{
			    	if (strcmp(all[i].name, buf) == 0)
					{
						printf("%d ", count);
						mass[count] = i;
						print_a(all[i]);
						count++;
					}
				}
				printf("\n");
				if (count == 0)
				{
					printf("No elements\n");
					return 0;
				}
				printf("Choose index:");
				int k = 1;
				while (k)
				{
				    if (scanf("%d", &g) == 1 && g < count)
					{
					   y = mass[g];
					   k = 0;
					}
					else 
						printf("Input error!\n");
				}
			}
			else
				return ERR_IO;
		}
		else if (strcmp(buf1, "capital") == 0)
		{
			printf("Input %s of country: ", buf1);
			if (scanf("%s", buf) == 1)
			{
				printf("\n");
		    	for (int i = 0; i < n; i++)
				{
			    	if (strcmp(all[i].capital, buf) == 0)
					{
						printf("%d ", count);
						mass[count] = i;
						print_a(all[i]);
						count++;
					}
				}
				printf("\n");
				if (count == 0)
				{
					printf("No elements\n");
					return 0;
				}
				printf("Choose index:");
				int k = 1;
				while (k)
				{
				    if (scanf("%d", &g) == 1 && g < count)
					{
					   y = mass[g];
					   k = 0;
					}
					else 
						printf("Input error!\n");
				}
			}
			else
				return ERR_IO;
		}
		else if (strcmp(buf1, "turism") == 0)
		{
			printf("Input %s of country: ", buf1);
			if (scanf("%s", buf) == 1)
			{
				printf("\n");
		    	for (int i = 0; i < n; i++)
				{
			    	if (strcmp(all[i].turism, buf) == 0)
					{
						printf("%d ", count);
						mass[count] = i;
						print_a(all[i]);
						count++;
					}
				}
				printf("\n");
				if (count == 0)
				{
					printf("No elements\n");
					return 0;
				}
				printf("Choose index:");
				int k = 1;
				while (k)
				{
				    if (scanf("%d", &g) == 1 && g < count)
					{
					   y = mass[g];
					   k = 0;
					}
					else 
						printf("Input error!\n");
				}
			}
		}
		else if (strcmp(buf1, "mainland") == 0)
		{
			printf("Input %s of country: ", buf1);
			if (scanf("%s", buf) == 1)
			{
				printf("\n");
		    	for (int i = 0; i < n; i++)
				{
			    	if (strcmp(all[i].mainland, buf) == 0)
					{
						printf("%d ", count);
						mass[count] = i;
						print_a(all[i]);
						count++;
					}
				}
				printf("\n");
				if (count == 0)
				{
					printf("No elements\n");
					return 0;
				}
				printf("Choose index:");
				int k = 1;
				while (k)
				{
				    if (scanf("%d", &g) == 1 && g < count)
					{
					   y = mass[g];
					   k = 0;
					}
					else 
						printf("Input error!\n");
				}
			}
			else 
				return ERR_IO;
		}
		else if (strcmp(buf1, "people") == 0)
		{
			printf("Input %s of country: ", buf1);
			if (scanf("%d", &l) == 1)
			{
				printf("\n");
		    	for (int i = 0; i < n; i++)
				{
			    	if (all[i].people == l)
					{
						printf("%d ", count);
						mass[count] = i;
						print_a(all[i]);
						count++;
					}
				}
				printf("\n");
				if (count == 0)
				{
					printf("No elements\n");
					return 0;
				}
				printf("Choose index: ");
				int k = 1;
				while (k)
				{
				    if (scanf("%d", &g) == 1 && g < count)
					{
					   y = mass[g];
					   k = 0;
					}
					else 
						printf("Input error!\n");
				}
			}
			else
				return ERR_IO;
		}
		else 
			return ERR_IO;
	}
	else
		return ERR_IO;
	
    struct country new[M];
	
	count = 0;
	for (int i = 0; i < n; i++)
	{
		if (i != y)
		{
			new[count] = all[i];
			count++;
		}
	}
	FILE *f = fopen(filename, "w");
	fclose(f);
    for (int i = 0; i < count; i++)
	{
		save_txt(filename, new[i]);
	}
	
	return 0;*/
}

void sort1(struct country *all, int n, int *m)
{
	*m = 0;
	struct country a;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n-1; j++)
			if (all[j].people > all[j+1].people)
			{
				a = all[j];
				all[j] = all[j+1];
				all[j+1] = a;
				*m += sizeof(a);
			}
			
	//printf("memory %d\n", m);
}

void sort2(struct country *all, int n, struct keys *k, int *m)
{
	struct keys buf;
	*m = 0;
	
	for (int i = 0; i < n; i++)
	{
		k[i].n = i;
		k[i].people = all[i].people;
	}
	
	*m += sizeof(k);
	
	for (int i = 0; i < n; i++)
		for (int j = i; j < n-1; j++)
		{
		    if (k[j].people > k[j+1].people)
			{
				buf = k[j];
				k[j] = k[j+1];
                k[j+1] = buf;
                *m += sizeof(buf);				
			}
		}
	//printf("memory %d\n", m);
}

void sort3(struct country *all, int n, struct keys *k, int *m)
{
	struct keys buf;
	*m = 0;
	int left;
	int right;
	int z;
	
	for (int i = 0; i < n; i++)
	{
		k[i].n = i;
		k[i].people = all[i].people;
	}
	*m += sizeof(k);
	for (int i = 1; i < n; i++)
	{
		if (k[i-1].people > k[i].people)
		{
			buf = k[i];
			left = 0;
			right = i-1;
			while (left <= right)
			{
				z = (left+right)/2;
				if (k[z].people < buf.people)
					left = z+1;
				else
					right = z-1;
			}
			for (int j = i-1; j >= left; j--)
			{
				k[j+1] = k[j];
			}
			k[left] = buf;
		}
			
		
	}
		
}