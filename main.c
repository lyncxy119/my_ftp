#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include "parse_cmd.h"
#include "command.h"
int listen_fd,connect_fd;
void signal_handler(int signal_no)
{
	switch(signal_no)
	{
		case SIGINT:
			close(listen_fd);
			close(connect_fd);
			printf("recv int signal\r\n");
		break;
		default:
		break;
	}
	return;
}
int main(int argc,char *argv[])
{
	int port;
	struct sockaddr_in	server_addr;
	char buf[4096];
	signal(SIGINT,signal_handler);	
	listen_fd = socket(AF_INET,SOCK_STREAM,0);
	if(listen_fd == -1)
	{
		printf("create socket error, %s\r\n",strerror(errno));
		exit(0);
	}

	memset((void*)&server_addr,0,sizeof(server_addr));
	server_addr.sin_family		=	AF_INET;
	server_addr.sin_addr.s_addr	=	htonl(INADDR_ANY);
	server_addr.sin_port		=	htons(6666);

	if(bind(listen_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) == -1)
	{
		printf("%s\r\n",strerror(errno));
		exit(0);
	}

	if(listen(listen_fd,10)	== -1)
	{
		printf("listen error:%s\r\n",strerror(errno));
		exit(0);
	}
	printf("waiting for connect...\r\n");
	while(1)
	{
		if((connect_fd = accept(listen_fd,(struct sockaddr*)NULL,NULL)) == -1)
		{
			printf("socket error:%s\r\n",strerror(errno));
			exit(0);
		}
		while(1)
		{
		int size;
		command_t *cmd;
		size = recv(connect_fd,buf,4096,0);
		buf[size] = '\0';
		int param_num;
		char param[15][15] = {{0}};
		parse_cmd(buf,param,&param_num);
		cmd = find_command(param);
		cmd->func(param_num,param,connect_fd);
			if(strncmp(cmd->command_name,"quit",4) == 0)
			{
				break;
			}
		//close(connect_fd);
		}
	
	}
	close(listen_fd);

	
}
