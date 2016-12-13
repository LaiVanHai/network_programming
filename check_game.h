#ifndef __CHECK_GAME__
#define __CHECK_GAME__

int Check_Color(char str[1024], int conn_sock, int **chess, int *color){
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
			*color = 2;
			chess[4][3] = chess[6][3];
			chess[6][3] = '_';
			/*cap nhat lai nuoc co*/
			bytes_sent = send(conn_sock,"RUN|6|3|4|3|",32,0);
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


int Check_Run(char string[1024], int conn_sock, int **chess, int color){
	// color mau quan co ben client
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
	if(p == NULL){
		bytes_sent = send(conn_sock,"RUN_ERROR",42,0);
		return Check_Send(bytes_sent);
	}
	x = atoi(p); 
	p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/ 
	if(p == NULL){
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

    if(check_chess_run(chess, color, x, y, x1 , y1)>0){ 
    	// check_run _ ai.h
    	//duong di cua phia client la hop le
    	chess[x1][y1] = chess[x][y];
    	chess[x][y]= '_';
    	/*cap nhat nuoc lai nuoc co*/
    	/*
    		AI: tinh toan duong di doi pho
    	*/
    	RunType run = find_way(chess, color); /* ai.h gui vao mang va mau quan co cua phia client*/
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
		return Check_Send(bytes_sent);
    	//return 1;
    }

}

#endif