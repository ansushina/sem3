#include"z.h"

void change_spaces(char *str)
{
	if (str == NULL)
		return;
	
	int i = 0;
	int j = 0;
	while (str[i] == ' ')
	{
		i++;
	}
	while (str[i] != '\0')
	{
		while (str[i] != ' ' && str[i] != '\0')
		{
			str[j] = str[i];
			j++;
			i++;
		}
		if (str[i] != '\0')
		{
			str[j] = str[i];
		    j++;
		    i++;
		}
		while (str[i] == ' ')
		{
			i++;
		}
	}
	if (str[j - 1] == ' ')
	    str[j - 1] = '\0';
	else 
		str[j] = '\0';
}