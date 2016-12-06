#include"interface.h"
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
int client_sock;
char buff[1024];
struct sockaddr_in server_addr;
int bytes_sent,bytes_received;
int chess[9][9];
int color;
////////////////////////////////////////////////////////////////////////////////
void menu(){
  char choice[10];
  printf("=====================================\n");
  printf("1. Dang nhap\n");
  printf("2. Tao tai khoan moi\n");
  printf("3. Huy ket noi\n");
  printf("=====================================\n");

  printf("Hay lua chon tuy chon: ");
  gets(choice);
  printf("-------------------------------------\n");
  //printf("ban da chon %s\n",choice);
  strcpy(buff,"SELECT_WORK|");
  strcat(buff,choice);
  strcat(buff,"|");
  /*khuon dang gui SELECT|1|*/
  //buff[strlen(buff)]='\0';
  //printf("%s\n",buff);
}
////////////////////////////////////////////////////////////////////////////////
void lg_user(){
  char s[80];
  printf("Nhap ten dang nhap: ");
  gets(s);
  printf("-------------------------------------\n");
  strcpy(buff, "LOGIN_USER|");
  strcat(buff, s);
  strcat(buff,"|");
  printf("%s\n",buff);
}
////////////////////////////////////////////////////////////////////////////////
void sgup_user(){
  char s[80];
  printf("Nhap ten dang ky: ");
  gets(s);
  printf("-------------------------------------\n");
  strcpy(buff, "SIGNUP_USER|");
  strcat(buff, s);
  strcat(buff,"|");
}
////////////////////////////////////////////////////////////////////////////////
void menu2(){
  int choice;
  int dd=0;
  printf("=====================================\n");
  printf("1. Dang nhap lai.\n");
  printf("2. Tao tai khoan moi\n");
  printf("3. Thoat\n");
  printf("=====================================\n");
  do
  {
    printf("Nhap vao lua chon cua ban:");
    scanf("%d", &choice);
    while(getchar()!='\n');
    switch(choice){
      case 1: {
        lg_user();
        dd=1;
        break;
      }
      case 2: {
        sgup_user();
        dd=1;
        break;
      }
      case 3: {
        strcpy(buff,"EXIT|");
        dd=1;
        break;
      }
      default: {
        printf("Ban vui long nhap lai yeu cau.\n");
        break;
      }
    }
  }while(dd==0);
}
////////////////////////////////////////////////////////////////////////////////

void lg_pass(){
  char s[80];
  printf("Nhap mat khau: ");
  gets(s);
  printf("-------------------------------------\n");
  strcpy(buff, "LOGIN_PASS|");
  strcat(buff, s);
  strcat(buff,"|");

}
////////////////////////////////////////////////////////////////////////////////

void sgup_pass(){
  char s[80];
  printf("Nhap mat khau: ");
  gets(s);
  printf("-------------------------------------\n");

  strcpy(buff, "SIGNUP_PASS|");
  strcat(buff, s);
  strcat(buff,"|");
}
////////////////////////////////////////////////////////////////////////////////
void confirm_pass(){
  char s[80];
  printf("Xac nhan mat khau: ");
  gets(s);
  printf("-------------------------------------\n");

  strcpy(buff, "CONFIRM_PASS|");
  strcat(buff, s);
  strcat(buff,"|");
}
////////////////////////////////////////////////////////////////////////////////
void authenticated_menu(){
  int choice;
  int dd=0;
  printf("=====================================\n");
  printf("1|- Bat dau tro choi.\n");
  printf("2|- Thoat dang nhap.\n");
  printf("3|- Huy ket noi.\n");
  printf("=====================================\n");
  do
  {
    printf("Nhap vao lua chon cua ban:");
    scanf("%d", &choice);
    //while(getchar()!='\n');
    switch(choice){
      case 1: {
        strcpy(buff,"START_GAME|");
        dd=1;
        break;
      }
      case 2: {
        strcpy(buff,"LOGOUT|");
        dd=1;
        break;
      }
      case 3: {
        strcpy(buff,"EXIT|");
        dd=1;
        break;
      }
      default: {
        printf("Ban vui long nhap lai yeu cau.\n");
        break;
      }
    }
  }while(dd==0);

}

void exit_program(){
  printf("Ban da huy ket noi thanh cong.\n");
}

void game_ready(){
  int dd=0;
  int choice=0;
  make_chess(chess);
  paint(chess,color);
  printf("=====================================\n");
  printf("1. Trang.\n");
  printf("2. Den.\n");
  printf("=====================================\n");
  do{
    printf("Vui long nhap vao lua chon cua ban:");
    scanf("%d",&choice);
    while(getchar()!='\n');
    switch(choice){
      case 1:
      {
        strcpy(buff,"COLOR|1|");
        color = 1;
        dd = 1;
        break;
      }
      case 2:
      {
        strcpy(buff,"COLOR|2|");
        color = 2;
        dd = 1;
        break;
      }
      case 3:
      {
        printf("**Loi**\nBan vui long nhap lai.\n");
        break;
      }
    }
  }while(dd==0);
}

void select_run(){
  char x1[2],y1[2],x[2],y[2];
  printf("Nhap vao quan co ban chon:\n");
  printf("Toa do hang:");
  gets(x1);
  printf("Toa do cot:");
  gets(y1);
  //scanf("%d %d",&x1,&y1);
  printf("Nhap vao vi tri ban muon toi:\n");
  printf("Toa do hang:");
  gets(x);
  printf("Toa do cot:");
  gets(y);
  strcpy(buff,"RUN|");
  strcat(buff,x1);
  strcat(buff,"|");
  strcat(buff,y1);
  strcat(buff,"|");
  strcat(buff,x);
  strcat(buff,"|");
  strcat(buff,y);
  strcat(buff,"|");
}

void select_warning(){
  int choice;
  int dd=0;
  printf("Day la nuoc co chieu tuong, ban co chiu thua khong?.\n");
  printf("=====================================\n");
  printf("1. Co.\n");
  printf("2. Khong.\n");
  printf("=====================================\n");
  do{
    printf("Vui long nhap vao lua chon cua ban:");
    scanf("%d",&choice);
    switch(choice){
      case 1:
      {
        strcpy(buff,"END_RUN");
        dd=1;
        break;
      }
      case 2:
      {
        select_run();
        dd=1;
        break;
      }
      default:
      {
        printf("**Loi**Ban da nhap vao tuy chon khong hop le.\n");
        break;
      }
    }

  }while(dd==0);

}

void server_run(int warning){
  /* warning = 0 nuoc co binh thuong
    warning = 1  nuoc co chieu tuong
  */
  char *p;
  int x,y,x1,y1;
  p = strtok(buff,"|");
  p = strtok(NULL,"|");
  x=atoi(p);
  p = strtok(NULL,"|");
  y=atoi(p);
  p = strtok(NULL,"|");
  x1=atoi(p);
  p = strtok(NULL,"|");
  y1=atoi(p);
  chess[x1][y1]=chess[x][y];
  chess[x][y]='_';
  paint(chess,color);
  if(warning == 0)
  {
    select_run();
  }
  else
  {
    select_warning();
  }
  
}

void you_win(){
  printf("************************************\n");
  printf("********** BAN DA THANG ************\n");
  printf("************************************\n");
  strcpy(buff,"RESULT"); /*Yeu cau nhan file ket qua tu phai server*/
}

void computer_win(){
  printf("************************************\n");
  printf("********** MAY DA THANG ************\n");
  printf("************************************\n");
  strcpy(buff,"RESULT"); /*Yeu cau nhan file ket qua tu phai server*/
}

int check_buff(char buff[80]) /* Kiem tra tin hieu ket thuc tu phia server*/
{
  if(strcmp(buff,"HELLO")==0) /*Khoi tao*/
    {
      menu();
      return 1;
    }
  if(strcmp(buff, "SELECT_ERROR") ==0) /*Nhap loi*/
    {
      printf("Thao tac nhap loi.vui long nhap lai.\n");
      menu();
      return 1;
    }
  /***********************************/
  ////////////////////////////LOGIN///////////////////////////////
  if(strcmp(buff,"READY_LOGIN")==0) /*Chuyen qua giao dien dang nhap,nhap Username*/
    {
      lg_user();
      return 1;
    }
  if(strcmp(buff, "LOGIN_USER_NOT_EXIST") ==0) /*Nhap tai khoan khong dung*/
    {
      printf("Tai khoan nhap khong dung.\n");
      menu2();
      return 1;
    }
  if(strcmp(buff, "LOGIN_USER_ID_OK") == 0) /*Giao dien nhap password*/
    {
      lg_pass();
      return 1;
    }
  if(strcmp(buff, "PASS_NOT_MATCH") ==0)
    {
      printf("Mat khau khong dung,moi nhap lai.\n");
      lg_pass();
      return 1;
    }
  /***********************************/
  if(strcmp(buff, "PASS_NOT_MATCH") ==0)
    {
      printf("Mat khau khong dung,moi nhap lai.\n");
      lg_pass();
      return 1;
    }

  /************************************/
  if(strcmp(buff, "BLOCK") ==0) /*Huy ket noi*/
    {
      printf("Ban bi huy ket noi.\n");
      return 0;
    }
  ////////////////////////////SIGNUP////////////////////////////////
  if(strcmp(buff, "READY_SIGNUP") == 0) /*Chuyen qua giao dien signup*/
    {
      sgup_user();
      return 1;
    }
  if(strcmp(buff, "USER_ID_EXISTED") == 0) /*Tai khoan da ton tai*/
    {
      printf("Tai khoan da ton tai, moi nhap lai\n");
      sgup_user();
      return 1;
    }
  if(strcmp(buff, "SIGNUP_USER_ID_OK") ==0) /*Nhap password*/
    {
      sgup_pass();
      return 1;
    }
  if(strcmp(buff, "PASS_SHORT") ==0) /*Password qua ngan*/
    {
      printf("Mat khau qua ngan, moi nhap lai.\n");
      sgup_pass();
      return 1;
    }
  if(strcmp(buff, "CONFIRM_PASS") ==0) /*confirm password*/
    {
      confirm_pass();
      return 1;
    }
  if(strcmp(buff, "CONFIRM_NOT_MATCH") ==0) /*Xac nhan mat khau chua dung*/
    {
      printf("Xac nhan mat khau chua dung, moi nhap lai.\n");
      confirm_pass();
      return 1;
    }
  if(strcmp(buff, "SIGNUP_USER_SUCCESS") ==0) /*Dang ki thanh cong, chuyen qua giao dien menu*/
    {
      menu();
      return 1;
    }
    if(strcmp(buff, "LOGIN_SUCCESS") ==0) /*Dang ki thanh cong, chuyen qua giao dien menu*/
    {
      authenticated_menu();
      return 1;
    }
    if(strcmp(buff, "LOGOUT_SUCCESS") ==0) /*Dang ki thanh cong, chuyen qua giao dien menu*/
    {
      printf("Ban da thoat dang nhap thanh cong.\n");
      menu();
      return 1;
    }
    if(strcmp(buff, "GAME_READY") ==0) /*Chon mau quan co de chuan bi choi*/
    {
      game_ready();
      return 1;
    }
    if(strcmp(buff, "COLOR_OK") ==0) /*Nhap vao nuoc co cua phia client*/
    {
      select_run();
      return 1;
    }
    if(buff[strlen(buff)-1]=='|'){
      char str[1024];
      char *p;
      printf("Check run.\n");
      strcpy(str, buff);
      p = strtok(str,"|");
      if(strcmp(p,"RUN")==0){ /*day la nuoc co binh thuong ma server gui den*/
        server_run(0); /*hien thi nuoc co cua phia server*/
        return 1;
      }
      if(strcmp(p,"RUN_W")==0){ /*day la nuoc co chieu tuong ma server gui den*/
        server_run(1); /*hien thi nuoc co cua phia server*/
        return 1;
      }
    }
    if(strcmp(buff, "EXIT_OK") == 0); /*Huy ket noi thanh cong*/
    {
      exit_program();
      return 0;
    }
    if(strcmp(buff, "YOU_WIN") == 0); /*Huy ket noi thanh cong*/
    {
      you_win();
      return 1;
    }
    if(strcmp(buff, "COMPUTER_WIN") == 0); /*Huy ket noi thanh cong*/
    {
      computer_win();
      return 1;
    }
    if(strcmp(buff, "RUN_ERROR") == 0); /*Huy ket noi thanh cong*/
    {
      run_error();
      return 0;
    }
  return 0;
}

int main(){
  
  client_sock=socket(AF_INET,SOCK_STREAM,0);
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5500);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  int dd=1;
  
  if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
    printf("\nError!Can not connect to sever!Client exit imediately! ");
    return 0;
  }
  
  do
    {		
      bytes_received = recv(client_sock,buff,1024,0);
      if(bytes_received == -1){
    	printf("\nError!Cannot receive data from sever!\n");
    	close(client_sock);
    	exit(-1);
      }
      buff[bytes_received] = '\0';
      printf("***From Sever: %s\n", buff);
      if(check_buff(buff) == 1){
        bytes_sent = send(client_sock,buff,strlen(buff),0);
        if(bytes_sent == -1){
          printf("\nError!Cannot send data to sever!\n");
          close(client_sock);
          exit(-1);
        }
      }
      else dd=0;
    }while(dd==1);	
  close(client_sock);
  return 0;
}
