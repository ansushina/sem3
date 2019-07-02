 #include "summa.h"
 
 #define YES 1
 #define NO 0
 
 int is_eq(int *a, int n1, int *b, int n2)
 {
	 if (n1 != n2)
		 return NO;
	 for (int i = 0; i < n1; i++)
	 {
		 if (a[i] != b[i])
             return NO;
	 }			 
	 return YES;
 } 
 
 void test_get_sum(void)
 {
	 {
		 int a[] = {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		 int b[] = {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		 int c[N+1], n3;
		 int c1[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		 int rc;
		 
		 rc = get_summa(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0]), c, &n3);
		 printf("TEST1: ");
		 if (rc == OK)
		 {
			 if (is_eq(c, n3, c1, sizeof(c1)/sizeof(c1[0])))
				 printf("OK\n");
			 else
				 printf("FAIL(array)\n");
		 }
		 else
			 printf("FAIL(%d)\n",rc);
	 }
	 {
		 int a[] = {1,0,2,4};
		 int b[] = {5,0,3,2,1};
		 int c[N+1], n3;
		 int c1[] = {5,1,3,4,5};
		 int rc;
		 
		 rc = get_summa(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0]), c, &n3);
		 printf("TEST2: ");
		 if (rc == OK)
		 {
			 if (is_eq(c, n3, c1, sizeof(c1)/sizeof(c1[0])))
				 printf("OK\n");
			 else
				 printf("FAIL(array)\n");
		 }
		 else
			 printf("FAIL(%d)\n",rc);
	 }
	 
	 {
		 int a[] = {1,0,0,9};
		 int b[] = {5,0,3,0,4};
		 int c[N+1], n3;
		 int c1[] = {5,1,3,1,3};
		 int rc;
		 
		 rc = get_summa(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0]), c, &n3);
		 printf("TEST3: ");
		 if (rc == OK)
		 {
			 if (is_eq(c, n3, c1, sizeof(c1)/sizeof(c1[0])))
				 printf("OK\n");
			 else
				 printf("FAIL(array)\n");
		 }
		 else
			 printf("FAIL(%d)\n",rc);
	 }
	 
	 {
		 int a[] = {7,0,0,0,9};
		 int b[] = {5,0,3,0,4};
		 int c[N+1], n3;
		 int c1[] = {1,2,0,3,1,3};
		 int rc;
		 
		 rc = get_summa(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0]), c, &n3);
		 printf("TEST4: ");
		 if (rc == OK)
		 {
			 if (is_eq(c, n3, c1, sizeof(c1)/sizeof(c1[0])))
				 printf("OK\n");
			 else
				 printf("FAIL(array)\n");
		 }
		 else
			 printf("FAIL(%d)\n",rc);
	 }
	 
	 {
		 int a[] = {1,0,0,9,0,0};
		 int b[] = {5,0,3,0,4};
		 int c[N+1], n3;
		 int c1[] = {1,5,1,2,0,4};
		 int rc;
		 
		 rc = get_summa(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0]), c, &n3);
		 printf("TEST5: ");
		 if (rc == OK)
		 {
			 if (is_eq(c, n3, c1, sizeof(c1)/sizeof(c1[0])))
				 printf("OK\n");
			 else
				 printf("FAIL(array)\n");
		 }
		 else
			 printf("FAIL(%d)\n",rc);
	 }
	 
	 {
		 int a[] = {1,0,0,0,0};
		 int b[] = {5,0,3,0,4};
		 int c[N+1], n3;
		 int c1[] = {6,0,3,0,4};
		 int rc;
		 
		 rc = get_summa(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0]), c, &n3);
		 printf("TEST6: ");
		 if (rc == OK)
		 {
			 if (is_eq(c, n3, c1, sizeof(c1)/sizeof(c1[0])))
				 printf("OK\n");
			 else
				 printf("FAIL(array)\n");
		 }
		 else
			 printf("FAIL(%d)\n",rc);
	 }
	 
	 	 {
		 int a[] = {1};
		 int b[] = {9,9,9};
		 int c[N+1], n3;
		 int c1[] = {1,0,0,0};
		 int rc;
		 
		 rc = get_summa(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0]), c, &n3);
		 printf("TEST7: ");
		 if (rc == OK)
		 {
			 if (is_eq(c, n3, c1, sizeof(c1)/sizeof(c1[0])))
				 printf("OK\n");
			 else
				 printf("FAIL(array)\n");
		 }
		 else
			 printf("FAIL(%d)\n",rc);
	 }
	 	 {
		 int a[] = {2,8,2,1};
		 int b[] = {3,9,7,2,3};
		 int c[N+1], n3;
		 int c1[] = {4,2,5,4,4};
		 int rc;
		 
		 rc = get_summa(a, sizeof(a)/sizeof(a[0]), b, sizeof(b)/sizeof(b[0]), c, &n3);
		 printf("TEST8: ");
		 if (rc == OK)
		 {
			 if (is_eq(c, n3, c1, sizeof(c1)/sizeof(c1[0])))
				 printf("OK\n");
			 else
				 printf("FAIL(array)\n");
		 }
		 else
			 printf("FAIL(%d)\n",rc);
	 }
 }
 
 void test_reverse(void)
 {
    {
		 int a[] = {2,8,2,1};
		 int c[N+1];
		 int c1[] = {1,2,8,2};
		 
		 reverse(a, sizeof(a)/sizeof(a[0]), c);
		 printf("TEST REVERSE\nTEST1: ");
		 if (is_eq(c, sizeof(a)/sizeof(a[0]) , c1, sizeof(c1)/sizeof(c1[0])))
			printf("OK\n");
		 else
			printf("FAIL(array)\n");
    }
	{
		 int a[] = {0,0,0,0,1};
		 int c[N+1];
		 int c1[] = {1,0,0,0,0};
		 
		 reverse(a, sizeof(a)/sizeof(a[0]), c);
		 printf("TEST2: ");
		 if (is_eq(c,sizeof(a)/sizeof(a[0]) , c1, sizeof(c1)/sizeof(c1[0])))
			printf("OK\n");
		 else
			printf("FAIL(array)\n");
    }
 }
 int main(void)
 {
	 test_get_sum();
	 test_reverse();
	 
	 return 0;
 }