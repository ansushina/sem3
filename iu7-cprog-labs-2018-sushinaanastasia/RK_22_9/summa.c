
#include "summa.h"

void reverse(int *a, int n, int *c)
{
	for (int z = 0; z < n; z++)
	{
		c[n - z-1] = a[z];
	}
}

int get_summa(const int *a, int n1,const int *b, int n2, int *c, int *n3)
{
	assert(a != NULL);
	assert(b != NULL);
	assert(c != NULL);
	assert(n1 > 0);
	assert(n1 <= 20);
	assert(n2 > 0);
    assert(n2 <= 20);
	
	int el, el1 = 0;
	int n;
	int d[N+1];
	//printf("%d %d\n",n1,n2);
	
	if (n1 > n2)
		n = n2;
	else 
		n = n1;

	
	for (int i = 0; i < n; i++)
	{
		el = a[n1-i-1] + b[n2-i-1] + el1;
		el1 = 0;
		//printf("%d",el);
		if (el > 9)
		{
			el1 = 1;
			el %= 10;
		}		
		d[i] = el;
	}
	
	*n3 = n;
	
	//for (int i = 0; i < *n3; i++)
	//		printf("%d ", d[i]);
	
	if (n1 > n2)
	{
		while (el1 == 1)
		{
			el = a[n1-n-1] + el1;
		    el1 = 0;
            if (el > 9)
		    {
			    el1 = 1;
			    el %= 10;
		    }		
		    d[n] = el;
			n++;
			*n3 += 1;
		}
		for (int j = n; j < n1; j++)
		{
			d[j] = a[n1-j-1];
			*n3 += 1;
		}
	}
	else if (n2 > n1)
	{
		while (el1 == 1 && n < n2)
		{
			el = b[n2-n-1] + el1;
		    el1 = 0;
			//printf("%d\n",el);
            if (el > 9)
		    {
			    el1 = 1;
			    el %= 10;
		    }		
		    d[n] = el;
			n++;
			*n3 += 1;
		}
		for (int j = n; j < n2; j++)
		{
			d[j] = b[n2-j-1];
			*n3 += 1;
		}
	}
	if (el1 == 1)
	{
		d[n] = 1;
		*n3 +=1;
	}
	
	reverse(d,*n3,c);
	
	return OK;
}