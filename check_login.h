#ifndef __CHECK_LOGIN__
#define __CHECK_LOGIN__
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include"check_send_recv.h"
int bytes_sent;

int Check_User(char str[1024], int conn_sock, char *username, UserType *user){ // kiem tra khi client gui ve username
	char *p;
	UserType user1;

	// if(status != unauthenticated){
	// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
	// 	return 0; 
	// }
	printf("Check_User 1|%s\n",str);
	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	//printf("User: %s\n",p);
	username=p;
	if(Find_User(username,&user1)==1)
	{
		username = p;
		*user=user1;
		//send("LOGIN_USER_ID_OK");
		//status = specified_id;/*chuyen qua trang thai xac nhan password */
		bytes_sent = send(conn_sock,"LOGIN_USER_ID_OK",22,0);
		return Check_Send(bytes_sent);
	}
	else
	{
		//send("LOGIN_USER_NOT_EXIST");
		bytes_sent = send(conn_sock,"LOGIN_USER_NOT_EXIST",22,0);
		return Check_Send(bytes_sent);
		/*
			Client se dua ra 3 lua chon
			- 1 tiep tuc dang nhap lai
			- 2 tao tai khoan moi
			- 3 thoat
		*/
	}
	
}

int Check_Login_Pass(char str[1024], int conn_sock, UserType user, int *retry){
	char *p;
	char password[1024];

	// if(status != specified_id){
	// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
	// 	return 0; 
	// }

	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan password ma client gui ve
	strcpy(password,p); // luu lai pass gui len cua nguoi dung
	if(strcmp(password,user.password)==0)
	{
		retry=0;
		//strcpy(user.username,username);
		strcmp(user.password,password);
		user.online=1;/*dat trang thai user thanh online*/
		//status = authenticated; /*dua he thong ve trang thai da dang nhap*/
		//send("LOGIN_SUCCESS");
		bytes_sent = send(conn_sock,"LOGIN_SUCCESS",22,0);
		return Check_Send(bytes_sent);
	}
	else{
		*retry++;
		if(*retry<5) // cho nhap sai toi da 5 lan
			{
				//send("PASS_NOT_MATCH");
				bytes_sent = send(conn_sock,"PASS_NOT_MATCH",22,0);
				return Check_Send(bytes_sent);
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

#endif