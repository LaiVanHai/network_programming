#ifndef __AI__
#define __AI__

#include "my_type.h"
#include "check_chess_run.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_color(int **array, int color, int x, int y, int x1, int y1){
    /*return 0: chon nham mau quan co*/
    /*return -1: 2 quan co cung 1 mau*/
    /*return 1: ve mau thi khong co van de gi*/
    /*kiem tra mau quan chon hop le truoc*/
    /*1 - trang, 2 - den*/
    if(color == 1){
      if(array[x][y] >= 'a' && array[x][y] <= 'z')
        return 0;
    }
    else if(color == 2) {
      if(array[x][y] >= 'A' && array[x][y] <= 'Z')
        return 0;
    }
    /*Kiem tra neu 2 quan co o 2 vi tri  cung 1 mau thi bao loi*/
    if(array[x1][y1]!='_'){
      if((array[x][y]>=97) && (array[x][y]<=122)){
        if((array[x1][y1]>=97) && (array[x1][y1]<=122)){
          return -1;
        }
      }
      if((array[x][y]>=65) && (array[x][y]<=90)){
        if((array[x1][y1]>=65) && (array[x1][y1]<=90)){
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

	}
}
 
int Random(int n)
{
   return rand()%(n+1);
}


RunType find_way(int **a, int color){
	RunType run_type;
	run_type.x= Random(7);
	run_type.y= Random(7);
	run_type.x1= Random(7);
	run_type.y1= Random(7);
	a[run_type.x1][run_type.y1] = a[run_type.x][run_type.y];
	a[run_type.x][run_type.y] = '_';
	run_type.status=1;
	return run_type;
}
#endif