#include<stdlib.h>
#include<string.h>
#include<stdio.h>
int chess[9][9];
int check_char();
void make_chess(int chess[9][9])
{
  int i,j;
  for(i=1;i<=6;i++)
    {
      if(i==1)
	{
	   for(j=0;j<=7;j++)
	{
	  chess[i][j]='o';
	  printf("%d\n",chess[i][j]);
	}
	}
      else
      if(i==6)
	{
	   for(j=0;j<=7;j++)
	{
	  chess[i][j]='O';
	}
	}
      else
      for(j=0;j<=7;j++)
	{
	  chess[i][j]='_';
	}
    }
  chess[0][0]='x';chess[7][0]='X';chess[0][7]='x';chess[7][7]='X';
  chess[0][1]='m';chess[7][1]='M';chess[0][6]='m';chess[7][6]='M';
  chess[0][2]='t';chess[7][2]='T';chess[0][5]='t';chess[7][5]='T';
  chess[0][3]='w';chess[0][4]='h';
  chess[7][3]='H';chess[7][4]='W';
  
}
void paint(int chess[8][8], int x){
  /* x=0 nguoi choi chon den, 1 nguoi choi chon trang */
  int i,j;
  printf("--------------------------------------------------------------------\n");
  printf("       0\t1\t 2\t 3\t 4\t 5\t 6\t 7\t\n");
  printf("____________________________________________________________________\t");
  if(x==0)
  {
    printf("--->Den(H)<---\n");
  }
  else
  {
    printf("--->Den<---\n");
  }
  

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
int main(){
  make_chess();
  paint(chess);
  int id,x,y,x1,y1;
  printf("Nhap vao quan co ban chon:");
  scanf("%d %d",&x1,&y1);
  printf("Nhap vao toa do:");
  scanf("%d",&x);
  scanf("%d",&y);
  chess[x][y]=chess[x1][y1];
  chess[x1][y1]='_';
  paint(chess);
  
}
