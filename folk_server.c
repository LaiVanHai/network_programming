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
StatusType status = unauthenticated; // trang thai he thong
PlayStatus play_status = not_play; // trang thai cua game
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
FILE *f1;

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

char* encode(char* str) {
   int i = 0;
 
   while (str[i] != '\0') {
      str[i] = str[i] - 30;  // Subtract 30 From Charcter
      i++;
   }
   return (str);
}

char* decode(char* str) {
   int i = 0;
 
   while (str[i] != '\0') {
      str[i] = str[i] + 30;  // Subtract 30 From Charcter
      i++;
   }
   return (str);
}

void Clear(){
	strcpy(user.username," ");
	strcpy(user.password," ");
	user.online=0;
}

int Find_User(char s1[1024])
{
	// TIM KIEM USER TRONG DATABASE
	// Cap nhat mat khau va tai khoan  vao trong bien user
	// password luu lai trong bien nay la password da duoc giai ma
	char s[80];
	char username1[80];
	char *p; 
	if((f1=fopen("password.txt","r+"))==NULL)
    {
      printf("File server error!!\n");
      return 0;
    }
	while(fgets(s,80,f1)!=NULL)
	{
		p=strtok(s,"\t"); //user va pass phan cach boi dau tab
		strcpy(username1,p);
		if(strcmp(s1,username1)==0)
		{
			strcpy(user.username, s1); /*luu lai ten dang nhap cua nguoi dung*/
			p=strtok(NULL,"\n");
			strcpy(user.password,decode(p)); // tim kiem lai mat khau
			return 1;
		}
	}
	fclose(f1);
	return 0;
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
	if(strcmp(p,"LOGIN_USER")==0){
		// tim user trong he thong
		return Check_User(recv_data, conn_soc); 
	}
	if(strcmp(p,"LOGIN_PASS")==0){
		// kiem tra pass co trung khop hay khong
		return Check_Login_Pass(recv_data,conn_soc);
	}
	if(strcmp(p,"SIGNUP")==0){
		// chuan bi cho viec tao tai khoan moi
		printf("Dang ki tai khoan\n");
		return Ready_Signup(conn_soc);
	}
	if(strcmp(p,"SIGNUP_USER")==0){
		// kiem tra ten tai khoan dang ky moi
		return Signup_User(recv_data, conn_soc);
	}
	if(strcmp(p,"SIGNUP_PASS")==0){
		//	tao mat khau cho tai khoan dang ki moi
		return Signup_Pass(recv_data, conn_soc,0);
	}
	if(strcmp(p,"CONFIRM_PASS")==0){
		// xac nhan lai mat khau dang ki
		return Signup_Pass(recv_data,conn_soc,1);
	}
}

int Signup_Pass(char str[1024], int conn_soc, int confirm){
	char *p;
	char confirm_password[1024];

	// if(status != enter_password|| status != confirm_pass){
	// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
	// 	return 0; 
	// }

	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	if(confirm==0)// mat khau moi nhap lan dau
	{
		if(strlen(p)<6){
			if(retry<5){
				retry++;
				//send("PASS_SHORT");/*mat khau client nhap vao qua ngan*/
				//return 1;
				bytes_sent = send(conn_sock,"PASS_SHORT",22,0);
				return Check_Send(conn_sock,bytes_sent);
			}else
			{
				Clear();
				//send("BLOCK"); // nhap sai qua nhieu lan
				bytes_sent = send(conn_sock,"BLOCK",22,0);
				return 0; 
			}
		}
		else
		{
			retry = 0;
			//send("CONFIRM_PASS"); /*gui yeu cau nhap mat khau xac thuc*/
			strcpy(password,p);
			//status = confirm_pass; /*dat he thong ve trang thai xac thuc mat khau*/
			//return 1;
			bytes_sent = send(conn_sock,"CONFIRM_PASS",22,0);
			return Check_Send(conn_sock,bytes_sent);
		}
	}
	else
	{
		// if(status != confirm_pass){
		// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
		// 	return 0; 
		// }
		// day la mat khau confirm
		strcpy(confirm_password,p);
		if(strcmp(password,confirm_password)==0){
			retry = 0;
			//send("SIGNUP_USER_SUCCESS");/*thong bao cho ben client biet la da tao thanh cong tai khoan*/
			/*Client: goi lai menu giong luc moi dang nhap vao*/
			//status = unauthenticated; /*dua he thong ve trang thai ban dau*/
			//return 1;
			Update_Database(username,encode(password));
			bytes_sent = send(conn_sock,"SIGNUP_USER_SUCCESS",22,0);
			return Check_Send(conn_sock,bytes_sent);
		}	
		else{
			if(retry<5){
				retry++;
				// send("CONFIRM_NOT_MATCH"); gui yeu cau ben client nhap lai mat khau xac nhan
				// return 1;
				bytes_sent = send(conn_sock,"CONFIRM_NOT_MATCH",22,0);
				return Check_Send(conn_sock,bytes_sent);
			}else
			{
				retry = 0;
				Clear();
				//send("BLOCK"); // nhap sai qua nhieu lan
				bytes_sent = send(conn_sock,"BLOCK",22,0);
				return 0; 
			}
		}
	}
}
	


void Update_Database(char user[1024],char pass[1024]){
	f1=fopen("password.txt","a+");
	fputs(user,f1);
	fputs("\t",f1);
	fputs(pass,f1);
	fputs("\n",f1);
	fclose(f1);
}

int Select_Work(char str[1024], int conn_soc){  /*tuy chon ban dau giua client va server*/
	// co 2 tuy chon
	// 1: dang nhap
	// 2: tao tai khoan moi
	// 3: huy ket noi
	// if(status != unauthenticated){
	// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
	// 	return 0; 
	// }
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

int Check_User(char str[1024], int conn_soc){ // kiem tra khi client gui ve username
	char *p;

	// if(status != unauthenticated){
	// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
	// 	return 0; 
	// }
	printf("Check_User 1|%s\n",str);
	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	strcpy(username,p);
	if(Find_User(username)==1)
	{
		//send("LOGIN_USER_ID_OK");
		status = specified_id;/*chuyen qua trang thai xac nhan password */
		bytes_sent = send(conn_sock,"LOGIN_USER_ID_OK",22,0);
		return Check_Send(conn_sock,bytes_sent);
	}
	else
	{
		//send("LOGIN_USER_NOT_EXIST");
		bytes_sent = send(conn_sock,"LOGIN_USER_NOT_EXIST",22,0);
		return Check_Send(conn_sock,bytes_sent);
		/*
			Client se dua ra 3 lua chon
			- 1 tiep tuc dang nhap lai
			- 2 tao tai khoan moi
			- 3 thoat
		*/
	}
	
}

int Check_Login_Pass(char str[1024], int conn_soc){
	char *p;
	char password[1024];

	// if(status != specified_id){
	// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
	// 	return 0; 
	// }

	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan password ma client gui ve
	strcpy(password,p); // luu lai pass dang ki cua nguoi dung
	if(strcmp(password,user.password)==0)
	{
		retry=0;
		strcpy(user.username,username);
		strcmp(user.password,password);
		user.online=1;/*dat trang thai user thanh online*/
		status = authenticated; /*dua he thong ve trang thai da dang nhap*/
		//send("LOGIN_SUCCESS");
		bytes_sent = send(conn_sock,"LOGIN_SUCCESS",22,0);
		return Check_Send(conn_sock,bytes_sent);
	}
	else{
		retry++;
		if(retry<5) // cho nhap sai toi da 5 lan
			{
				//send("PASS_NOT_MATCH");
				bytes_sent = send(conn_sock,"PASS_NOT_MATCH",22,0);
				return Check_Send(conn_sock,bytes_sent);
			}
			else
			{
				Clear();
				//send("BLOCK");// huy ket noi
				bytes_sent = send(conn_sock,"BLOCK",22,0);
				return 0; // nhap sai qua nhieu, huy ket noi
			}
	}
}

int Ready_Signup(int conn_soc){

	//if(status == unauthenticated){
		/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
		// Chuan bi cho cong viec dang ki tai khoan moi
		// Dua bien luu user hien tai ve trang thai rong
		status = signup; /* cap nhat lai trang thai dang ki */
		//send("READY_SIGNUP");
		bytes_sent = send(conn_sock,"READY_SIGNUP",22,0);
		return Check_Send(conn_sock,bytes_sent); 
	//}
	//return 0;
}
	

int Signup_User(char str[1024], int conn_soc){
	char *p;

	//if(status == signup){
		printf("Username 1:%s\n",str);
		/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
		p = strtok(str,"|");
		p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
		strcpy(username,p);
		printf("Username:%s\n",username);
		if(Find_User(username)==1)
		{
			//send("USER_ID_EXISTED");
			bytes_sent = send(conn_sock,"USER_ID_EXISTED",22,0);
			return Check_Send(conn_sock,bytes_sent);
		}
		else
		{
			//send("SIGNUP_USER_ID_OK");
			status = signup_pass; /*chuuyen qua trang thai nhap password de dang ki*/
			bytes_sent = send(conn_sock,"SIGNUP_USER_ID_OK",22,0);
			return Check_Send(conn_sock,bytes_sent);
		}

	//}
	//return 0; 
	
}

int main(){

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
					printf("*** From Cllient: %s\n",recv_data);
					if(Check_Mess(recv_data, conn_sock) == 0){
						check_status=0;
					}
				}
			}while(check_status>0);
			
			exit(0);
		}
		
		status = unauthenticated;
		play_status = not_play;

		signal(SIGCHLD,sig_chld);
		
		close(conn_sock);
	}
	close(listen_sock);
	return 1;
}
