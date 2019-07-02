#include"errors.h"
#include"process.h"
#include"io.h"

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);
	FILE *f, *f1;
	char *source = NULL, *new;
	int rc = OK, u;
	size_t n = 0;
	if (argc != 7)
	{
		printf("app.exe in.txt out.txt –s search –r replace \n");
		return ERR_PARAM;
	}
	if (my_strcmp(argv[3], "-s") != 0 || my_strcmp(argv[5], "-r") != 0)
	{
		printf("app.exe in.txt out.txt –s search –r replace \n");
		return ERR_PARAM;
	}
	f = fopen(argv[1], "r");
	
    if (f)
	{
		f1 = fopen(argv[2], "w");
		if (f1)
		{
		    u = my_getline(&source, &n, f);
			if (u == -1)
			{
				printf("Can't get line from file\n");
				rc = ERR_IO;
			}
			while (u > 0)
			{
			    new = str_replace(source, argv[4], argv[6]);
				if (new)
				{
				    printf("%s", new);
	    			print_str(f1, new);
		    	    free(new);
			    }
				free(source);
				n = 0;
				source = NULL;
                u = my_getline(&source, &n, f);
			}
			fclose(f1);
		}
		else
		{
			printf("File 2 can't be open!\n");
			rc = ERR_IO;
		}
		fclose(f);
	}
    else
	{
		printf("File in can't be open!\n");
		rc = ERR_IO;
	}
	return rc;
}