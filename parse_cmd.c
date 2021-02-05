#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse_cmd.h"
void parse_cmd(char *buf,char param[][15],int * num)
{
	int line_len,param_index = 0;	
		int param_counter = 0;
	line_len= strlen(buf);

	for(int i =0;i < line_len;i++)
	{
		if(buf[i] == ' ')
		{
			param[param_index][param_counter]='\0';
			param_counter = 0;
			param_index	++;
		}
		else
		{
			if(param_counter == 0)
			{
				param[param_index][0] = (char *)malloc(MAX_PARAMETER_LEN*sizeof(char));
			}
			param[param_index][param_counter] = buf[i];
			param_counter++;
		}
	}

	*num = param_index + 1;
	return;
}

