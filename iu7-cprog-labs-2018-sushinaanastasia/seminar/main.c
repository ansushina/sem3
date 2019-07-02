#include"io.h"
#include"process.h"
#include"string.h"

//app.exe filename action(sort change)
int main(int argc, char *argv[])
{
	int rc;
	double **mtr;
	int n, m;
	if (argc != 3 || (strcmp(argv[2], "sort") != 0 && strcmp(argv[2], "change") != 0))
	{
		printf("app.exe filename action(sort change)\n");
		return ERR_PARAM;
	}
	
	
	rc = mtr_read(argv[1], &mtr, &n, &m);
	if (rc == OK)
	{
		printf("before: \n");
		mtr_print(mtr, n , m);
		printf("after:\n");
		if (strcmp(argv[2], "sort") == 0)
		{
			sort(mtr, n, m);
			mtr_print(mtr, n , m);
		}
		else if (strcmp(argv[2], "change") == 0)
		{
			change(mtr, n, m);
			mtr_print(mtr, n , m);
		}
		mtr_free(mtr, n);
	}
	else if (rc == ERR_IO)
	{
		printf("Input error!\n");
	}
	else if (rc == ERR_FILE)
	{
		printf("File can't be open!\n");
	}
	else 
	{
		printf("MEmory error!\n");
	}
	
	return rc;
}
