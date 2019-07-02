#include "process.h"
#include "errors.h"
#include<stdlib.h>
#include<time.h>
#include<stdint.h>
#include<inttypes.h>

#define M 1000
#define L 20

void create_sort_array(int *ab, int *ae)
{
	for (int *pj = ab; pj < ae; pj++)
	    *pj = pj - ab;
}

void create_unsort_array(int *ab, int *ae)
{
	for (int *pj = ab; pj < ae; pj++)
		*pj = ae - pj;
}

void create_rand_array(int *ab, int *ae)
{
	for (int *pj = ab; pj < ae; pj++)
	    *pj = rand();
}

unsigned long long tick(void)
{
	unsigned long long d;
	
	__asm__ __volatile__("rdtsc" : "=A" (d));
	
	return d;
}

int main(void)
{
	int a[M];
	long int tb, te;
	long int t1, t2;
	FILE *s1, *u1, *r1, *s2, *u2, *r2, *s3, *u3, *r3;
	
	srand(time(NULL));
	s1 = fopen("sort1.txt", "w");
	u1 = fopen("unsort1.txt", "w");
	r1 = fopen("rand1.txt", "w");
	for (int i = 1; i < 10; i++)
	{
		create_sort_array(a, a + i);
		tb = tick();
		for (int j = 0; j < L; j++)
		    mysort(a, i, sizeof(int), cmp_int);
		te = tick();
		t1 = (te - tb) / L;
		
		tb = tick();
		for (int j = 0; j < L; j++)
		    qsort(a, i, sizeof(int), cmp_int);
		te = tick();
		t2 = (te - tb) / L;	
		
		fprintf(s1, "%d %ld %ld \n", i, t1, t2);
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{  
		    create_unsort_array(a, a + i);
		    mysort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t1 = (te - tb) / L;
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{
		    create_unsort_array(a, a + i);
		    qsort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t2 = (te - tb) / L;	
		
		fprintf(u1, "%d %ld %ld \n", i, t1, t2);
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{
		    create_rand_array(a, a + i);
		    mysort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t1 = (te - tb) / L;
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{
		    create_rand_array(a, a + i);
		    qsort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t2 = (te - tb) / L;		
	
		fprintf(r1, "%d %ld %ld \n", i, t1, t2);
	}
	
	fclose(s1);
	fclose(u1);
	fclose(r1);
	
	s2 = fopen("sort2.txt", "w");
	u2 = fopen("unsort2.txt", "w");
	r2 = fopen("rand2.txt", "w");
	for (int i = 10; i < 100; i += 10)
	{
		create_sort_array(a, a + i);
		tb = tick();
		for (int j = 0; j < L; j++)
		    mysort(a, i, sizeof(int), cmp_int);
		te = tick();
		t1 = (te - tb) / L;
		
		tb = tick();
		for (int j = 0; j < L; j++)
		    qsort(a, i, sizeof(int), cmp_int);
		te = tick();
		t2 = (te - tb) / L;	
		
		fprintf(s2, "%d %ld %ld \n", i, t1, t2);
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{  
		    create_unsort_array(a, a + i);
		    mysort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t1 = (te - tb) / L;
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{
		    create_unsort_array(a, a + i);
		    qsort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t2 = (te - tb) / L;	
		
		fprintf(u2, "%d %ld %ld \n", i, t1, t2);
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{
		    create_rand_array(a, a + i);
		    mysort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t1 = (te - tb) / L;
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{
		    create_rand_array(a, a + i);
		    qsort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t2 = (te - tb) / L;		
	
		fprintf(r2, "%d %ld %ld \n", i, t1, t2);
	}
	
	fclose(s2);
	fclose(u2);
	fclose(r2);
	
	s3 = fopen("sort3.txt", "w");
	u3 = fopen("unsort3.txt", "w");
	r3 = fopen("rand3.txt", "w");
	for (int i = 100; i < 1000; i += 100)
	{
		create_sort_array(a, a + i);
		tb = tick();
		for (int j = 0; j < L; j++)
		    mysort(a, i, sizeof(int), cmp_int);
		te = tick();
		t1 = (te - tb) / L;
		
		tb = tick();
		for (int j = 0; j < L; j++)
		    qsort(a, i, sizeof(int), cmp_int);
		te = tick();
		t2 = (te - tb) / L;	
		
		fprintf(s3, "%d %ld %ld \n", i, t1, t2);
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{  
		    create_unsort_array(a, a + i);
		    mysort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t1 = (te - tb) / L;
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{
		    create_unsort_array(a, a + i);
		    qsort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t2 = (te - tb) / L;	
		
		fprintf(u3, "%d %ld %ld \n", i, t1, t2);
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{
		    create_rand_array(a, a + i);
		    mysort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t1 = (te - tb) / L;
		
		tb = tick();
		for (int j = 0; j < L; j++)
		{
		    create_rand_array(a, a + i);
		    qsort(a, i, sizeof(int), cmp_int);
		}
		te = tick();
		t2 = (te - tb) / L;		
	
		fprintf(r3, "%d %ld %ld \n", i, t1, t2);
	}
	
	fclose(s3);
	fclose(u3);
	fclose(r3);
}