#include"my_type.h"
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#define PORT 5500
#define BACKLOG 20

UserType user; // luu thong tin cua user
StatusType status; // trang thai he thong
PlayStatus play_status; // trang thai cua game
int data[9][9]; //  du lieu ban co
char username[1024];
char password[1024]; 
int retry=0; // dem so lan nhap sai
int listen_sock, conn_sock; /* file descriptors */
char recv_data[1024];
int bytes_sent, bytes_received;
struct sockaddr_in server; /* server's address information */
struct sockaddr_in client; /* client's address information */
pid_t pid;
int sin_size;

void sig_chld(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("[ForkingServer] Child %d terminated\n",pid);
}

int Check_Send(int conn_soc, int bytes_sent){
	if(bytes_sent<0)
	{
		printf("\nError!Can not sent data to client!");
		close(conn_soc);
		return -1;
	}
	return 1;
}

int Check_Recv(int conn_soc, int bytes_recv){
	if(bytes_recv<0)
	{
		printf("\nError!Can not receive data from client!");
		close(conn_soc);
		return -1;
	}
	return 1;
}

int Check_Mess(char recv_data[1024], int conn_soc){
	char *p;
	char str[1024];
	strcpy(str,recv_data);
	p = strtok(str,"|");
	if(strcmp(p,"SELECT_WORK")==0){
		// lua chon cong viec khi moi vao
		return(Select_Work(recv_data, conn_soc));
	}
}

int Select_Work(char str[1024], int conn_soc){  /*tuy chon ban dau giua client va server*/
	// co 2 tuy chon
	// 1: dang nhap
	// 2: tao tai khoan moi
	// 3: huy ket noi
	if(status != unauthenticated){
		/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
		return 0; 
	}
	char *p;
	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	int check = atoi(p); // lua chon cua client gui ve
	switch(check){
		case 1: // lua chon dang nhap
		{
			retry = 0;
			//send("LOGIN");
			printf("READY_LOGIN\n");
			bytes_sent = send(conn_sock,"READY_LOGIN",22,0);
			return Check_Send(conn_sock,bytes_sent);
		}
		case 2: // lua chon dang ki
		{
			retry = 0;
			//send("READY_SIGNUP");
			bytes_sent = send(conn_sock,"READY_SIGNUP",22,0);
			return Check_Send(conn_sock,bytes_sent);
		}
		case 3:
		{
			retry = 0;
			bytes_sent = send(conn_sock,"BLOCK",22,0);
			return 0; // lua chon huy ket noi
		}
		default:
		{
			retry++;
			if(retry<5) // cho nhap sai toi da 5 lan
			{
				//send("SELECT_ERROR");
				bytes_sent = send(conn_sock,"SELECT_ERROR",22,0);
				return Check_Send(conn_sock,bytes_sent);
			}
			else
				//send("BLOCK");// huy ket noi
				bytes_sent = send(conn_sock,"BLOCK",22,0);
				return 0; // nhap sai qua nhieu, huy ket noi
		}
	}

}

int main(){
	status = unauthenticated;
	play_status = not_play;

	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		exit(-1);
	}
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   

	if(bind(listen_sock,(struct sockaddr*)&server,sizeof(server))==-1){ /* calls bind() */
		printf("bind() error\n");
		exit(-1);
	}     

	if(listen(listen_sock,BACKLOG) == -1){  /* calls listen() */
		printf("listen() error\n");
		exit(-1);
	}

	while(1){
		sin_size=sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock,(struct sockaddr *)&client,&sin_size))==-1){ /* calls accept() */
			printf("accept() error\n");
			exit(-1);
		}
  
		if((pid=fork())==0){
			close(listen_sock);
			printf("You got a connection from %s\n",inet_ntoa(client.sin_addr) ); /* prints client's IP */
			bytes_sent = send(conn_sock,"HELLO",22,0); /* send to the client welcome message */
			if (Check_Send(conn_sock,bytes_sent) < 0){
				continue;
			}
			int check_status =1; /*bien kiem soat qua trinh lam viec voi client*/

			do{
				bytes_received = recv(conn_sock,recv_data,1024,0); //blocking
				if (Check_Recv(conn_sock,bytes_received) < 0){
					close(conn_sock);
				}
				else{
					recv_data[bytes_received] = '\0';
					//printf("%s\n",recv_data);
					if(Check_Mess(recv_data, conn_sock) == 0){
						check_status=0;
					}
				}
			}while(check_status>0);
			
			exit(0);
		}
		
		signal(SIGCHLD,sig_chld);
		
		close(conn_sock);
	}
	close(listen_sock);
	return 1;
}
