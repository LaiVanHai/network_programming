#ifndef __CHECK_GAME__
#define __CHECK_GAME__

#include "time_machine.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "my_type.h"
#include <string.h>
#include <stdio.h>

int Check_Color(char str[1024], int conn_sock, int **chess, int *color, char **server_run);/*Kiem tra su hop le ve mau quan co*/
int Check_Run(char string[1024], int conn_sock, int **chess, int color, char **server_run, char **client_run, int *flag);/*Kiem tra duong di quan co*/


int Check_Color(char str[1024], int conn_sock, int **chess, int *color, char **server_run){
	char *p;
	int number;
	FILE *f1;
	char buff2[80] = "";
	char buff[80] = "";
	int x, y, x1, y1;
	// if(status != authenticated || play_status != select_color){
	// 	phai dang nhap moi choi game duoc
	// 	/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
	// 	return 0; 
	// }
	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	number = atoi(p);
	printf("Vao duoc check color.\n");
	// if(number == 2){ // 1: trang, 2: den
		/*mau trang di truoc*/
		if(number == 2){
			// may se la nguoi danh truoc
			*color = 2;
			int **chess2 = chess;
	    	RunType run = find_way(chess2, *color); /* ai.h gui vao mang va mau quan co cua phia client*/
			printf("xong find way.\n");
			x = run.x;
	    	sprintf(str, "%d", x);
	    	/*chuyen so thanh xau*/
	    	strcpy(buff,str);
	    	strcat(buff,"|");

	    	printf("x\n");

	    	y = run.y;
	    	sprintf(str, "%d", y);/*chuyen so thanh xau*/
	    	printf("3\n");
	    	strcat(buff,str);
	    	printf("2\n");
	    	strcat(buff,"| -> |");
	    	printf("1\n");
	    	printf("%s\n",buff);
	    	printf("0\n");

	    	x1 = run.x1;
	    	printf("y\n");
	    	sprintf(str, "%d", x1);/*chuyen so thanh xau*/
	    	printf("y1.\n");
	    	strcat(buff,str);
	    	printf("linh dan\n");
	    	strcat(buff,"abc");
	    	strcat(buff,"|");
	    	printf("x1");

	    	y1 = run.y1;
	    	sprintf(str, "%d", y1);/*chuyen so thanh xau*/
	    	strcat(buff,str);
	    	strcat(buff,"|");

	    	strcpy(*server_run,buff);
	    	printf("y1\n");

	    	chess[x1][y1] = chess[x][y];
    		chess[x][y]= '_';

    		printf("Xong cap nhat nuoc co.\n");
			/*cap nhat lai nuoc co*/
			strcpy(buff2,"RUN|");
    		strcat(buff2,buff);
    		bytes_sent = send(conn_sock,buff2,sizeof(buff2),0);
    		printf("Xong gui nuoc co.\n");
			return Check_Send(bytes_sent);

		}
		if(number == 1){
			// nguoi dung chon quan mau trang
			*color = 1;
			bytes_sent = send(conn_sock,"COLOR_OK",22,0);
			return Check_Send(bytes_sent);
		}
}


int Check_Run(char string[1024], int conn_sock, int **chess, int color, char **server_run, char **client_run, int *flag){
	// color mau quan co ben client
	char *p;
	int x,x1; // toa do hang
	int y,y1; // toa do cot
	char buff[1024];
	char buff2[1024];
	char str[5];

	p = strtok(string,"|");
	p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/
	if(p == NULL){
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		*flag = 0;
		return Check_Send(bytes_sent);
	}
	strcpy(buff,"|");
	strcat(buff,p);
	x = atoi(p); 

	p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/ 
	if(p == NULL)	{
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		*flag = 0;
		return Check_Send(bytes_sent);
	}
	strcpy(buff,"|");
	strcat(buff,p);
	strcat(buff,"|->|");
	y = atoi(p); 

	p = strtok(NULL,"|");
	if(p == NULL){
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		*flag = 0;
		return Check_Send(bytes_sent);
	}
	strcat(buff,p);
	strcat(buff,"|");
	x1 = atoi(p); /* lay toa do hang cua nuoc toi*/ 
    
    p = strtok(NULL,"|");
    if(p == NULL){
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		*flag = 0;
		return Check_Send(bytes_sent);
	}
	strcat(buff,p);
	strcat(buff,"|");
    y1 = atoi(p); /* lay toa do cot cua nuoc toi*/ 
   
    if(check_chess_run(chess, color, x, y, x1 , y1)>0){ 
    	// check_run _ ai.h
    	//duong di cua phia client la hop le
    	strcpy(*client_run,buff);
    	*flag = 1;
    	chess[x1][y1] = chess[x][y];
    	chess[x][y]= '_';
    	
    	/*cap nhat nuoc lai nuoc co*/
    	/*
    		AI: tinh toan duong di doi pho
    	*/
    	int **chess2 = chess;
    	RunType run = find_way(chess2, color); /* ai.h gui vao mang va mau quan co cua phia client*/

    	if(run.status == 0){
    		//send("YOU_WIN"); // client thang
    		bytes_sent = send(conn_sock,"YOU_WIN",32,0);
    		strcpy(*server_run,"end_game"); /*khong con nuoc co de danh*/
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

	    	strcpy(*server_run, buff);
	    	strcat(*server_run," -> |");

	    	x1 = run.x1;
	    	sprintf(str, "%d", x1);/*chuyen so thanh xau*/
	    	strcat(*server_run,str);
	    	strcat(*server_run,"|");
	    	strcat(buff,str);
	    	strcat(buff,"|");
	    	
	    	y1 = run.y1;
	    	sprintf(str, "%d", y1);/*chuyen so thanh xau*/
	    	strcat(*server_run,str);
	    	strcat(*server_run,"|");
	    	strcat(buff,str);
	    	strcat(buff,"|");

	    	chess[x1][y1] = chess[x][y];
    		chess[x][y]= '_';

    		/*hien thi ban co sau khi cap nhat nuoc co cua client va server*/
    		paint(chess,color);
	    	
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
    	*flag = 0;
    	/*Neu nuoc co cua client nhap vao bi loi*/
    	//send("RUN_ERROR");
    	bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		return Check_Send(bytes_sent);
    	//return 1;
    }

}

#endif