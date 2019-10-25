/*
Составить программу выполняющую сложения 20 значных чисел.
Элементы массива располагаются в текстовых файлах.
Первая строка массива - количество элементов. 
Имена текстовых файлов передаются в командной строке.
*/

#include "summa.h"
#include "io.h"

int main(int argc, char **argv)
{
	int rc;
	FILE *f;
	
	int n1,n2,n3;
    int a[N], b[N], c[N+1];
	
	if (argc != 3)
	{
		printf("app.exe <file-name> <file-name>!\n");
		return ERR_PARAM;
	}
	
	f = fopen(argv[1], "r");
	
	if (f)
	{
		rc = array_read(f, a, &n1);
		fclose(f);
		if (rc == ERR_IO)
		{
			printf("Input error!\n");
			return rc;
		}
		if (rc == ERR_RANGE)
		{
			printf("Range error. N1 from one to twenty. \
			a1[i] from zero to nine!/n");
			return rc;
		}
	}
	else
	{
		printf("File 1 can't be open!");
		return ERR_IO;
	}
	
	f = fopen(argv[2], "r");
	
	if (f)
	{
		rc = array_read(f, b, &n2);
		fclose(f);
		if (rc == ERR_IO)
		{
			printf("Input error!\n");
			return rc;
		}
		if (rc == ERR_RANGE)
		{
			printf("Range error. N2 from one to twenty. \
			b[i] from zero to nine!/n");
			return rc;
		}
	}
	else
	{
		printf("File 2 can't be open!\n");
		return ERR_IO;
	}
	//rray_print(a,n1);
	//array_print(b,n2);
	//printf("%d %d \n",n1,n2);
	rc = get_summa(a, n1, b, n2, c, &n3);
	//printf("%d %d\n",rc, n3);
	
	if (rc == OK)
	{
		array_print(c, n3);
	}
	else 
	{
		printf("Too big numbers, can't create sum! \n");
	}
	
	return rc;
}