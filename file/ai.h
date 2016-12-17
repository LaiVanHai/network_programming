#ifndef __AI__
#define __AI__

#include "my_type.h"
#include "check_chess_run.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_color(int **chess, int color, int x, int y, int x1, int y1);/*kiem tra su hop le ve mau*/
int check_chess_run(int **chess, int color, int x, int y, int x1, int y1); /*Kiem tra duong di cua quan co*/
RunType find_way(int **a, int color);/*Tim kiem duong di moi cho phia server*/


int check_color(int **chess, int color, int x, int y, int x1, int y1){
    /*return 0: chon nham mau quan co*/
    /*return -1: 2 quan co cung 1 mau*/
    /*return 1: ve mau thi khong co van de gi*/
    /*kiem tra mau quan chon hop le truoc*/
    /*1 - trang, 2 - den*/
    if(color == 1){
      if(chess[x][y] >= 'a' && chess[x][y] <= 'z')
        return 0;
    }
    else if(color == 2) {
      if(chess[x][y] >= 'A' && chess[x][y] <= 'Z')
        return 0;
    }
    /*Kiem tra neu 2 quan co o 2 vi tri  cung 1 mau thi bao loi*/
    if(chess[x1][y1]!='_'){
      if((chess[x][y]>=97) && (chess[x][y]<=122)){
        if((chess[x1][y1]>=97) && (chess[x1][y1]<=122)){
          return -1;
        }
      }
      if((chess[x][y]>=65) && (chess[x][y]<=90)){
        if((chess[x1][y1]>=65) && (chess[x1][y1]<=90)){
          return -1;
        }
      }
    }
  return 1;/*khong co van de gi*/
}

int check_chess_run(int **chess, int color, int x, int y, int x1, int y1)
{
	int value; /*ket qua lua chon quan co*/
	/*kiem tra tinh hop le cua nuoc co*/
	if(x<0 || x>7 || y<0 || y>7 || x1<0 || x1>7 || y1<0 || y1>7 ){
		/*nhap vao vi tri quan co khong hop le*/
		return -1;
	}
	if(chess[x][y]=='_'){
		//printf("day la quan co%c\n",chess[x][y]);
		/*chon quan co o vi tri trong khong*/
		return -1;
	}

	if(check_color(chess, color, x, y, x1, y1)!=1){
		/*xay ra loi ve mau quan co*/
		return -1;
	}

	value = chess[x][y];

	switch(value){
		case 'm':
		{
			return check_knight(chess,color,x,y,x1,y1);
		}
		case 'M':
		{
			return check_knight(chess,color,x,y,x1,y1);
		}
		case 'o':
		{
			return check_pawn(chess,color,x,y,x1,y1);
		}
	    case 'O':
	    {
	      	return check_pawn(chess,color,x,y,x1,y1);
	  	}
	    case 'x':
	    {
	      	return check_rock(chess,color,x,y,x1,y1);
	    }
	    case 'X':
	    {
	      	return check_rock(chess,color,x,y,x1,y1);
	    }
	    case 't':
	    {
	      	return check_bishop(chess,color,x,y,x1,y1);
	    }
	    case 'T':
	    {
	      	return check_bishop(chess,color,x,y,x1,y1);
	    }
	    case 'h':
	    {
	      	return check_queen(chess,color,x,y,x1,y1);
	    }
	    case 'H':
	    {
	      	return check_queen(chess,color,x,y,x1,y1);
	    }
	    case 'w':
	    {
	      	return check_king(chess,color,x,y,x1,y1);
	    }
	    case 'W':
	    {
	      	return check_king(chess,color,x,y,x1,y1);
	    }
	}
}

int Random(int n)
{
   return rand()%(n+1);
}


RunType find_way(int **a, int color){
	int color_server;
    int stempt;
	int dd=0;
	if(color==1)
	{
		color_server = 2;
	}
	else
	{
		color_server = 1;
	}

	RunType run_type;

	do{
       // printf(" 140 Server find way.\n");
		run_type.x= Random(7);
		run_type.y= Random(7);
		run_type.x1= Random(7);
		run_type.y1= Random(7);
        run_type.x2= run_type.x;
		dd = check_chess_run(a,color_server,run_type.x,run_type.y,run_type.x1,run_type.y1);
	}while(dd!=1);
	run_type.status=1;
	return run_type;
}
#endif
