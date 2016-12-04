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
  char choice[10];
  int dd=0;
  printf("=====================================\n");
  printf("1|- Bat dau tro choi.\n");
  printf("2|- Thoat dang nhap.\n");
  printf("3|- Huy ket noi.\n");
  printf("=====================================\n");
  printf("Vui long nhap lua chon cua ban:");
  gets(choice);

}

void exit_programm(){
  printf("Ban da huy ket noi thanh cong.\n");
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
    if(strcmp(buff, "EXIT_OK") == 0); /*Huy ket noi thanh cong*/
    {
      exit_programm();
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
