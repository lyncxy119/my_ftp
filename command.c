#include "command.h"
#include "stdio.h"

extern command_t	__cmd_start,__cmd_end;
void do_hello(int argc,char argv[][15],int connect_fd)
{
	printf("hello world\r\n");
	send(connect_fd,"hello world\r\n",strlen("hello world\r\n"),0);
	
	return;
}
CMD_INIT(do_hello,hello,1);

void do_quit(int argc,char argv[][15],int connect_fd)
{
	printf("quit my_ftp now\r\n");
	send(connect_fd,"quit my_ftp now\r\n",strlen("quit my_ftp now\r\n"),0);
	sleep(2);
	close(connect_fd);
	return;
}
CMD_INIT(do_quit,quit,1);
command_t * find_command(char argv[][15])
{
	command_t *command_ptr;
	command_t *command_temp;
	command_temp = &__cmd_start;	
	int len; 
	printf("%s\r\n",argv[0]);
	len = strlen(argv[0]);	
	
	printf("cmd len %d\r\n",len);
	for(command_ptr = &__cmd_start; command_ptr < &__cmd_end; command_ptr++)
	{
		printf("compare command name :%s %s\r\n",command_ptr->command_name,argv[0]);
		if(strncmp(command_ptr->command_name,argv[0],len) == 0)
		{
			printf("command match\r\n");
			command_temp = command_ptr;
			return command_temp;	
		}
	}
	printf("cmd not found\r\n");
	return command_temp;
}

