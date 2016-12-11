#ifndef __CHECK_CHESS_RUN__
#define __CHECK_CHESS_RUN__

int check_knight(int **array, int color, int x, int y, int x1, int y1){
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

#endif