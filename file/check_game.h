#ifndef __CHECK_GAME__
#define __CHECK_GAME__

#include "time_machine.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int Check_Color(char str[1024], int conn_sock, int **chess, int *color, char file_name[1024]);/*Kiem tra su hop le ve mau quan co*/
int Check_Run(char string[1024], int conn_sock, int **chess, int color, char file_name[2014]);/*Kiem tra duong di quan co*/


int Check_Color(char str[1024], int conn_sock, int **chess, int *color, char file_name[1024]){
	char *p;
	int number;
	FILE *f1;
	// if(status != authenticated || play_status != select_color){
	// 	phai dang nhap moi choi game duoc
	// 	/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
	// 	return 0; 
	// }
	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	number = atoi(p);
	if((f1 = fopen(file_name,"a+"))==NULL)
	{
	  printf("**ERROR** Open file error.\n");
	  return 0;
	}


	// if(number == 2){ // 1: trang, 2: den
		/*mau trang di truoc*/
		if(number == 2){
			fprintf(f1,"Your chess of color: Black.\n"); /*luu thong tin vao file log*/
			fprintf(f1,"===============================================\n");
			fprintf(f1,"=======COMPUTER_RUN======||======YOU_RUN=======\n");
			fprintf(f1,"=========================||====================\n");

			// may se la nguoi danh truoc
			*color = 2;
			chess[4][3] = chess[6][3];
			chess[6][3] = '_';
			/*cap nhat lai nuoc co*/
			bytes_sent = send(conn_sock,"RUN|6|3|4|3|",32,0);
			fprintf(f1,"%c - 6_3 -> 4_3\t||\t", chess[4][3]);
			fclose(f1);
			printf("5\n");
			return Check_Send(bytes_sent);
		}
		if(number == 1){
			// nguoi dung chon quan mau trang
			fprintf(f1,"Your chess of color: White.\n"); /*luu thong tin vao file log*/
			fprintf(f1,"===============================================\n");
			fprintf(f1,"=======COMPUTER_RUN======||======YOU_RUN=======\n");
			fprintf(f1,"=========================||====================\n");
			*color = 1;
			fclose(f1);
			printf("6\n");
			bytes_sent = send(conn_sock,"COLOR_OK",22,0);
			return Check_Send(bytes_sent);
		}
	
}


int Check_Run(char string[1024], int conn_sock, int **chess, int color, char file_name[1024]){
	// color mau quan co ben client
	char *p;
	int x,x1; // toa do hang
	int y,y1; // toa do cot
	char buff[1024];
	char buff2[1024];
	char str[5];
	FILE *f1;

	p = strtok(string,"|");
	p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/
	if(p == NULL){
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		return Check_Send(bytes_sent);
	}
	x = atoi(p); 
	p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/ 
	if(p == NULL)	{
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		return Check_Send(bytes_sent);
	}
	y = atoi(p); 
	p = strtok(NULL,"|");
	if(p == NULL){
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		return Check_Send(bytes_sent);
	}
	x1 = atoi(p); /* lay toa do hang cua nuoc toi*/ 
    p = strtok(NULL,"|");
    if(p == NULL){
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		return Check_Send(bytes_sent);
	}
    y1 = atoi(p); /* lay toa do cot cua nuoc toi*/ 
    if((f1 = fopen(file_name,"a+"))==NULL)
	{
	  printf("**ERROR** Open file error.\n");
	  return 0;
	}

    if(check_chess_run(chess, color, x, y, x1 , y1)>0){ 
    	// check_run _ ai.h
    	//duong di cua phia client la hop le
    	chess[x1][y1] = chess[x][y];
    	chess[x][y]= '_';
    	if(color == 2){
    		fprintf(f1,"%c - %d_%d -> %d_%d\n", chess[x1][y1], x, y, x1, y1);
    	}else{
    		fprintf(f1,"%c - %d_%d -> %d_%d\t||\t", chess[x1][y1], x, y, x1, y1);
    	}
    	printf("8\n");
    	/*cap nhat nuoc lai nuoc co*/
    	/*
    		AI: tinh toan duong di doi pho
    	*/
    	int **chess2 = chess;
    	RunType run = find_way(chess2, color); /* ai.h gui vao mang va mau quan co cua phia client*/
		x1 = run.x1;
		y1 = run.y1;
		x = run.x;
		y = run.y;   

		if(color == 1){
    		fprintf(f1,"%c - %d_%d -> %d_%d\n", chess[x1][y1], x, y, x1, y1);
    	}else{
    		fprintf(f1,"%c - %d_%d -> %d_%d\t||\t", chess[x1][y1], x, y, x1, y1);
    	} 	
    	
    	if(run.status == 0){
    		//send("YOU_WIN"); // client thang
    		char stemp[1024];
    		strcpy(stemp,scan_time()); /*lay thoi gian he thong*/
			fprintf(f1,"======================================\n");
			fprintf(f1,"End time: %s\n",stemp);
    		fprintf(f1,"************************************\n");
  			fprintf(f1,"************* YOU_WIN **************\n");
  			fprintf(f1,"************************************\n");
  			fclose(f1);
    		bytes_sent = send(conn_sock,"YOU_WIN",32,0);
			return Check_Send(bytes_sent);
    		//play_status = not_play; /*dua game ve trang thai chua bat dau*/
    		/**************************
    		gui file co pho ve phia client
    		***************************/
    	}
    	else
    	{
    		fclose(f1);
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
    	fclose(f1);
    	printf("9\n");
    	/*Neu nuoc co cua client nhap vao bi loi*/
    	//send("RUN_ERROR");
    	bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		return Check_Send(bytes_sent);
    	//return 1;
    }

}

#endif