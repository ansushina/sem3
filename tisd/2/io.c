#include"io.h"
#include<string.h>

void p()
{
	printf("Name         People       Capital            Mainland     Tourism      Variable part\n");
}

int read_new(struct country *a)
{
	char buf[N+1];
	int k = 1;
	int b;
	while (k)
	{
		printf("Input name of country(30 signs):");
	    if (scanf("%s", buf) == 1)
	    {
	        int i = 0;
	        while (i < N && buf[i] != '\0')
	        {
	        	a->name[i] = buf[i];
	        	i++;
	        }
	        a->name[i] = '\0';
			k = 0;
		}
		else
			printf("Input Error!\n");
	} 
	k = 1;
	while (k)
	{
		printf("Input people of country(int):");
		if (scanf("%d", &(a->people)) == 1)
			k = 0;
		else 
		{
			gets(buf);
			printf("Input error!\n");
		}
	}
	k = 1;
	while (k)
	{
		printf("Input capital of country(30 signs):");
	    if (scanf("%s", buf) == 1)
	    {
	        int i = 0;
	        while (i < N && buf[i] != '\0')
	        {
	        	a->capital[i] = buf[i];
	        	i++;
	        }
	        a->capital[i] = '\0';
			k = 0;
		}
		else
			printf("Input Error!\n");
	}
	k = 1;
	while (k)
	{
		printf(" 1. Europe \n 2. Asia\n 3. NortAmerica\n 4. SouthAmerica\n 5. Australia \n 6. Africa \n");
		printf("Input mainland of country(number):");
	    if (scanf("%d", &b) == 1)
	    {
			if (b == 1)
	            strcpy(a->mainland, "Europe");
			else if (b == 2)
	            strcpy(a->mainland, "Asia");
			else if (b == 3)
	            strcpy(a->mainland, "NorthAmerica");
			else if (b == 4)
	            strcpy(a->mainland, "SouthAmerica");
			else if (b == 5)
	            strcpy(a->mainland, "Australia");
			else if (b == 6)
	            strcpy(a->mainland, "Africa");
			k = 0;
		}
		else
		{
			gets(buf);
			printf("Input Error!\n");
		}
	}
	k = 1;
	while (k)
	{
		printf("Input turism of country(number)(1.sport, 2.excursion, 3.beach):");
	    if (scanf("%d", &b) == 1)
	    {
			if (b == 2)
			{
				strcpy(a->turism, "excursion");
				int k = 1;
				while (k)
				{
					printf("Input number of excursion(int): ");
					if (scanf("%d", &(a->tur.ex.n)) == 1)
						k = 0;
					else 
					{
						gets(buf);
						printf("Input error\n");
					}
				}
				k = 1;
				while (k)
				{
					printf("Input type of excursion(30 signs): ");
					if (scanf("%s", buf) == 1)
					{
						int i = 0;
	                    while (i < N && buf[i] != '\0')
	                    {
	                    	a->tur.ex.type[i] = buf[i];
	                    	i++;
	                    }
	                    a->tur.ex.type[i] = '\0';
						k = 0;
					}
					else 
						printf("Input error\n");
				}
				break;
			}
			else if (b == 1)
			{
				strcpy(a->turism, "sport");
				int k = 1;
				while (k)
				{
					printf("Input type of sport(30 signs): ");
					if (scanf("%s", buf) == 1)
					{
						int i = 0;
	                    while (i < N && buf[i] != '\0')
	                    {
	                    	a->tur.sport.type[i] = buf[i];
	                    	i++;
	                    }
	                    a->tur.sport.type[i] = '\0';
						k = 0;
					}
					else 
						printf("Input error\n");
				}
				k = 1;
				while (k)
				{
					printf("Input cost of sport(int): ");
					if (scanf("%d", &(a->tur.sport.cost)) == 1)
						k = 0;
					else 
					{
						gets(buf);
						printf("Input error\n");
					}
				}
				break;
			}
			else if (b == 3)
			{
				strcpy(a->turism, "beach");
				int k = 1;
				while (k)
				{
					printf("Input season(30 signs): ");
					if (scanf("%s", buf) == 1)
					{
						int i = 0;
	                    while (i < N && buf[i] != '\0')
	                    {
	                    	a->tur.beach.season[i] = buf[i];
	                    	i++;
	                    }
	                    a->tur.beach.season[i] = '\0';
						k = 0;
					}
					else 
						printf("Input error\n");
				}
				k = 1;
				while (k)
				{
					printf("Input water temperature(int): ");
					if (scanf("%d", &(a->tur.beach.tw)) == 1)
						k = 0;
					else 
					{
						gets(buf);
						printf("Input error\n");
					}
				}
				k = 1;
				while (k)
				{
					printf("Input air temperature(int): ");
					if (scanf("%d", &(a->tur.beach.ta)) == 1)
						k = 0;
					else 
					{
						gets(buf);
						printf("Input error\n");
					}
				}
				k = 1;
				while (k)
				{
					printf("Input time(int in hours): ");
					if (scanf("%d", &(a->tur.beach.time)) == 1)
						k = 0;
					else 
					{
						gets(buf);
						printf("Input error\n");
					}
				}
				break;
			}
		}
		else
		{
			gets(buf);
			printf("Input Error!\n");
		}
	}
	return 0;
}


void print_a(struct country a)
{
	printf("%-12s %-12d %-18s %-12s %-9s ", a.name, a.people, a.capital,
	a.mainland, a.turism);
	if (strcmp(a.turism, "excursion") == 0)
	{
		printf("%-9d %-10s\n", a.tur.ex.n, a.tur.ex.type);
	}
	if (strcmp(a.turism, "sport") == 0)
	{
		printf("%-10s %-9d\n", a.tur.sport.type, a.tur.sport.cost);
	}
	if (strcmp(a.turism, "beach") == 0)
	{
		printf("%-10s %-5d %-5d %-4d\n", a.tur.beach.season, a.tur.beach.tw,
		a.tur.beach.ta, a.tur.beach.time);
	}
}

int save(char *filename, struct country a)
{
	FILE *f = fopen(filename, "wb");
	fwrite(&a, sizeof(struct country), 1, f);
	fclose(f);
	return 0;
}

int read(char *filename, struct country a)
{
	FILE *f = fopen(filename, "rb");
	fread(&a,sizeof(struct country), 1, f);
	print_a(a);
	fclose(f);
	return 0;
}

int read_txt(FILE *f, struct country *a)
{
	
	if (!f)
		return ERR_IO;
	
	char buf[N+1];

	if (fscanf(f,"%s", buf) == 1)
	{
	    int i = 0;
	    while (i < N && buf[i] != '\0')
	    {
	        a->name[i] = buf[i];
	        i++;
	    }
	    a->name[i] = '\0';
	}
	else
	{
		
		return ERR_IO;
	} 

	if (fscanf(f,"%d", &(a->people)) != 1)
	{
		return ERR_IO;
	}
	if (fscanf(f,"%s", buf) == 1)
	{
	    int i = 0;
	    while (i < N && buf[i] != '\0')
	    {
	        a->capital[i] = buf[i];
	        i++;
	    }
	    a->capital[i] = '\0';
	}
	else
	{

		return ERR_IO;
	}

	if (fscanf(f,"%s", buf) == 1)
	{
	    int i = 0;
	    while (i < N && buf[i] != '\0')
	    {
	     	a->mainland[i] = buf[i];
	       	i++;
	    }
	    a->mainland[i] = '\0';
	}
	else
	{
		return ERR_IO;
	}
	
	if (fscanf(f,"%s", buf) == 1)
	{
	    if (strcmp(buf, "excursion") == 0)
		{
			strcpy(a->turism, buf);
			if (fscanf(f,"%d", &(a->tur.ex.n)) != 1)
			{
				return ERR_IO;
			}
			
			if (fscanf(f,"%s", buf) == 1)
			{
				int i = 0;
	            while (i < N && buf[i] != '\0')
	            {
	                a->tur.ex.type[i] = buf[i];
	                i++;
	            }
	            a->tur.ex.type[i] = '\0';
			}
			else 
			{
				return ERR_IO;
			}
		}
	    else if (strcmp(buf, "sport") == 0)
		{
			strcpy(a->turism, buf);
			if (fscanf(f,"%s", buf) == 1)
			{
				int i = 0;
	            while (i < N && buf[i] != '\0')
	            {
	                a->tur.sport.type[i] = buf[i];
	                i++;
	            }
	            a->tur.sport.type[i] = '\0';
			}
			else 
			{
				return ERR_IO;
			}
		
			if (fscanf(f,"%d", &(a->tur.sport.cost)) != 1)
			{
				return ERR_IO;
			}
		}
		else if (strcmp(buf, "beach") == 0)
		{
			strcpy(a->turism, buf);
		
			if (fscanf(f,"%s", buf) == 1)
			{
				int i = 0;
	            while (i < N && buf[i] != '\0')
	            {
	                a->tur.beach.season[i] = buf[i];
	                i++;
	            }
	            a->tur.beach.season[i] = '\0';
				}
			else 
			{
				return ERR_IO;
				
			}
		
			if (fscanf(f,"%d", &(a->tur.beach.tw)) != 1)
			{
				return ERR_IO;
			}
			if (fscanf(f, "%d", &(a->tur.beach.ta)) != 1)
			{
				return ERR_IO;
			}
			
			if (fscanf(f, "%d", &(a->tur.beach.time)) != 1)
			{
				return ERR_IO;
			}
		}
		else
		{
			return ERR_IO;
		}
	}
    else 
    {
		return ERR_IO;
	}

	return 0;
}

int save_txt(char *filename, struct country a)
{
	FILE *f = fopen(filename, "a");
	if (!f)
		return ERR_IO;
	fprintf(f,"%s %d %s %s %s ", a.name, a.people, a.capital,
	a.mainland, a.turism);
	if (strcmp(a.turism, "excursion") == 0)
	{
		fprintf(f,"%d %s\n", a.tur.ex.n, a.tur.ex.type);
	}
	if (strcmp(a.turism, "sport") == 0)
	{
		fprintf(f,"%s %d\n", a.tur.sport.type, a.tur.sport.cost);
	}
	if (strcmp(a.turism, "beach") == 0)
	{
		fprintf(f,"%s %d %d %d\n", a.tur.beach.season, a.tur.beach.tw,
		a.tur.beach.ta, a.tur.beach.time);
	}
	fclose(f);
	return 0;
}