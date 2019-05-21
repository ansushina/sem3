#include"io.h"
#include"process.h"
#include<string.h>

void menu()
{
	printf("\nActions:\n");
	//printf("new - to create new file\n");
	printf("1. plus - to add new line\n");
	printf("2. delete - to delete line\n");
	printf("3. print - to print table from file\n");
	printf("4. find - to find elemets by flag\n");
	printf("5. sort - to sort table\n");
	printf("6. end - to end program\n\n");
}

void info()
{
	printf("This program makes operations with table.\n");
	printf("Counrty: \n");
	printf("Name People Capital Mainland Tourism \n");
	printf("Variable part:\n");
	printf("sport: type cost\n");
	printf("excursion: n type\n");
	printf("beach: season watert airt time\n\n");
}

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__("rdtsc" : "=A" (d));
	return d;
}

int main()
{
	int action;
	char filename[N+1] = "1.txt";
	char buf[N+1];
	int rc;
	struct country all[M];
	struct keys key[M];
	int n;
	long int tb, te;
	long int t1, t2, t3,t4;
	int m1, m2, m3;
	setbuf(stdout, NULL);
	
	info();
	
	int k = 1;
	while (k)
	{
		menu();
		printf("Input action(number): ");
		if (scanf("%d", &action) == 1)
		{
			if (action == 6)
				k = 0;
			else if (action == 1)
			{
				struct country a;
				
				read_new(&a);
					//print_a(a);
				rc = save_txt(filename, a);
				if (rc != 0)
					printf("Can't open file!\n");
				printf("DONE\n");
					//printf("%d", rc);
			}
			else if (action == 2)
			{
				rc = delete(filename);
				if (rc != 0)
					printf("\nERROR\n");
			}
			else if (action == 3)
			{
				struct country a;
				
				rc = 0;
				int i = 0;
				FILE *f = fopen(filename,"r");
				if (rc != 0)
					printf("Can't open file!\n");
				printf("\n");
				p();
				while (rc == 0 && i < M)
				{
			        rc = read_txt(f, &a);
				    if (rc == 0)
					{
				        print_a(a);
					}
					i++;
				}
				printf("\n");
					//printf("DONE\n");
				fclose(f);

			}
			else if (action == 4)
			{
				int b;
				printf(" 1. Europe \n 2. Asia\n 3. NortAmerica\n 4. SouthAmerica\n 5. Australia \n 6. Africa \n");
		        printf("Input mainland of country(number):");
	            if (scanf("%d", &b) == 1)
	            {
					int f = 1;
	        		if (b == 1)
	                    strcpy(buf, "Europe");
	        		else if (b == 2)
	                    strcpy(buf, "Asia");
	        		else if (b == 3)
	                    strcpy(buf, "NorthAmerica");
	        		else if (b == 4)
	                    strcpy(buf, "SouthAmerica");
		        	else if (b == 5)
	                    strcpy(buf, "Australia");
		        	else if (b == 6)
	                    strcpy(buf, "Africa");
					else
						f = 0;
					if (f)
					{
						printf("1. sport \n2. beach \n3. excursion\n");
						printf("Input tourism(number): ");
						if (scanf("%d", &b) == 1)
						{
							if (b == 1)
							{
								find(filename, buf, "sport");
							}
							else if (b == 2)
							{
								find(filename, buf, "beach");
							}
							else if (b == 3)
							{
								find(filename, buf, "excursion");
							}
							else 
								printf("Input error\n");
						}
					}
					else
						printf("Input error\n");
				}
			}
			else if (action == 5)
			{

				read_all(filename, all, &n);
					
				tb = tick();
				sort1(all, n, &m1);
				te = tick();
				t1 = te - tb;
					
				printf("Table sort sort table: ");
				printf("\n");
				p();
				for (int i = 0; i < n; i++)
					print_a(all[i]);
				printf("\n");
				
				read_all(filename, all, &n);
				
				tb = tick();
				sort2(all, n, key, &m2);
				te = tick();
				t2 = te-tb;
					
				printf("Key table: \n");
				printf("  n     people\n");
				for (int i = 0; i < n; i++)
					printf("%-7d %-10d\n", key[i].n, key[i].people);
				printf("\n");
				
				printf("Do you want to print sort table by keys table? y/n: ");
					
				if (scanf("%s", buf) == 1 && strcmp(buf, "y") == 0)
				{
					printf("\n");
					p();
					for (int i = 0; i < n; i++)
						print_a(all[key[i].n]);
				}
				printf("\n");
				tb = tick();
				sort3(all, n, key, &m3);
				te = tick();
				t3 = te-tb;
				
				tb = tick();
				sort4(all, n, &m1);
				te = tick();
				t4 = te - tb;
					
				printf(" time 1 table bubble: %ld \n time 2 key bubble: %ld\n time 3 key insert: %ld \n", t1, t2, t3);
				printf("time 4 table inseart: %ld \n", t4);
				
				m1 = sizeof(struct country) * (n + 1);
                m2 = sizeof(struct country) * n + sizeof(struct keys)*(n+1);
                m3 = sizeof(struct country) * n +	sizeof(struct keys)*(n+1) + sizeof(int)*3;
                int m4 = sizeof(struct country) * (n+1) + sizeof(int)*3;
				printf("\n mem1(table bubble ): %d\n mem2(key bubble): %d\n mem3(key Inseart): %d\n mem 4(table insert); %d\n \n", m1, m2, m3, m4);
				double  x1 = (t1 - t2)*100/t1;
				double  x2 = (t2 - t3)*100/t2;
				printf("Key sort vs table sort: %lf \n", x1 );
				printf("Bubble vs insert : %lf  \n", x2);
			}
		
			/*printf("\nDo you want to quit? y/n :");
			if (scanf("%s", buf) == 1)
			{
				if (strcmp(buf, "y") == 0)
					k = 0;
				else 
					k = 1;
			}*/
	    }
		else 
		{
			gets(buf);
		    printf("\nInput error\n\n");
		}
	}
	
	
	return 0;
}