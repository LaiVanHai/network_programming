#ifndef __MY_TYPE__
#define __MY_TYPE__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char username[1024];
	char password[1024];
	int online;
}UserType;

typedef struct{
	int x;
	int y;
	int x1;
	int y1;
	int status; 
	/*
		1: nuoc co binh thuong
		2: nuoc co chieu tuong
		0: may het co-> may:thua
	*/
}RunType;

typedef enum {
	unauthenticated, /* trang thai khi bat dau ket noi voi client*/
	specified_id,
	signup,
	signup_pass,
	confim_pass,
	authenticated
}StatusType;

typedef enum {
	not_play, /*trang thai chua bat dau choi*/
	select_color, /*trang thai chon mau*/
	check_run, /*trang thai kiem tra nuoc di*/
	play /*trang thai choi*/
}PlayStatus;

#endif