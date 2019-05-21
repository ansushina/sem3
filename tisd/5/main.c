//** единый алгоритм 
//** вектор + список
//** все в отдельных подпрограммах 
//** адреса элементов очереди(список)
//** выдать на экран общеее время моделировая
//** после 100 заявок 1ого типа 
//** текущая длина 
//**+средняя 
//** среднее время пребывая заявок в очкереди
//** время простоя 
//** количество вошедших в систему 
//** количество вышедщих
//** возможность изменения время прихода и обратоки заявок
//** наличие пояснений 
//** вывод процента погрешности работы программы 
//** время выполнения программы при реализоции списком, массивом 
// объем памяти 
//** переполнение очереди? 
// фрагментация памяти? 

 /*
 Система массового обслуживания состоит из обслуживающего аппарата (ОА) и 
двух очередей заявок двух типов. 
Заявки 1-го и 2-го типов поступают в "хвосты" своих очередей по случайному закону 
с интервалами времени Т1 и Т2, равномерно распределенными от 1 до 5  и от 0 до 3 
единиц времени (е.в.) соответственно. В ОА они поступают из "головы" очереди по 
одной и обслуживаются также равновероятно за времена Т3 и Т4, распределенные 
от 0 до 4 е.в. и от 0 до 1 е.в. соответственно, после чего покидают систему. 
(Все времена – вещественного типа)  В начале процесса в системе заявок нет. 
Заявка любого типа может войти в ОА, если: 
 а) она вошла в пустую систему; 
 б) перед ней обслуживалась заявка ее же типа; 
 в) перед ней из ОА вышла заявка другого типа, оставив за собой пустую очередь 
 (система с чередующимся приоритетом).  
 Смоделировать процесс обслуживания первых 1000 заявок 1-го типа,
выдавая после обслуживания каждых 100 заявок информацию о текущей и средней
длине каждой очереди, а в конце процесса - общее время моделирования и 
количество вошедших в систему и вышедших из нее заявок обоих типов.  
По требованию пользователя выдать на экран адреса элементов очереди 
при удалении и добавлении элементов.
Проследить, возникает ли при этом фрагментация памяти. 
 
 */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define OK 0
#define ERR_READ 1
#define ERR_PARAM 2
#define ERR_MEMORY 3
#define ERR_NULL 4
#define ERR_RANGE 5
#define ERR_FILE 6
#define ERR_IO 7
#define ERR_FULL 8
#define ERR_EMPTY 9

#define N 1000
#define M 100

void menu()
{
	printf("\nActions:\n");
	printf("1. Run with massiv \n");
	printf("2. Run with spisok\n");
	printf("3. Print parameters \n");
	printf("4. Change parameters\n");
	printf("5. Return original parameters\n");
	printf("6. Run with adresses\n");
	printf("7. exit\n");
}

void info()
{
	printf("\nThis program makes operations with order\n");
	printf("Two orders, one OA;\n T1 from 1 to 5;\n T2 from 0 to 3\n");
	printf("T3 from 0 to 4;\n T4 from 0 to 1;\n All times are double\n");
	printf("Number of calls is 1000\n");
	printf("for each 100 calls print info");
    printf("\n");
}

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__("rdtsc" : "=A" (d));
	return d;
}

struct j
{
	double i;
	struct j *next;
};

struct j *create_j(double i)
{
	struct j *p = malloc(sizeof(struct j));
	if (p)
	{
		p->i = i; 
		p->next = NULL;
	}
	return p;
}

void free_list(struct j *head)
{
	struct j *p;
	while (head)
	{
		p = head;
		head = head->next;
		free(p);
	}
}

int add_m(double **pin, double **pout, double *mas, double i)
{
	if (!(*pin) || !mas || !(*pout))
		return ERR_NULL;
	**pin = i;
	*pin += 1;
	if (*pin == mas + N)
		*pin = mas;
	if (*pin == *pout)
		return ERR_FULL;
	
	//printf("pin %p\n", (void *)*pin);
	return OK;
}

int pop_m(double **pin, double **pout, double *mas, double *i)
{
	if (!pin || !pout || !mas)
		return ERR_FULL;
	*i = **pout;
	**pout = -1;
	(*pout)++;
	if (*pout == mas + N)
		*pout = mas;
	
	if (*pout == *pin)
		return ERR_EMPTY;
	
	//printf("pout %p\n", (void *)*pout);
	return 0;
}

void print_stack(struct j *head)
{
	if (!head)
		return;
	printf("\nStack:\n ");
	struct j *t = head;
	int i = 0; 
	while (t && i < N)
	{
		i++;
		printf("%f\n", t->i);
		t = t->next;
	}
	printf("\n");
}

int add_s(struct j **pin, struct j **pout, struct j **full, double i)
{
    //if (!pin || !pout ||)
	struct j *pin1 = *pin;
	struct j *new = create_j(i);
	if (new)
	{
	    if (!(*pout))
		{
		   *pout = new;
		    *pin = new;	
		}
	    else
		{
           pin1->next = new;
           *pin = new;	
		}		   
	}
	else 
	{
		return ERR_MEMORY;
	}
	int j;
	for (j = 0; full[j] && j < 2*N; j++);
	full[j] = new;
	//printf("new %p\n", (void *)new);
	return OK;
}

int pop_s(struct j **pin, struct j **pout, struct j **empty, double *i)
{
	
	*i = (*pout)->i;
	struct j *k = *pout;
	if(!(*pout)->next)
	{
		int j;
	    for (j = 0; empty[j]; j++);
	    empty[j] = k;
		free(k);
		
		//printf("free %p\n", (void *)k);
		*pout = NULL;
		return ERR_EMPTY;
	}
	*pout =(*pout)->next;
	
	int j;
	for (j = 0; empty[j]; j++);
	empty[j] = k;
	free(k);
	//printf("free %p\n", (void *)k);
	return OK;
}

double get_rand(int *p)
{
	return (p[1] - p[0])*(double)(rand()/(double)RAND_MAX) + p[0];
}

double find_min(double a, double b, double c)
{
	if (a < b && a < c)
		return a;
	if (b < a && b < c)
		return b;
	return c;
}

void proverka(double tstop, double t_all, int in1, int in2, int *p1, 
    int *p2, int *p3, int *p4)
{
	
	double t_alln, tstopn, tmin;
	double in1n = N; 
	double in2n;
	
	double time1 = ((double)(p1[1] + p1[0]))/2 * N;
	double time2 = ((double)(p3[1] + p3[0]))/2 * N;
	if (time1 > time2)
	{
		t_alln = time1; 
		tmin = time2;
	}
	else 
	{
		t_alln = time2; 
		tmin = time1;
	}
	in1n = t_alln / ((double)(p1[1] + p1[0])/2);
	//printf("%f %f %f %f \n", t_alln, tstopn, in1n, in2n );
	in2n =  t_alln / ((double)(p2[1] + p2[0])/2);
    tstopn = t_alln - tmin - (double)(p4[1] + p4[0])/2 * in2n;
	tstopn *= -1;
	//printf("%f %f %f %f \n", t_alln, tstopn, in1n, in2n );
	double pr1 = abs(t_alln - t_all) / t_alln * 100;  
	double pr2 = abs(in1n - in1) / in1n * 100;  
	double pr3 = abs(in2n - in2) / in2n * 100;

	double max;
    if( pr1 > pr2 && pr1 > pr3)
        max = pr1;
    else if (pr2 > pr1 && pr2 > pr3)
	{
        max = pr2;
	}
    else
	{
        max = pr3;
	}
	printf("Theory results: \n");
	printf("All time of modulation = %lf\n", t_alln);
	printf("Wait time = %lf\n", tstopn);
	printf("in 1 type  = %lf\n", in1n);
	printf("in 2 type  = %lf \n", in2n);
	printf("procent is %f\n", max);
}

void process_m(int *p1, int *p2, int *p3, int *p4)
{
	double mas[N] = {-1}; 
	double mas1[N] = {-1};
	double i;
	double *pin = mas, *pout = mas;//pin - tail pout - head;
	double *pin1 = mas1, *pout1 = mas1;
	
	long long int begin_time, end_time;
	double t1 = 0, t2 = 0, toa = 0, tmin = 0, tstop = 0, t_all = 0; 
	int flag1 = ERR_EMPTY;
	int flag2 = ERR_EMPTY;
	int flag = 0;
	int type = 1;
	int count_in1 = 0, count_out1 = 0, count_in2 = 0, count_out2 = 0;
	int count1 = 0, count2 = 0, count_sr1 = 0, count_sr2 = 0, iter;
	double time_in1 = 0, time_in2 = 0, t1_sr = 0, t2_sr = 0, t3_sr = 0, t4_sr = 0;
	
	begin_time = tick();
	iter = 0;
	while(count_out1 < N)
	{
		iter++;
	    /*for (int j = 0; j < N; j++)
		{
			printf("%lf ", mas[j]);
		}
		printf("\n");
		for (int j = 0; j < N; j++)
		{
			printf("%lf ", mas1[j]);
		}
		printf("\n");*/
		//printf("%lf %lf %lf\n", t1,t2,toa);
		if (flag1 == ERR_FULL || flag2 == ERR_FULL)
		{
			printf("Full first!\n");
			break;
		}
		
		if (t1 == 0)
		{
			t1 = get_rand(p1);
			t1_sr += t1;
		}
	    if (t2 == 0)
		{
			t2 = get_rand(p2);
			t2_sr += t2;
		}
		
		
		if (toa == 0)
		{
			if ((type == 1 && !flag1) || (!flag1 && flag2))
			{
				type = 1;
				toa = get_rand(p3);
				t3_sr += toa;
				//printf("pop 1\n");
				flag1 = pop_m(&pin, &pout, mas, &i);
				time_in1 += t_all - i;
				count_out1++;
				count1--;
				flag = 1;
			}
			else if (!flag2)
			{
				type = 2;
				toa = get_rand(p4);
				t4_sr += toa;
				//printf("pop 2\n");
				flag2 = pop_m(&pin1, &pout1, mas1, &i);
				time_in2 += t_all - i;
				count_out2++;
				count2--;
			}
		}
		if (toa)
		{
		    tmin = find_min(t1, t2, toa);
		}
		else 
		{
			if (t1 < t2)
				tmin = t1;
			else 
				tmin = t2;
		}
		//printf("%lf %lf %lf\n", t1,t2,toa);
		//printf("tmin %lf\n", tmin);
		if (tmin == t1)
		{
			//printf("add 1\n");
			flag1 = add_m(&pin, &pout, mas, t_all);
			count1++;
			count_in1++;
		}
		if (tmin == t2)
		{
			//printf("add 2\n");
			flag2 = add_m(&pin1, &pout1, mas1, t_all);
			count_in2++;
			count2++;
		}
		
		t1 -= tmin;
		t2 -= tmin;
		toa -= tmin;
		
		//printf("%lf %lf %lf\n\n", t1,t2,toa);
		if (toa < 0)
		{
			tstop += toa;
			toa = 0; 
		}
		t_all += tmin;
		count_sr1 += count1;
		count_sr2 += count2;
		
		if (count_out1 % 100 == 0 && flag)
		{
			printf("------------------------------\n");
			printf("out 1 type = %d \n", count_out1);
			printf("in 1 type  = %d\n", count_in1);
	        printf("in 2 type  = %d \n", count_in2);
	        printf("out 2 type = %d \n", count_out2);
			printf("wait in order 1 type = %lf\n", time_in1 / count_out1);
	        printf("wait in order 2 type = %lf\n", time_in2 / count_out2);
			printf("Number of calls in 1 = %d\n", count1);
	        printf("Number of calls in 2 = %d \n", count2 );
			printf("Middle number in 1   = %d\n", count_sr1/iter);
	        printf("Middle number in 2   = %d \n", count_sr2/iter );
			flag = 0;
			printf("\n");
		}
	}
	end_time = tick();
	printf("-------------------------------\n");
	printf("All time of modulation = %lf\n", t_all);
	printf("Wait time = %lf\n", tstop);
	
	printf("in 1 type  = %d\n", count_in1);
	printf("in 2 type  = %d \n", count_in2);
	printf("out 1 type = %d \n", count_out1);
	printf("out 2 type = %d \n", count_out2);
	
	//printf("in_order_sr1 = %lf\n", time_in1 / count_out1);
	//printf("in_order_sr2 = %lf\n", time_in2 / count_out2);
	printf("middle t1 = %lf\n", t1_sr / count_in1);
	printf("middle t2 = %lf\n", t2_sr / count_in2);
	printf("middle t3 = %lf\n", t3_sr / count_out1);
	printf("middle t4 = %lf\n", t4_sr / count_out2);
	
	printf("time in ticks(massiv) = %I64d\n", end_time - begin_time);
	
	proverka(tstop, t_all, count_in1, count_in2, p1, p2, p3, p4);
	begin_time = tick(); 
}

void process_s(int *p1, int *p2, int *p3, int *p4, int f)
{
	
	struct j *empty[2*N] = {NULL};
	struct j *full[2*N] = {NULL};
	struct j *pin = NULL, *pout = NULL;
	
	struct j *empty1[2*N] = {NULL};
	struct j *full1[2*N] = {NULL};
	struct j *pin1 = NULL, *pout1 = NULL;
	
	double i;
	
	long long int begin_time, end_time;
	double t1 = 0, t2 = 0, toa = 0, tmin = 0, tstop = 0, t_all = 0; 
	int flag1 = ERR_EMPTY;
	int flag2 = ERR_EMPTY;
	int flag = 0;
	int type = 1;
	int count_in1 = 0, count_out1 = 0, count_in2 = 0, count_out2 = 0;
	int count1 = 0, count2 = 0, count_sr1 = 0, count_sr2 = 0, iter;
	double time_in1 = 0, time_in2 = 0, t1_sr = 0, t2_sr = 0, t3_sr = 0, t4_sr = 0;
	
	begin_time = tick();
	iter = 0;
	while(count_out1 < N && iter < 100000)
	{
		iter++;
		//printf("%d \n", iter);
	    /*for (int j = 0; j < N; j++)
		{
			printf("%lf ", mas[j]);
		}
		printf("\n");
		for (int j = 0; j < N; j++)
		{
			printf("%lf ", mas1[j]);
		}
		printf("\n");*/
		//printf("%lf %lf %lf\n", t1,t2,toa);
		//print_stack(pout);
		//print_stack(pout1);
		if (flag1 == ERR_FULL || flag2 == ERR_FULL)
		{
			printf("Full first!\n");
			break;
		}
		
		if (t1 == 0)
		{
			t1 = get_rand(p1);
			t1_sr += t1;
		}
	    if (t2 == 0)
		{
			t2 = get_rand(p2);
			t2_sr += t2;
		}
		
		
		if (toa == 0)
		{
			if ((type == 1 && pout) || (pout && !pout1))
			{
				for (int i = 0; i < N; i++)
				{
					if (full[i] == pout)	
					{
				    	full[i] = NULL;
				    }
				}
				type = 1;
				toa = get_rand(p3);
				t3_sr += toa;
				//printf("pop 1\n");
				flag1 = pop_s(&pin, &pout, empty, &i);
				time_in1 += t_all - i;
				count1--;
				count_out1++;
				flag = 1;
			}
			else if (pout1)
			{
				for (int i = 0; i < N; i++)
				{
					if (full1[i] == pout1)	
					{
				    	full1[i] = NULL;
				    }
				}
				type = 2;
				toa = get_rand(p4);
				t4_sr += toa;
				//printf("pop 2\n");
				flag2 = pop_s(&pin1, &pout1, empty1, &i);
				time_in2 += t_all - i;
				count2--;
				count_out2++;
			}
		}
		if (toa)
		{
		    tmin = find_min(t1, t2, toa);
		}
		else 
		{
			if (t1 < t2)
				tmin = t1;
			else 
				tmin = t2;
		}
		//printf("%lf %lf %lf\n", t1,t2,toa);
		//printf("tmin %lf\n", tmin);
		if (tmin == t1)
		{
			//printf("add 1\n");
			flag1 = add_s(&pin, &pout, full, t_all);
			count1++;
			for (int i = 0; i < N; i++)
			{
			    if (empty[i] == pin)	
				{
					empty[i] = NULL;
				}
			}
			
			count_in1++;
		}
		if (tmin == t2)
		{
			//printf("add 2\n");
			flag2 = add_s(&pin1, &pout1, full1, t_all);
			count2++;
			count_in2++;
			for (int i = 0; i < N; i++)
			{
			    if (empty1[i] == pin1)	
			    {
				empty1[i] = NULL;
			    }
			}
		}
		
		t1 -= tmin;
		t2 -= tmin;
		toa -= tmin;
		
		//printf("%lf %lf %lf\n\n", t1,t2,toa);
		if (toa < 0)
		{
			tstop += toa;
			toa = 0; 
		}
		t_all += tmin;
		count_sr1 += count1;
		count_sr2 += count2;
		
		if (count_out1 % 100 == 0 && flag && f != 1)
		{
			printf("------------------------------\n");
			printf("out 1 type = %d \n", count_out1);
			printf("in 1 type  = %d\n", count_in1);
	        printf("in 2 type  = %d \n", count_in2);
	        printf("out 2 type = %d \n", count_out2);
			printf("wait in order 1 type = %lf\n", time_in1 / count_out1);
	        printf("wait in order 2 type = %lf\n", time_in2 / count_out2);
			printf("Number of calls in 1 = %d\n", count1);
	        printf("Number of calls in 2 = %d \n", count2 );
			printf("Middle number in 1   = %d\n", count_sr1/iter);
	        printf("Middle number in 2   = %d \n", count_sr2/iter );
			flag = 0;
			printf("\n");
		}
	}
	end_time = tick();
	printf("-------------------------------\n");
	printf("All time of modulation = %lf\n", t_all);
	printf("Wait time = %lf\n", tstop);
	
	printf("in 1 type  = %d\n", count_in1);
	printf("in 2 type  = %d \n", count_in2);
	printf("out 1 type = %d \n", count_out1);
	printf("out 2 type = %d \n", count_out2);
	
	//printf("in_order_sr1 = %lf\n", time_in1 / count_out1);
	//printf("in_order_sr2 = %lf\n", time_in2 / count_out2);
	printf("middle t1 = %lf\n", t1_sr / count_in1);
	printf("middle t2 = %lf\n", t2_sr / count_in2);
	printf("middle t3 = %lf\n", t3_sr / count_out1);
	printf("middle t4 = %lf\n", t4_sr / count_out2);
	
	printf("time in ticks(spisok) = %I64d\n", end_time - begin_time);
    printf("memory is %d\n", sizeof(struct j) * (count_in1 + count_in2));
	
	proverka(tstop, t_all, count_in1, count_in2, p1, p2, p3, p4);
	
	if (f)
	{
	    printf("\n-----------------\nEPMTY:\n");
		int o = 0;
	    for (int i = 0; i < N; i++)
     	{
		    if (empty[i])	
	    	{
	    		printf("%p \n",(void *)empty[i]);
				o++;
	    	}
	    }
		printf("EMPTY count = %d\n", o);
        printf("\nFULL: \n");
	    for (int i = 0; i < N; i++)
	    {
    	    if (full[i])
	        printf("%p \n", (void *)full[i]);
	    }
		printf("\n --------------\nEPMTY1:\n");
		int o1 = 0;
	    for (int i = 0; i < N; i++)
     	{
		    if (empty1[i])	
	    	{
	    		printf("%p \n",(void *)empty1[i]);
				o1++;
	    	}
	    }
		printf("EMPTY1 count = %d\n", o1);
        printf("\nFULL1: \n");
	    for (int i = 0; i < N; i++)
	    {
    	    if (full1[i])
	        printf("%p \n", (void *)full1[i]);
	    }
	}	
	/*for (int i = 0; i < N; i++)
	{
		if (full[i])
			free(full[i]);
	}
	for (int i = 0; i < N; i++)
    {
		if (full1[i])
			free(full1[i]);
	}*/
	free_list(pout);
	free_list(pout1);
	//printf("time in ticks = %I64d\n", end_time - begin_time);
	
	
	
	begin_time = tick(); 
}


void little_process(int *p1, int *p2, int *p3, int *p4)
{
	struct j *empty[2*N] = {NULL};
	struct j *full[2*N] = {NULL};
	struct j *pin = NULL, *pout = NULL;
	
	struct j *empty1[2*N] = {NULL};
	struct j *full1[2*N] = {NULL};
	struct j *pin1 = NULL, *pout1 = NULL;
	
	double i;
	
	long long int begin_time, end_time;
	double t1 = 0, t2 = 0, toa = 0, tmin = 0, tstop = 0, t_all = 0; 
	int flag1 = ERR_EMPTY;
	int flag2 = ERR_EMPTY;
	int flag = 0;
	int type = 1;
	int count_in1 = 0, count_out1 = 0, count_in2 = 0, count_out2 = 0;
	int count1 = 0, count2 = 0, count_sr1 = 0, count_sr2 = 0, iter;
	double time_in1 = 0, time_in2 = 0, t1_sr = 0, t2_sr = 0, t3_sr = 0, t4_sr = 0;
	
	begin_time = tick();
	iter = 0;
	while(count_out1 < 10)
	{
		iter++;
		if (flag1 == ERR_FULL || flag2 == ERR_FULL)
		{
			printf("Full first!\n");
			break;
		}
		
		if (t1 == 0)
		{
			t1 = get_rand(p1);
			t1_sr += t1;
		}
	    if (t2 == 0)
		{
			t2 = get_rand(p2);
			t2_sr += t2;
		}
		
		
		if (toa == 0)
		{
			if ((type == 1 && pout) || (pout && !pout1))
			{
				for (int i = 0; i < N; i++)
				{
					if (full[i] == pout)	
					{
				    	full[i] = NULL;
				    }
				}
				type = 1;
				toa = get_rand(p3);
				t3_sr += toa;
				printf("free 1 %p\n", (void *)pout);
				flag1 = pop_s(&pin, &pout, empty, &i);
				time_in1 += t_all - i;
				count1--;
				count_out1++;
				flag = 1;
			}
			else if (pout1)
			{
				for (int i = 0; i < N; i++)
				{
					if (full1[i] == pout1)	
					{
				    	full1[i] = NULL;
				    }
				}
				type = 2;
				toa = get_rand(p4);
				t4_sr += toa;
				printf("free 2 %p\n", (void *)pout1);
				flag2 = pop_s(&pin1, &pout1, empty1, &i);
				time_in2 += t_all - i;
				count2--;
				count_out2++;
			}
		}
		if (toa)
		{
		    tmin = find_min(t1, t2, toa);
		}
		else 
		{
			if (t1 < t2)
				tmin = t1;
			else 
				tmin = t2;
		}

		if (tmin == t1)
		{
			flag1 = add_s(&pin, &pout, full, t_all);
			printf("new 1  %p\n", (void *)pin);
			count1++;
			for (int i = 0; i < N; i++)
			{
			    if (empty[i] == pin)	
				{
					empty[i] = NULL;
				}
			}
			
			count_in1++;
		}
		if (tmin == t2)
		{
			flag2 = add_s(&pin1, &pout1, full1, t_all);
			printf("new 2  %p\n", (void *)pin1);
			count2++;
			count_in2++;
			for (int i = 0; i < N; i++)
			{
			    if (empty1[i] == pin1)	
			    {
				empty1[i] = NULL;
			    }
			}
		}
		
		t1 -= tmin;
		t2 -= tmin;
		toa -= tmin;
		
		if (toa < 0)
		{
			tstop += toa;
			toa = 0; 
		}
		t_all += tmin;
		count_sr1 += count1;
		count_sr2 += count2;
	}
	end_time = tick();
	printf("-------------------------------\n");
	printf("All time of modulation = %lf\n", t_all);
	printf("Wait time = %lf\n", tstop);
	
	printf("in 1 type  = %d\n", count_in1);
	printf("in 2 type  = %d \n", count_in2);
	printf("out 1 type = %d \n", count_out1);
	printf("out 2 type = %d \n", count_out2);
	
	//printf("in_order_sr1 = %lf\n", time_in1 / count_out1);
	//printf("in_order_sr2 = %lf\n", time_in2 / count_out2);
	printf("middle t1 = %lf\n", t1_sr / count_in1);
	printf("middle t2 = %lf\n", t2_sr / count_in2);
	printf("middle t3 = %lf\n", t3_sr / count_out1);
	printf("middle t4 = %lf\n", t4_sr / count_out2);
	
	printf("time in ticks(spisok) = %I64d\n", end_time - begin_time);
	
	for (int i = 0; i < N; i++)
	{
		if (full[i])
			free(full[i]);
	}
	for (int i = 0; i < N; i++)
	{
		if (full1[i])
			free(full1[i]);
	}
	
} 
int main()
{
	int p1[2] = { 1,5 };
	int p2[2] = { 0,3 };
	int p3[2] = { 0,4 };
	int p4[2] = { 0,1 };
	setbuf(stdout, NULL);
	srand(time(NULL));
	char buf[31];
	int action;
	
	info();
	int k = 1;
	while (k)
	{
		menu();
		printf("Input action(number): ");
		if (scanf("%d", &action) == 1)
		{
			printf("\n");
            if (action == 7)
				k = 0;
			else if (action == 3)
			{
				printf("T1 from %d to %d;\n", p1[0], p1[1]);
				printf("T2 from %d to %d;\n", p2[0], p2[1]);
				printf("T3 from %d to %d;\n", p3[0], p3[1]);
				printf("T4 from %d to %d;\n", p4[0], p4[1]);
			}
			else if (action == 4)
			{
				printf("Input T1 from to(int int): ");
				int p[2];
				if (scanf("%d %d", p, p + 1) != 2 && p[0] < p[1])
				{
					printf("input error\n");
					continue;
				}
				p1[0] = p[0];
				p1[1] = p[1];
				
				printf("Input T2 from to(int int): ");
				if (scanf("%d %d", p, p + 1) != 2 && p[0] < p[1])
				{
					printf("input error\n");
					continue;
				}
				p2[0] = p[0];
				p2[1] = p[1];
				
				printf("Input T3 from to(int int): ");
				if (scanf("%d %d", p, p + 1) != 2 && p[0] < p[1])
				{
					printf("input error\n");
					continue;
				}
				p3[0] = p[0];
				p3[1] = p[1];
				
				printf("Input T4 from to(int int): ");
				if (scanf("%d %d", p, p + 1) != 2 && p[0] < p[1])
				{
					printf("input error\n");
					continue;
				}
				p4[0] = p[0];
				p4[1] = p[1];
			}
			else if (action == 5)
			{
				p1[0] = 1;
				p1[1] = 5;
				
				p2[0] = 0;
				p2[1] = 3;
				
				p3[0] = 0;
				p3[1] = 4;
				
				p4[0] = 0;
				p4[1] = 1;
			}
			else if (action == 1)
			{
				process_m(p1,p2,p3,p4);
				printf("Memory on massiv %d \n", sizeof(double)*N);
			}
			else if (action == 2)
			{
				process_s(p1,p2,p3,p4,0);
			}
			else if (action == 6)
			{
				process_s(p1,p2,p3,p4,1);
				//printf("try on little number of elements\n");
				//little_process(p1,p2,p3,p4);
			}
		} 
		else 
		{
			gets(buf);
		    printf("\nInput error\n\n");
		}
	}
	return 0;
}