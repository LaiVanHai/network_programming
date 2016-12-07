#include <stdio.h>
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
  chess[7][3]='H';chess[7][4]='W';

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
int check_tot(int chess[8][8] ,int x, int y, int x1, int y1, int mau){
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
int check_xe(int mang[8][8], int x, int y, int x1, int y1, int mau){
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
/************************************************************************/
void main(){
  int x,y, x1,y1;
  int giatri;
  int mau = 1;
  int kiemtra =0;
  make_chess(chess);
  paint(chess,mau);

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

    switch(giatri){
    case 'O':
      kiemtra = check_tot(chess,x,y,x1,y1,mau);
      break;
    case 'o':
      kiemtra = check_tot(chess,x,y,x1,y1,mau);
      break;
    case 'X':
      kiemtra = check_xe(chess,x,y,x1,y1,mau);
      break;
    }

    if(kiemtra == 1) {
      chess[x1][y1] = giatri;
      chess[x][y] = '_';
      paint(chess, 1);
    }
    else printf("Toa do can di chuyen khong dung\n");
}
