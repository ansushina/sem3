#include"io.h"
#include"process.h"
#include<string.h>

int main(int argc, char *argv[])
{
	int rc;
	double **matrix;
    int n, m, n2;	
	double *array;
	
	if (argc != 3 || (strcmp(argv[2], "-r") != 0 && strcmp(argv[2], "-m") != 0))
	{
		printf("app.exe filename action\n");
		printf(" -r replace\n -m make massiv \n");
		return ERR_PARAM;
	}
	
	rc = read_matrix(argv[1], &matrix, &n, &m);
	if (rc == OK)
	{
		print_matrix(matrix, n, m);
		if (strcmp(argv[2], "-r") == 0)
		{
			rc = reverse(matrix, n, m);
			if (rc == OK)
			{
				print_matrix(matrix, n, m);
			}
			else if (rc == ERR_MTR)
			{
				printf("n = m!\n");
			}
			else if (rc == ERR_NULL)
			{
				printf("NULL parameter in func!\n");
			}
		}
		else if (strcmp(argv[2], "-m") == 0)
		{
			if (n == m)
			{
				array = make_array(matrix, n , m, &n2);
				if (array)
				{
					print_array(array, n2);
					free(array);
				}
				else
				{
					rc = ERR_MEMORY;
					printf("Memory ERRor or no elemets more then arg");
				}
			}
			else
			{
				rc = ERR_MTR;
				printf("n = m!\n");
			}
		}
		free_matrix(matrix, n);
	}
	else if (rc == ERR_IO)
	{
		printf("Input error");
	}
	else if (rc == ERR_MEMORY)
	{
		printf("Memory ERRor");
	}
	else 
	{
		printf("file error");
	}
	
	return rc;
}