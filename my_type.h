#ifndef __MY_TYPE__
#define __MY_TYPE__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char[1024] username;
	char[1024] password;
	int online;
}UserType;

typedef struct{
	char chess;
	int x;
	int y;
	int status; 
	/*
		1: nuoc co binh thuong
		2: nuoc co chieu tuong
		0: may het co-> may:thua
	*/
}RunType;

enum StatusType{
	unauthenticated, /* trang thai khi bat dau ket noi voi client*/
	specified_id,
	signup,
	enter_password,
	authenticated
}

enum PlayStatus{
	not_play, /*trang thai chua bat dau choi*/
	select_color, /*trang thai chon mau*/
	check_run, /*trang thai kiem tra nuoc di*/
	play /*trang thai choi*/
}

#endif