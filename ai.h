#ifndef __MY_TYPE__
#define __MY_TYPE__

#include"my_type.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
 
int Random(int n)
{
   return rand()%(n+1);
}


int check_run(int a[9][9], int color, int x1, int y1, int x, int y)
{
	/*kiem tra tinh hop le cua nuoc co*/
	return 1;
}

RunType find_way(int a[9][9], int color){
	RunType run_type;
	run_type.x= Random(7);
	run_type.y= Random(7);
	run_type.x1= Random(7);
	run_type.y1= Random(7);
	run_type.status=1;
	return run_type;
}
#endif