#include"errors.h"
#include"process.h"
#include"io.h"


/**
 * @brief create_struct
 * создает новый элемент
 * @param data [in] данные
 * @return структуру
 */
node_t *create_struct(void *data)
{
	if (!data)
		return NULL;
    node_t *p = malloc(sizeof(node_t));
	if (p)
	{
		p->data = data;
		p->next = NULL;
	}
	return p;
} 

/**
 * @brief add_struct
 * добавляет элемент в список
 * @param head [in] - структура
 * @param pj [in] - элемент
 * @return начала списка
 */
node_t *add_struct(node_t *head, node_t *pj)
{
	if (!pj)
		return NULL;
	if (!head)
		return pj;
	node_t *beg = head;
	while (head->next)
	{
		//printf("%p ", (void *) head->next);
		head = head->next;
	}
	head->next = pj;
	return beg;
}

/**
 * @brief free_list
 * освобождает память
 * @param head [in] структура
 */
void free_list(node_t *head)
{
	node_t *p;
	while (head)
	{
		p = head;
		head = head->next;
		free(p);
	}
}

/**
 * @brief read_data
 * считывает одну запись
 * @param f [in] - файл
 * @param data [out] - данные
 * @return код ошибки
 * Ok - нет ошибок
 * ERR_IO -ошибка ввода
 */
int read_data(FILE *f, struct b *data)
{
	/*if (1 != fscanf(f, "%s", data->name))
	{
		return ERR_IO;
	}
	if (fscanf(f, "%s", data->author) != 1)
	{
		return ERR_IO;
	}*/
	//Возникают Memory errors(unaccessible access) в строке 80
	if (!f || !data || !(data->name) || !(data->author))
		return ERR_IO;
	
	if (!fgets(data->name, N, f))
	{
		return ERR_IO;
	}
	int len = strlen(data->name);
	if (data->name[len - 1] == '\n')
		data->name[len - 1] = '\0';
	if (!fgets(data->author, N, f))
	{
		return ERR_IO;
	}
	len = strlen(data->author);
	if (data->author[len - 1] == '\n')
		data->author[len - 1] = '\0';
	return OK;
}

/**
 * @brief count_n
 * подсчитывает число записей в файле
 * @param f [in] - файл
 * @return количество
 */
int count_n(FILE *f)
{
	int i = 0;
	struct b data;
	while (read_data(f, &data) == OK)
	{
		i++;
	}
	rewind(f);
	return i;
}

/**
 * @brief read_data_from_file
 * считывает данные из файла
 * @param f [in] - файл
 * @param head [out] - начало списка
 * @param d [out] - массив данных
 * @return Ok - нет ошибок
 * ERR_NULL - пустой файл
 * ERR_MEMORY- ошибка памяти
 */
int read_data_from_file(FILE *f, node_t **head, struct b **d)
{
	node_t *new;
	int rc = OK;
    int count = count_n(f);	
	*head = NULL;
	if (!count)
		return ERR_NULL;

	struct b *data = malloc(sizeof(struct b) * count);
	if (!data)
		return ERR_MEMORY;
	
	int i = 0;
    while (i < count && read_data(f, data + i) == OK)
	{
	    new = create_struct(data + i);
		if (new)
		{
	        *head = add_struct(*head, new);
		    i++;
		}
		else 
		{
			free_list(*head);
			rc = ERR_MEMORY;
			break;
		}
	}
	*d = data;
	if (rc)
		free(data);

	return rc;
}

/**
 * @brief print_to_file
 * записывает в файл
 * @param f [in] - начало списка
 * @param head [in] - список
 */
void print_to_file(FILE *f, node_t *head)
{
	node_t *g = head;
	//printf("\n");
	while (g->next)
    {
		fprintf(f, "%s %s \n", ((struct b*)g->data)->name, ((struct b*)g->data)->author);
		g = g->next;
	}
	fprintf(f, "%s %s \n", ((struct b*)g->data)->name, ((struct b*)g->data)->author);
}
