#ifndef __CHECK_SEND_RECV__
#define __CHECK_SEND_RECV__
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <stdlib.h>

int Check_Send(int bytes_sent){
	if(bytes_sent<0)
	{
		printf("\nError!Can not sent data to client!");
		return -1;
	}
	return 1;
}

int Check_Recv(int bytes_recv){
	if(bytes_recv<0)
	{																																																				
		printf("\nError!Can not receive data from client!");
		return -1;
	}
	return 1;	
}

#endif