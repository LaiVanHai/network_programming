#include"my_type.h"
#include"ai.h"
#include"server.h"
#include"database.h"
#include"check_login.h"
#include"check_signup.h"
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define PORT 5500
#define BACKLOG 20

UserType user; // luu thong tin cua user
StatusType status = unauthenticated; // trang thai he thong
PlayStatus play_status = not_play; // trang thai cua game
int data[9][9]; //  du lieu ban co
char *username;
char password[1024]; 
int retry = 0; // dem so lan nhap sai
int listen_sock, conn_sock; /* file descriptors */
char recv_data[1024];
int bytes_sent, bytes_received;
struct sockaddr_in server; /* server's address information */
struct sockaddr_in client; /* client's address information */
pid_t pid;
int sin_size;
FILE *f1;
int color; // luu mau quan co ben phia client
int chess[9][9]; // ban co 

void sig_chld(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("[ForkingServer] Child %d terminated\n",pid);
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
		return Check_User(recv_data, conn_soc, username, &user); 
	}
	if(strcmp(p,"LOGIN_PASS")==0){
		// kiem tra pass co trung khop hay khong
		printf("Login: %s\n", user.username);
		return Check_Login_Pass(recv_data, conn_soc, user, &retry);
	}
	if(strcmp(p,"SIGNUP")==0){
		// chuan bi cho viec tao tai khoan moi
		printf("Dang ki tai khoan\n");
		return Ready_Signup(conn_soc);
	}
	if(strcmp(p,"SIGNUP_USER")==0){
		// kiem tra ten tai khoan dang ky moi
		return Signup_User(recv_data, conn_soc, &user);
	}
	if(strcmp(p,"SIGNUP_PASS")==0){
		//	tao mat khau cho tai khoan dang ki moi
		return Signup_Pass(recv_data, conn_soc, 0, &retry, &user);
	}
	if(strcmp(p,"CONFIRM_PASS")==0){
		// xac nhan lai mat khau dang ki
		printf("Vao confirm roi, pass la:%s\n", username);
		return Signup_Pass(recv_data, conn_soc, 1, &retry, &user);
	}
	if(strcmp(p,"LOGOUT")==0){
		// nguoi dung muon thoat dang nhap
		// suy tinh xem co nen bat nguoi dung truyen user muon thoat khong nhi
		return Check_Logout(recv_data,conn_soc);
	}
	if(strcmp(p,"START_GAME")==0){
		// nhan yeu cau bat dau tro choi cua nguoi dung
		return Start_Game(conn_soc);
	}
	if(strcmp(p,"COLOR")==0){
		// nguoi choi da chon mau quan co, bat dau tro choi
		return Check_Color(recv_data,conn_soc);
	}
	if(strcmp(p,"RUN")==0){
		// nhan nuoc co tu phia client
		return Check_Run(recv_data,conn_soc);
	}
	if(strcmp(p,"END_RUN")==0){
		// nhan duoc thong bao chiu thua tu phia client
		return End_Game(conn_soc);
	}
	if(strcmp(p,"RESULT")==0){
		// nhan duoc thong bao chiu thua tu phia client
		return Send_Result(conn_soc);
	}
	if(strcmp(p,"EXIT")==0){
		// nguoi dung muon huy ket noi voi server
		return Exit_Connect(conn_soc);
	}
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
	int check;
	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	if(p==NULL){
		check = 4; /* truong hop client khong nhap gi*/
	}
	else check = atoi(p); // lua chon cua client gui ve
	switch(check){
		case 1: // lua chon dang nhap
		{
			retry = 0;
			//send("LOGIN");
			printf("READY_LOGIN\n");
			bytes_sent = send(conn_sock,"READY_LOGIN",22,0);
			return Check_Send(bytes_sent);
		}
		case 2: // lua chon dang ki
		{
			retry = 0;
			//send("READY_SIGNUP");
			bytes_sent = send(conn_sock,"READY_SIGNUP",22,0);
			return Check_Send(bytes_sent);
		}
		case 3:
		{
			retry = 0;
			bytes_sent = send(conn_sock,"EXIT_OK",22,0);
			return 0; // lua chon huy ket noi
		}
		default:
		{
			retry++;
			if(retry<5) // cho nhap sai toi da 5 lan
			{
				//send("SELECT_ERROR");
				bytes_sent = send(conn_sock,"SELECT_ERROR",22,0);
				return Check_Send(bytes_sent);
			}
			else
				//send("BLOCK");// huy ket noi
				bytes_sent = send(conn_sock,"BLOCK",22,0);
				return 0; // nhap sai qua nhieu, huy ket noi
		}
	}
}



int Check_Logout(char recv_data[1024], int conn_soc){
	// if(status != authenticated){
	// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
	// 	return 0; 
	// }
	// if(user.online==0){
	// 	// nguoi dung chua dang nhap
	// 	send("LOGOUT_NOT_SUCCESS"); 
	// 	 thong bao nguoi dung chua dang nhap
	// 	va quay lai trang thai nhu khi nhan thong diep HELLO
		
	// 	return 1;
	// }
	// else
	{
		Clear();// xoa tai khoan dang dang nhap
		//send("LOGOUT_SUCCESS");
		bytes_sent = send(conn_sock,"LOGOUT_SUCCESS",22,0);
		return Check_Send(bytes_sent);
		//status = unauthenticated;
		/* thong bao nguoi dung thoat dang nhap thanh cong
 		va quay lai trang thai nhu khi nhan thong diep HELLO
		*/
		//return 0;
	}
}


int Start_Game(int conn_soc){
	// if(status != authenticated || play_status != not_play){
	// 	phai dang nhap moi choi game duoc
	// 	/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
	// 	return 0; 
	// }
	bytes_sent = send(conn_sock,"GAME_READY",22,0);
	return Check_Send(bytes_sent);
	//send("GAME_READY"); 
	//play_status = select_color; /*dua game vao trang thai chon mau*/
	/* nhan duoc thong diep nay client cho nguoi dung chon mau quan co*/
	//return 1;
}


int Check_Color(char str[1024], int conn_soc){
	char *p;
	int number;

	// if(status != authenticated || play_status != select_color){
	// 	phai dang nhap moi choi game duoc
	// 	/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
	// 	return 0; 
	// }

	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	number = atoi(p);
	// if(number == 2){ // 1: trang, 2: den
	// 	//send("COLOR_OK");
	// 	bytes_sent = send(conn_sock,"COLOR_OK",22,0);
	// 	return Check_Send(conn_sock,bytes_sent);
		//play_status = play; /*dat game vao trang thai choi*/
		/*mau trang di truoc*/
		if(number == 2){
			// may se la nguoi danh truoc
			color = 1;
			//send("RUN|6|3|4|3");/*gui ve phia client nuoc co cua server*/
			//return 1;
			bytes_sent = send(conn_sock,"RUN|6|3|4|3|",32,0);
			return Check_Send(bytes_sent);
		}
		if(number == 1){
			// nguoi dung chon quan mau trang
			color = 2;
			//send("COLOR_OK");
			bytes_sent = send(conn_sock,"COLOR_OK",22,0);
			return Check_Send(bytes_sent);
		}
		//return 1;
	// }
	// else
	// {
	// 	//send("COLOR_ERROR");
	// 	bytes_sent = send(conn_sock,"COLOR_ERROR",22,0);
	// 	return Check_Send(conn_sock,bytes_sent);
	// 	//return 1;
	// }
	
}


int Check_Run(char string[1024], int conn_soc){
	char *p;
	int x,x1; // toa do hang
	int y,y1; // toa do cot
	char buff[1024];
	char buff2[1024];
	char str[5];
	//RunType run;


	// if(status != authenticated || play_status != play){
	// 	/*phai dang nhap moi choi game duoc*/
	// 	/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
	// 	return 0; 
	// }

	p = strtok(string,"|");
	p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/ 
	x = atoi(p); 
	p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/ 
	y = atoi(p); 
	p = strtok(NULL,"|");
	x1 = atoi(p); /* lay toa do hang cua nuoc toi*/ 
    p = strtok(NULL,"|");
    y1 = atoi(p); /* lay toa do cot cua nuoc toi*/ 

    if(check_chess_run(chess, color, x1, y1, x , y)>0){ 
    	// check_run _ ai.h
    	//duong di cua phia client la hop le
    	/*
    		AI: tinh toan duong di doi pho
    	*/
    	RunType run = find_way(chess,color); /* ai.h gui vao mang va mau quan co cua phia client*/
    	if(run.status == 0){
    		//send("YOU_WIN"); // client thang
    		bytes_sent = send(conn_sock,"YOU_WIN",32,0);
			return Check_Send(bytes_sent);
    		//play_status = not_play; /*dua game ve trang thai chua bat dau*/
    		/**************************
    		gui file co pho ve phia client
    		***************************/
    	}
    	else
    	{
	    	x = run.x;
	    	sprintf(str, "%d", x);
	    	/*chuyen so thanh xau*/
	    	strcpy(buff,str);
	    	strcat(buff,"|");
	    	y = run.y;
	    	sprintf(str, "%d", y);/*chuyen so thanh xau*/
	    	strcat(buff,str);
	    	strcat(buff,"|");
	    	x1 = run.x1;
	    	sprintf(str, "%d", x1);/*chuyen so thanh xau*/
	    	strcat(buff,str);
	    	strcat(buff,"|");
	    	y1 = run.y1;
	    	sprintf(str, "%d", y1);/*chuyen so thanh xau*/
	    	strcat(buff,str);
	    	strcat(buff,"|");
	    	if(run.status == 1)
	    	{
	    		//send("RUN|chess|x|y"); // neu day la nuoc co binh thuong
	    		strcpy(buff2,"RUN|");
	    		strcat(buff2,buff);
	    		bytes_sent = send(conn_sock,buff2,sizeof(buff2),0);
				return Check_Send(bytes_sent);
	    	}
	    	if(run.status == 2)
	    	{
	    		//send("RUN_W|chess|x|y"); // neu day la nuoc co chieu tuong
	    		strcpy(buff2,"RUN_W|");
	    		strcat(buff2,buff);
	    		bytes_sent = send(conn_sock,buff2,sizeof(buff2),0);
				return Check_Send(bytes_sent);
	    		/*ben client:
	    			1: ban choi tiep
	    			2: ban chiu thua 
	    		*/
	    	}
    	}	
    }
    else
    {
    	/*Neu nuoc co cua client nhap vao bi loi*/
    	//send("RUN_ERROR");
    	bytes_sent = send(conn_sock,"RUN_ERROR",22,0);
		return Check_Send(bytes_sent);
    	//return 1;
    }

}

int End_Game(int conn_soc){
	//send("COMPUTER_WIN");
	bytes_sent = send(conn_sock,"COMPUTER_WIN",22,0);
	return Check_Send(bytes_sent);
	//play_status = not_play; /*dua game ve trang thai chua bat dau*/
	/**************************
	gui file co pho ve phia client
	***************************/
}

int Send_Result(int conn_sock){
	/*Thao tac gui file ve phia client*/
	return 1;
}


int Exit_Connect(int conn_sock){
	bytes_sent = send(conn_sock,"EXIT_OK",22,0);
	return 0; // lua chon huy ket noi
}

void Clear(){
	strcpy(user.username," ");
	strcpy(user.password," ");
	user.online=0;
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
			if (Check_Send(bytes_sent) < 0){
				continue;
			}
			int check_status =1; /*bien kiem soat qua trinh lam viec voi client*/

			do{
				bytes_received = recv(conn_sock,recv_data,1024,0); //blocking
				if (Check_Recv(bytes_received) < 0){
					close(conn_sock);
				}
				else{
					recv_data[bytes_received] = '\0';
					printf("*** From Cllient: %s\n",recv_data);
					if(Check_Mess(recv_data, conn_sock) <= 0){
						close(conn_sock);
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
