#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

typedef struct
{
	void	(*func)(int argc,char*argv[],int connect_fd);
	char	command_name[20];
	int	max_args_num;	
} command_t;

#define CMD_SECTION	__attribute__	((section(".command")))
#define CMD_INIT(func,name,max_args_num) command_t __cmd_##func CMD_SECTION = {func,#name,max_args_num}

