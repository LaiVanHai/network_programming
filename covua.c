#include<stdio.h>
#include"my_type.h"
#define MAX 8

int chess[8][8];
//int check_char();
void make_chess(int chess[8][8])
{
  int i,j;
  for(i=1;i<=6;i++)
    {
      for(j=0;j<=7;j++)
        {
          if(i==1) chess[i][j]='o';
          else if(i==6) chess[i][j]='O';
          else chess[i][j]='_';
        }
    }
  chess[0][0]='x';chess[7][0]='X';chess[0][7]='x';chess[7][7]='X';
  chess[0][1]='m';chess[7][1]='M';chess[0][6]='m';chess[7][6]='M';
  chess[0][2]='t';chess[7][2]='T';chess[0][5]='t';chess[7][5]='T';
  chess[0][3]='w';chess[0][4]='h';
  chess[7][3]='W';chess[7][4]='h';

  chess[6][0] = '_';
}
void paint(int chess[8][8], int x){
  /* x=0 nguoi choi chon den, 1 nguoi choi chon trang */
  int i,j;
  printf("--------------------------------------------------------------------\n");
  printf("       0\t1\t 2\t 3\t 4\t 5\t 6\t 7\t\n");
  printf("____________________________________________________________________\t");
  if(x==0)
      printf("--->Den(H)<---\n");
  else
      printf("--->Den<---\n");

  for(i=0;i<=7;i++){
    printf("   ||\n");
    printf("   ||\n");
    printf("%d  ||   ",i);
    for(j=0;j<=7;j++){
      printf("%c\t",chess[i][j]);

    }
    printf("\n");
  }
  printf("____________________________________________________________________\t");
  if(x==0)
    {
      printf("--->Trang<---\n");
    }else{
    printf("--->Trang(H)<---\n");
  }
}
/***********************************************************************/
int check_mau(int mau, int giatri){
  if(mau == 0){
    if(giatri >= 'a' && giatri <= 'z')
      return 1;
    else return 0;
  }
  else if(mau == 1) {
    if(giatri >= 'A' && giatri <= 'Z')
      return 1;
    else return 0;
  }
}
/***********************************************************************/
int check_tot(int chess[8][8], int mau, int x, int y, int x1, int y1){
  int cheo_trai = '_', cheo_phai = '_';
  if(mau == 0) {
    int khoangcach_x = x1 - x;

    if(y1 == y) {
      if(khoangcach_x > 2 || khoangcach_x < 1)
        return 0;
      else if(khoangcach_x == 2){
        if(x == 1) {
          if(chess[x+1][y] == '_' && chess[x+2][y] == '_') return 1;
          else return 0;
        }
        else return 0;
      }
      else if(khoangcach_x == 1) {
        if(chess[x+1][y] == '_') return 1;
        else return 0;
      }
    }
    else if(y1 == y-1) {
      if(chess[x+1][y-1] >= 'A' && chess[x+1][y-1] <= 'Z' && khoangcach_x == 1)
        return 1;
      else return 0;
    }
    else if(y1 == y+1) {
      if(chess[x+1][y+1] >= 'A' && chess[x+1][y+1]<= 'Z' && khoangcach_x == 1)
        return 1;
      else return 0;
    }
    else return 0;
  }
  else{
    int khoangcach_x = x-x1;

    if(y1 == y) {
      if(khoangcach_x > 2 || khoangcach_x < 1)
        return 0;
      else if(khoangcach_x == 2){
        if(x == 6) {
          if(chess[x-1][y] == '_' && chess[x-2][y1] == '_') return 1;
          else return 0;
        }
        else return 0;
      }
      else if(khoangcach_x == 1) {
        if(chess[x-1][y] == '_') return 1;
        else return 0;
      }
    }
    else if(y1 == y-1) {
      if(chess[x-1][y-1] >= 'a' && chess[x-1][y-1] <= 'z' && khoangcach_x == 1)
        return 1;
      else return 0;
    }
    else if(y1 == y+1) {
      if(chess[x-1][y+1] >= 'a' && chess[x-1][y+1]<= 'z' && khoangcach_x == 1)
        return 1;
      else return 0;
    }
    else return 0;
  }
}
/************************************************************************/
int check_xe(int mang[8][8], int mau, int x, int y, int x1, int y1){
  int i,j;
  if(x == x1){
    if(y>y1) {
      for(j=y ; j>y1 ; j--){
        if(chess[x][j] != '_')
          return 0;
      }
      if((chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
    else {
      for(j=y ; j<y1 ; j++){
        if(chess[x][j] != '_')
          return 0;
      }
      if((chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
  }
  else if(y == y1) {
    if(x>x1){
      for(i=x ; i>x1 ; i-- ){
        if(chess[i][y1] != '_')
          return 0;
      }
      if((chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
    else {
      for(i=x ; i<x1 ; i++ ){
        if(chess[i][y1] != '_')
          return 0;
      }
      if((chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
  }
  else return 0;
}
int check_knight(int array[8][8], int color, int x, int y, int x1, int y1){
  int count=0;/*dem so nuoc toi da ma quan ma co the di*/
  int i;
  int j;
  i = y + 2;
  j = y - 2;
  if((i==y1 && i<=7 && i>=0)||(j == y1 && j<=7 && j>=0)){
    printf("Quan ma di theo phuong ngang.\n");
      i = x + 1;
      j = x - 1;
      if((i==x1 && i<=7 && i>=0)||(j==x1 && j<=7 && j>=0)){
        return 1; /*duong di hop le*/
      }else{
        return 0; /*duong di khong hop le*/
      }
  }else
  {
    i = x + 2;
    j = x - 2;
    if((i==x1 && i<=7 && i>=0)||(j == x1 && j<=7 && j>=0)){
      printf("Quan ma di theo phuong doc.\n");
      i = y + 1;
      j = y - 1;
      if((i==y1 && i<=7 && i>=0)||(j==y1 && j<=7 && j>=0)){
        return 1; /*duong di hop le*/
      }else{
        return 0; /*duong di khong hop le*/
      }
    }
    else
    {
      /*duong di cua quan ma khong hop le*/
      return 0; 
    }
  }
}

int check_color(int array[8][8], int color, int x, int y, int x1, int y1){
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
/************************************************************************/
void main(){
  int x,y, x1,y1;
  int giatri;
  int mau = 1;
  int kiemtra =0;
  make_chess(chess);
  paint(chess,mau);
  int dd =0;
  do{
  do{
    printf("Nhap quan co can danh: ");
    scanf("%d%*c%d%*c", &x, &y);
    if(x<0 || x>7 || y<0 || y>7)
      printf("Toa do ban nhap khong dung, nhap cac so tu 0-->7.Moi nhap lai\n");
    else if(chess[x][y] == '_') printf("Vi tri ban chon khong co quan co nao.Moi nhap lai\n");
    else {
      giatri = chess[x][y];
      kiemtra = check_mau(mau, giatri);
      if(kiemtra == 0) {
        printf("Ban da danh sai quan co, quan co cua ban la mau ");
        if(mau == 0) printf("den\n");
        else printf("trang\n");
      }
    }
  } while(x<0 || x>7 || y<0 || y>7 || kiemtra == 0 || chess[x][y] == '_');

  giatri = chess[x][y];
  printf("Nhap vi tri can di chuyen: ");
  scanf("%d%*c%d%*c", &x1,&y1);
  if(check_color(chess,mau,x,y,x1,y1)<=0){
    printf("Co van de lien quan den mau.\n");
  }else
  {
      switch(giatri){
      case 'O':
        kiemtra = check_tot(chess,mau,x,y,x1,y1);
        break;
      case 'o':
        kiemtra = check_tot(chess,mau,x,y,x1,y1);
        break;
      case 'X':
        kiemtra = check_xe(chess,mau,x,y,x1,y1);
        break;
      case 'M':
        kiemtra = check_knight(chess,mau,x,y,x1,y1);
        break;
      }

      if(kiemtra == 1) {
        chess[x1][y1] = giatri;
        chess[x][y] = '_';
        paint(chess, 1);
      }
      else printf("Toa do can di chuyen khong dung\n");
  }
  }while(dd==0);
}