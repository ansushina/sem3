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

#define N 30

/*
**Построить ДДП, в вершинах которого находятся слова из текстового файла. 
** Вывести его на экран в виде дерева. 
** Сбалансировать полученное дерево и вывести его на экран. 
** Удалить указанное слово в исходном и сбалансированном дереве.
** Сравнить время удаления и
** объем памяти.
** Построить хеш-таблицу из слов текстового файла,
** задав размерность таблицы с экрана, 
** используя метод цепочек для устранения коллизий.
 
** Вывести построенную таблицу слов на экран. 
** Осуществить удаление введенного слова, 
** вывести таблицу. 
** Сравнить время удаления, 
** объем памяти и
 количество сравнений при использовании ДДП, 
 сбалансированных деревьев, хеш-таблиц и 
 файла. 
*/

// ** слова
// ** вывести
// ** удалить указанное 
// ** время удаления сравнить
// ** сравнить память 
// **хеш таблица
// **размерность с экрана
// **метод цепочек 
// **вывести таблицу 
// ** удалить и вывести 
// ** сравнить время 
// ** количество сравнений 
// ** эффективность поиска 
// реструкторизация? 
// ?? обход дерева 
// ** включение
// ** исключение 
// ** поиск
// зависимость от высоты и степени ветвления 
// ?? изменение хеш-функции? 
// ** Вывод времени и количества
// ** сообщения при ошибках 
// ** добавить узел в пустое дерево 
// ** удаление из пустого дерева 
// ** поиск несуществующего 



void menu()
{
	printf("\nActions:\n");
	printf("1. Print tree \n");
	printf("2. add new word \n");
	printf("3. delete word \n");
	printf("4. find word \n");
	printf("5. Mem difference\n");
	//printf("6.  \n");
	printf("6. exit\n");
}

void info()
{
	printf("This program makes operations with tree\n");
	printf("Elements of tree is words.\n");
	printf("Input file is tree.txt\n");
	printf("Output files out.txt, tree.gv\n");
    printf("\n");
}

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__("rdtsc" : "=A" (d));
	return d;
}

// ......... HESH .................
typedef struct st_t st;
struct st_t
{
	char word[N];
	st *next;
};

st *create_struct(char *word)
{
	if (!word)
		return NULL;
    st *p = malloc(sizeof(st));
	if (p)
	{
		strcpy(p->word, word);
		p->next = NULL;
	}
	return p;
} 

st *add_struct(st *head, char *word)
{
	st *pj = create_struct(word);
	if (!pj)
		return NULL;
	if (!head)
		return pj;
	st *beg = head;
	while (head->next)
	{
		if (strcmp(word, head->word) == 0)
		{
			free(pj);
			return beg;
		}
		//printf("%p ", (void *) head->next);
		head = head->next;
	}
	head->next = pj;
	return beg;
}

void free_list(st *head)
{
	st *p;
	while (head)
	{
		p = head;
		head = head->next;
		free(p);
	}
}

int hesh(char *word, int max)
{
	int n  = 5;
	int h = 0;
	int i = 0;
	while (word[i] != '\0')
	{
		h += ((int)word[i])* pow(n, i);
		i++;
	}
	h %= max;
	return h;
}

void add_to_hesh(st **htable, char *word, int max)
{
	if (!word)
		return;
	int i = hesh(word, max);
	htable[i] = add_struct(htable[i], word);
}

void delete_hesh(st **htable, char *word, int max)
{
	int i = hesh(word, max);
	st *prev = NULL;
	st *k = htable[i];
	while (k && strcmp(word, k->word) != 0 )
	{
		prev = k;
		k = k->next;
	}
	if (k)
	{
		if (!prev)
		{
			htable[i] = k->next;
			free(k);
		}
		else
		{
			prev->next = k->next;
			free(k);
		}
	}
	else 
	{
		printf("AVL: No element\n");
	}
}

void print_hesh(st **htable, int max)
{
	for (int i = 0; i < max; i++)
	{
		st *k = htable[i];
		printf("%4d ", i);
		while(k)
		{
			printf("%s ", k->word);
			k = k->next;
		}
		printf("\n");
	}
}

st *find_el_hesh(st **htable, char *word, int max, int *count)
{
	int i = hesh(word, max);
	st *k = htable[i];
	*count = 1;
	while (k && strcmp(word, k->word) != 0 )
	{
		k = k->next;
		*count += 1;
	}
	return k;
}


void free_hesh(st **htable, int max)
{
	for (int i = 0; i < max; i++)
	{
		st *k = htable[i];
		if(k)
		{

			free_list(k);
		}
	}
	free(htable);
}

int count_kol(st **htable, int max)
{
	int j = 0; 
	int m = 0;
	for (int i = 0; i < max; i++)
	{
		j = 0;
		st *k = htable[i];
		while(k)
		{
			j++;
			k = k->next;
		}
		if (j > m)
			m = j;
	}
	return m;
}

st **restruct(st **htable, int max, int * new)
{
	printf("RESCTRUCT!\n");
	*new = max * 3;
	printf("New number of kol = %d\n", *new);
	st **ntable = calloc(*new, sizeof(st*));
	if (ntable)
	{
		for (int i = 0; i < max; i++)
	    {
		    st *k = htable[i];
		    while(k)
		    {
			    add_to_hesh(ntable, k->word, *new);
    			k = k->next;
	    	}
	    }
	}
	//print_hesh(ntable, *new);
	return ntable;
}


st ** read_from_file_hesh(st **htable, int *max, char *filename, int kol)
{
	char buf[31]; 
	int i;
	
	FILE *f = fopen(filename, "r");
	if (f) 
	{
		while (fscanf(f,"%s", buf) == 1)
		{
		    add_to_hesh(htable, buf, *max);
			i = count_kol(htable, *max);
			if (i >= kol)
			{
				int n;
				st **new = restruct(htable, *max, &n);
				if (new)
				{
					free_hesh(htable, *max);
					htable = new;
					
					*max = n;
					//print_hesh(htable, *max);
				}
			}
			
		}
	}
	fclose(f);
	return htable;
}


// ..................NODE.....................
typedef struct node_t node;
struct node_t // структура для представления узлов дерева
{
	char word[N];
	unsigned char height;
	node* left;
	node* right;
};

node *create_el_node(char *s)
{
	node *p = malloc(sizeof(node));
	if (p)
	{
		strcpy(p->word, s);
		p->left = NULL;
		p->right = NULL;
		p->height = 1;
	}
	return p;
}

unsigned char height(node* p)
{
	return p?p->height:0;
}

int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node * rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if( bfactor(p)== 2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, char* k) // вставка ключа k в дерево с корнем p
{
	if( !p ) return create_el_node(k);
	if (strcmp(k, p->word) == 0)
		return balance(p);
	if( strcmp(k, p->word) < 0 )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left?findmin(p->left):p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* del(node* p, char * k) // удаление ключа k из дерева p
{
	if( !p ) return 0;
	if( strcmp(k, p->word) < 0 )
		p->left = del(p->left,k);
	else if( strcmp(k, p->word) > 0 )
		p->right = del(p->right,k);	
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		free(p);
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void print_n(node *el, node *parent, FILE *f)
{
	if (el)
	{
		if (parent)
		{
			fprintf(f,"%s->%s\n", parent->word, el->word);
		}
		print_n(el->left, el, f);
		print_n(el->right, el, f);
	}
}

void print_tree_node(node *head)
{
	FILE *graph = fopen("node.gv", "w");

    fprintf(graph, "digraph N{\n");

	if (head && !(head->left) && !(head->right))
	{
		fprintf(graph,"%s\n", head->word);
	}
	print_n(head, NULL, graph);
    fprintf(graph, "}");

    fclose(graph);
}

node *find_el_node(node *head, char *word, int *count)
{
	if (!head)
		return 0; 
	node *p = head;
	*count = 1;
	while(strcmp(p->word, word) != 0)
	{
		if (strcmp(word, p->word) < 0)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
		if (!p)
		{
			return NULL;
		}
		*count += 1;
	}
	return p; 
}

node *read_from_file_node(char *filename)
{
	char buf[31]; 
	node *head = NULL;
	
	FILE *f = fopen(filename, "r");
	if (f) 
	{
		while (fscanf(f,"%s", buf) == 1)
		{
		    head = insert(head, buf);
		}
	}
	fclose(f);
	return head;
}

void free_n(node *head)
{
	if (head)
	{
	    free_n(head->left);
    	free_n(head->right);
	    free(head);
	}
}
// ....... TREE...........................

typedef struct tree_element t_el;

struct tree_element
{
	char word[N];
	t_el *left;
	t_el *right;
};

t_el *create_el(char *s)
{
	t_el *p = malloc(sizeof(t_el));
	if (p)
	{
		strcpy(p->word, s);
		p->left = NULL;
		p->right = NULL;
	}
	return p;
}

t_el *add_el(t_el *head, t_el *el)
{
	if (!head)
		return el;
	t_el *p = head;
	while(p)
	{
		if (strcmp(el->word, p->word) == 0)
		{
			break;
		}
		if (strcmp(el->word, p->word) < 0)
		{
			if (!(p->left))
			{
				p->left = el;
				break;
			}
			else
			{
			    p = p->left;
			}
		}
		else
		{
			if (!(p->right))
			{
				p->right = el;
				break;
			}
			else 
			{
				p = p->right;
			}
		}
	}
	return head;
}

t_el *delete_el(t_el *head, char *word)
{
	if (!head || !word)
		return NULL;
	if (!(head->left) && !(head->right))
	{
		if (strcmp(head->word, word) == 0)
		{
		    free(head);
		    return NULL;
		}
		else 
			return NULL;
	}
	t_el *p = head;
	t_el *prev = NULL;
	int lflag = 0;
	
	if (strcmp(head->word, word) == 0 && !(p->left))
	{
		head = p->right;
		free(p);
		return head;
	}	
	if (strcmp(head->word, word) == 0 && !(p->right))
	{
		head = p->left;
		free(p);
		return head;
	}	
	
	while(strcmp(p->word, word) != 0)
	{
		if (strcmp(word, p->word) < 0)
		{
			prev = p;
			lflag = 1;
			p = p->left;
		}
		else
		{
			prev = p;
			lflag = 0;
			p = p->right;
		}
		if (!p)
		{
			printf("NO THIS ELEMENT IN TREE\n");
			return head;
		}
	}
	
	
	if (!(p->left) && !(p->right))
	{
		if(lflag == 0)
		{
			prev->right = NULL;
		}
		else 
		{
			prev->left = NULL;
		}
		free(p);
	}
	else if (!(p->left))
	{
		if(lflag == 0)
		{
			prev->right = p->right;
		}
		else 
		{
			prev->left = p->right;
		}
		free(p);
	}
	else if (!(p->right))
	{
		if(lflag == 0)
		{
			prev->right = p->left;
		}
		else 
		{
			prev->left = p->left;
		}
		free(p);
	}
    else if (!(p->right->left))
	{
		t_el *r = p->right;
		strcpy(p->word, p->right->word);
		p->right = r->right;
		free(r);
	}
	else
	{
		t_el *l = p->right;
		t_el *lprev = p; 
		while(l->left)
		{
			lprev = l;
			l = l->left; 
		}
		
		strcpy(p->word, l->word);
		
		if (!(l->right))
		{
			lprev->left = NULL;
		}
		else
		{
			lprev->left = l->right;
		}
		free(l);
	}
	return head; 
}

t_el *delete(t_el *head)
{
	char buf[31];
	printf("Input word: ");
	if (scanf("%31s", buf) == 1)
	{
		head = delete_el(head, buf);
	}
	else
	{
		printf("INPUT ERROR\n");
	}
	return head; 
}

t_el *read_from_file(char *filename)
{
	char buf[31]; 
	t_el *new;
	t_el *head = NULL;
	
	FILE *f = fopen(filename, "r");
	if (f) 
	{
		while (fscanf(f,"%s", buf) == 1)
		{
			new = create_el(buf);
		    head = add_el(head, new);
		}
	}
	fclose(f);
	return head;
}

t_el *add(t_el *head)
{
	char buf[31];
	printf("\nInput word: ");
	if (scanf("%31s", buf) == 1)
	{
		t_el *new = create_el(buf);
		head = add_el(head, new);
	}
	else
	{
		printf("INPUT ERROR\n");
	}
	return head; 
}

void print_t(t_el *el, t_el *parent, FILE *f)
{
	if (el)
	{
		if (parent)
		{
			fprintf(f,"%s->%s\n", parent->word, el->word);
		}
		print_t(el->left, el, f);
		print_t(el->right, el, f);
	}
}

void print_tree(t_el *head)
{
	FILE *graph = fopen("tree.gv", "w");

    fprintf(graph, "digraph TREE{\n");

	if (head && !(head->left) && !(head->right))
	{
		fprintf(graph,"%s\n", head->word);
	}
	print_t(head, NULL, graph);
    fprintf(graph, "}");

    fclose(graph);
}

t_el *find_el(t_el *head, char *word, int *count)
{
	if (!head)
		return 0; 
	t_el *p = head;
	*count = 1;
	while(strcmp(p->word, word) != 0)
	{
		if (strcmp(word, p->word) < 0)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
		if (!p)
		{
			return NULL;
		}
		*count += 1;
	}
	return p; 
}

void free_t(t_el *head)
{
	if (head)
	{
	    free_t(head->left);
	    free_t(head->right);
	    free(head);
	}
}
// ****ALL*************

int find_file(char *fname, char *word)
{
	FILE *f = fopen(fname, "r");
	char buf[N];
	int count = 0;
	if (f)
	{
		int g = fscanf(f, "%s", buf);
		while (g && strcmp(buf, word) != 0)
		{
			g = fscanf(f, "%s", buf);
			count++;
		}
		
		
		fclose(f);
		if (strcmp(buf, word) == 0)
		{
			fclose(f);
			return count;
		}
		else
		{
			fclose(f);
			return 0;
		}
	}
	else 
	{
		fclose(f);
		return 0;
	}
}

void dif_find(t_el *head, node *head_node, st **htable, int max)
{
	int c1 = 0, c2 = 0, c3 = 0,c4 = 0;
	int n = 0;
	for (int i = 0; i < max; i++)
	{
		st *k = htable[i];
		while(k)
		{
			int count1 = 0, count2 = 0, count3 = 0;
			t_el *el = find_el(head, k->word, &count1);
			node *el_n = find_el_node(head_node, k->word, &count2);
			st *el_h = find_el_hesh(htable,k->word,max, &count3);
			c4 += find_file("tree.txt", k->word);
			k = k->next;
			n++;
			c1 += count1;
			c2 += count2;
			c3 += count3;
			
		}
	}
	printf("SR TREE: %f \n", (float)c1/n);
	printf("SR AVL: %f \n", (float)c2/n);
	printf("SR HASH: %f\n", (float)c3/n);
	printf("SR FILE: %f\n", (float)c4/n);
	
	/*for (int i = 0; i < max; i++)
	{
		st *k = htable[i];
		while(k)
		{
			tb = tick();
		    head = delete_el(head, buf);
			te = tick();
			t1 = te-tb;
			// node
		    tb = tick();
			head_node = del(head_node, buf);
			te = tick();
			t2 = te-tb;
			// hesh
			tb = tick();
			delete_hesh(htable, buf, max);
			te = tick();
			t3 = te-tb; 
		}
	}*/
}



#define APP "mspaint.exe"
#define DOT "C:\\Graphviz2.38\\bin\\dot.exe"
#define ME "C:\\c_prog\\TiSD\\6"

int main()
{
	setbuf(stdout, NULL);
	srand(time(NULL));
	char buf[31];
	long int tb, te;
	long int t1, t2, t3;
	int action, rc;
	t_el *head = NULL;
	node *head_node = NULL;
	int max  = 25;
	int kol = 0;
	info();
	
	printf("Input number of hesh table: ");
	if (scanf("%d", &max) != 1 || max <= 0)
	{
		printf("Input error!\n ");
		return 0;
	}
	printf("Input number of kollisii: ");
	if (scanf("%d", &kol) != 1 || kol <= 0)
	{
		printf("Input error!\n ");
		return 0;
	}
	
	st **htable = calloc(max, sizeof(st*));
	
	head = read_from_file("tree.txt");
	head_node = read_from_file_node("tree.txt");
	htable = read_from_file_hesh(htable, &max, "tree.txt", kol);
	
	/*system(DOT " -Tpng " ME "\\tree.gv -o" ME "\\tree.png");
    system("start " APP " " ME "\\tree.png");
	system(DOT " -Tpng " ME "\\node.gv -o" ME "\\AVL.png");
    system("start " APP " " ME "\\AVL.png");*/
	
	//print_hesh(htable, max);
	
	int k = 1;
	while (k)
	{
		menu();
		printf("Input action(number): ");
		if (scanf("%d", &action) == 1)
		{
            if (action == 6)
				k = 0;
			else if (action == 2)
			{
	            printf("\nInput word: ");
	            if (scanf("%31s", buf) == 1)
	            {
					// tree
		            t_el *new = create_el(buf);
		            head = add_el(head, new);
					//node
					head_node = insert(head_node, buf);
					
					//hesh
					add_to_hesh(htable, buf, max);
					int j = count_kol(htable, max);
			        if (j >= kol)
			        {
			        	int n;
				        st **new = restruct(htable, max, &n);
				        if (new)
				        {
				        	htable = new;
					        free_hesh(htable, max);
							max = n;
				        } 
			        }
	            }
	            else
	            {
		        printf("INPUT ERROR\n");
	            }
			}
			else if (action == 3)
			{
               	printf("Input word: ");
	            if (scanf("%31s", buf) == 1)
	            {
					// tree
				    tb = tick();
		            head = delete_el(head, buf);
					te = tick();
					t1 = te-tb;
					// node
					tb = tick();
					head_node = del(head_node, buf);
					te = tick();
					t2 = te-tb;
					// hesh
					tb = tick();
					delete_hesh(htable, buf, max);
					te = tick();
					t3 = te-tb; 
					printf("\ntime TREE: %d \n", t1);
	                printf("time AVL: %d \n", t2);
	                printf("time HeSH: %d\n", t3);
	            }
		        else
	            {
		            printf("INPUT ERROR\n");
	            } 
				
			}
			else if (action == 1)
			{
				// tree
				if (head)
				{
				    print_tree(head);
				    system(DOT " -Tpng " ME "\\tree.gv -o" ME "\\tree.png");
                    system("start " APP " " ME "\\tree.png");
				}
				else
				{
					printf("EMPTY\n");
				}
				// node
				if (head_node)
				{
				    print_tree_node(head_node);
					system(DOT " -Tpng " ME "\\node.gv -o" ME "\\AVL.png");
                    system("start " APP " " ME "\\AVL.png");
				}
				// hesh
				print_hesh(htable, max);
			}
			else if (action == 4)
			{
				printf("\nInput word: ");
	            if (scanf("%31s", buf) == 1)
	            {
				    // tree
					int count1 = 0, count2 = 0, count3 = 0;
				    t_el *el = find_el(head, buf, &count1);
		            if (el)
		            {
		            	printf("YES! Element in tree!\n");
			            printf("TREE: %p \n", (void *)el);
					}
				    // node 
					node *el_n = find_el_node(head_node, buf, &count2);
					if (el_n)
					{
						 printf("AVL: %p \n", (void *)el_n);
					}
					// hesh
					st *el_h = find_el_hesh(htable,buf,max, &count3);
					if (el_h)
					{
						 printf("HESH: %p \n", (void *)el_h);
					}
					int count4 = find_file("tree.txt", buf);
					printf("\n TREE: %d \n", count1);
	                printf(" AVL: %d \n", count2);
	                printf(" HeSH: %d\n", count3);
					printf(" File: %d\n", count4);
					//dif_find(head, head_node, htable, max);
				}
	            else
	            {
		        printf("INPUT ERROR\n");
	            }
			}
			else if (action == 5)
			{
				printf("Memory difference\n");
				
				int count = 0;
				for (int i = 0; i < max; i++)
				{
					st *k = htable[i];
					while(k)
					{
						count++;
						k = k->next;
					}
				}
				printf("\nTree mem = %d \n", count * sizeof(t_el));
				printf("AVL mem = %d \n", count * sizeof(node));
				printf("hash mem = %d \n", count *sizeof(st)+ sizeof(htable));
				
				printf("Srednee kolvo sravnenii: \n");
				dif_find(head, head_node, htable, max);
				
			}
		}
		else 
		{
			gets(buf);
		    printf("\nInput error\n\n");
		}
	}
	
	free_t(head);
	free_n(head_node);
	free_hesh(htable, max);
	return 0;
}