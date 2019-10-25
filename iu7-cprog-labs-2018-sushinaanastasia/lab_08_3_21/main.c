#include"errors.h"
#include"io.h"
#include"sum.h"
#include"multiply.h"
#include"process.h"
#include"matrix.h"

#include<string.h>

/**
 * @brief info
 * Информация
 */
void info()
{
	printf("INFORMATION: \n");
	printf("START:\n");
	printf("app.exe action mtr_1.txt <mtr_2.txt> res.txt\n");
	printf("Actions:\n");
	printf("a - addition (need mtr_1.txt, mtr_2.txt, res.txt)\n");
	printf("m - multiply (need mtr_1.txt, mtr_2.txt, res.txt)\n");
	printf("o - Gauss(need mtr_1.txt, res.txt)\n");
	printf("h - help (need nothing)\n");
}


int main(int argc, char *argv[])
{
	int rc = OK;
	double **a, **b, **c;
	int n1, m1, n2, m2;
	
	if (argc == 2 && strcmp(argv[1], "h") == 0)
	{
		info();
		return OK;
	}
	
	if (argc != 4 && argc != 5)
	{
		printf("app.exe action mtr_1.txt <mtr_2.txt> res.txt!\n");
		return ERR_PARAM;
	}
	
	if ((strcmp(argv[1], "a") == 0 || strcmp(argv[1], "m") == 0) && argc == 5)
	{
		rc = read_matrix(argv[2], &a, &n1, &m1);
			
		if (rc == OK)
		{
			rc = read_matrix(argv[3], &b, &n2, &m2);
			if (rc == OK)
			{
				if (strcmp(argv[1], "a") == 0)
				{
					rc = sum(a, n1, m1, b, n2, m2, &c);
				}
				else if (strcmp(argv[1], "m") == 0)
				{
					rc = multiply(a, n1, m1, b, n2, m2, &c);
				}
				if (rc == OK)
				{
					print_matrix(argv[4], c, n1, m2);
					free_matrix(c, n1);
				}
				else if (rc == ERR_MULT)
					printf("Can't get multiply!\n");
				else if (rc == ERR_SUM)
					printf("Can't get addition!\n");
				else 
					printf("MEMORY ERROR3\n");
				//print_matrix(argv[4], a, n1, m1);
				free_matrix(b, n2);
			}
			else if (rc == ERR_READ)
			    printf("IO error in second file.\n");
		    else if (rc == ERR_FILE)
				printf("second file can't be opened!\n");
			else if (rc == ERR_RANGE)
			    printf("Wrong params in second file!\n");
		    else 
			    printf("MEMORY ERROR2\n");
			
			//printf("n %d m %d", n1, m1);
			//print_matrix(argv[4], a, n1, m1);*/
			free_matrix(a, n1);
		}
		else if (rc == ERR_READ)
			printf("IO error in first file.\n");
		else if (rc == ERR_FILE)
			printf("first file can't be opened!\n");
		else if (rc == ERR_RANGE)
			printf("Wrong params in first file!\n");
		else 
			printf("MEMORY ERROR1\n");
	}
	else if (strcmp(argv[1], "o") == 0 && argc == 4)
	{
		rc = read_matrix(argv[2], &a, &n1, &m1);
		if (rc == OK)
		{
			rc = do_gauss(a, n1, m1, &c);
			if (rc == OK)
			{
				rc = print_matrix(argv[3], c, n1, 1);
				if (rc != OK)
					printf("File ERROR");
				free_matrix(c, n1);
			}
			else if (rc == ERR_GAUSS)
				printf("Can't do gauss!\n");
			else 
				printf("MEMORY ERROR4\n");
			free_matrix(a, n1);
		}
		else if (rc == ERR_READ)
			printf("IO error in first file.\n");
		else if (rc == ERR_FILE)
			printf("first file can't be opened!\n");
		else if (rc == ERR_RANGE)
			printf("Wrong params in first file!\n");
		else 
			printf("MEMORY ERROR1\n");
	}
	else 
		rc = ERR_PARAM;
	
	return rc;
}
