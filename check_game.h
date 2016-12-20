#ifndef __CHECK_GAME__
#define __CHECK_GAME__

#include "time_machine.h"

int Check_Color(char str[1024], int conn_sock, int **chess, int *color, ChessStatus *chess_status);/*Kiem tra su hop le ve mau quan co*/
int Check_Run(char string[1024], int conn_sock, int **chess, int color, ChessStatus *chess_status);/*Kiem tra duong di quan co*/


int Check_Color(char str2[1024], int conn_sock, int **chess, int *color, ChessStatus *chess_status){
	char *p;
	int number;
	int x, x1, y, y1;
	char buff[1024];
	char buff2[1024];
	char str[5];
	ChessStatus chess_status2;

	// if(status != authenticated || play_status != select_color){
	// 	phai dang nhap moi choi game duoc
	// 	/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
	// 	return 0; 
	// }

	p = strtok(str2,"|");
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
			*color = 2;
			int **chess2 = chess;
			int check; 
			chess_status2 = *chess_status;
    		RunType run = find_way(chess2, *color, &chess_status2, &check); /* ai.h gui vao mang va mau quan co cua phia client*/
    		*chess_status = chess_status2;
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
    		strcpy(buff2,"RUN|");
    		strcat(buff2,buff);
    		printf("%s\n", buff2);
    		bytes_sent = send(conn_sock,buff2,sizeof(buff2),0);
			return Check_Send(bytes_sent);

		}
		if(number == 1){
			// nguoi dung chon quan mau trang
			*color = 1;
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


int Check_Run(char string[1024], int conn_sock, int **chess, int color, ChessStatus *chess_status){
	// color mau quan co ben client
	char *p;
	int x,x1; // toa do hang
	int y,y1; // toa do cot
	char buff[1024];
	char buff2[1024];
	char str[5];
	ChessStatus chess_status2;
	int stempt; /*bien luu trang thai nuoc co duoc danh*/
	/*
	0: nuoc co loi
	1: nuoc co binh thuong, 
	2: nuoc co nhap thanh,
	3: nuoc co phong tot*/

	//RunType run;


	// if(status != authenticated || play_status != play){
	// 	/*phai dang nhap moi choi game duoc*/
	// 	/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
	// 	return 0; 
	// }

	p = strtok(string,"|");
	p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/
	if(p == NULL){
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		if(Check_Send(bytes_sent)>0)
			return 2;
	}
	x = atoi(p); 
	p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/ 
	if(p == NULL)	{
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		if(Check_Send(bytes_sent)>0)
			return 2;
	}
	y = atoi(p); 
	p = strtok(NULL,"|");
	if(p == NULL){
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		if(Check_Send(bytes_sent)>0)
			return 2;
	}
	x1 = atoi(p); /* lay toa do hang cua nuoc toi*/ 
    p = strtok(NULL,"|");
    if(p == NULL){
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		if(Check_Send(bytes_sent)>0)
			return 2;
	}
    y1 = atoi(p); /* lay toa do cot cua nuoc toi*/ 
	chess_status2 = *chess_status;
	stempt = check_chess_run(chess, color, x, y, x1 , y1, &chess_status2); /*quet trang thai nuoc co*/

    if(stempt > 0){ 
    	// check_run _ ai.h
    	//duong di cua phia client la hop le
    	chess[x1][y1] = chess[x][y];
    	chess[x][y]= '_';
    	/*cap nhat nuoc lai nuoc co*/

    	*chess_status = chess_status2;
    	/*cap nhat lai bien luu trang thai cac quan co neu co su thay doi*/
    	/*
    		AI: tinh toan duong di doi pho
    	*/
    	int **chess2 = chess;
    	chess_status2 = *chess_status;
    	int check_castling;

    	RunType run = find_way(chess2, color, &chess_status2, &check_castling); /* ai.h gui vao mang va mau quan co cua phia client*/
		x1 = run.x1;
		y1 = run.y1;
		x = run.x;
		y = run.y;

    	*chess_status = chess_status2;
    	
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
    	/*Neu nuoc co cua client nhap vao bi loi*/
    	//send("RUN_ERROR");
    	bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		if(Check_Send(bytes_sent)>0)
			return 2;
    	//return 1;
    }

}

#endif