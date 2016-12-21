#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define MAX 8

int chess[8][8];
/*********************************************************************************/
/* - Hàm khởi tạo bàn cờ
   - Giá trị truyền vào là 1 mảng 8*8, hàng 0-->7, cột 0-->7
   - Màu đen là các chữ cái thường, màu trắng là các chữ in hoa
*/
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
  chess[0][3]='h';chess[7][3]='H';
  chess[0][4]='w';chess[7][4]='W';
  chess[4][5]='_';
}
/*********************************************************************************/
/* - Hàm vẽ bàn cờ
   - Giá trị truyền vào là 1 mảng 8*8, màu của quân cờ color (1-trắng, 2-đen)
*/
void paint(int chess[8][8], int color){
  int i,j;
  printf("--------------------------------------------------------------------\n");
  printf("       0\t1\t2\t3\t4\t5\t6\t7\t\n");
  printf("____________________________________________________________________\t");
  if(color == 2) printf("--->Den(H)<---\n");
  else       printf("--->Den<---\n");

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
  if(color == 2) printf("--->Trang<---\n");
  else       printf("--->Trang(H)<---\n");
}
/***********************************************************************/
/* - Hàm kiểm tra màu của quân cờ người chơi cần đánh.
   - Tham số truyền vào gồm màu của quân cờ color, giá trị của quân cờ
   ở vị trí hiện tại(x,y).
   - Hàm trả về 1 nếu quân cờ cần đánh đúng màu của người chơi, trả về
   0 nếu không đúng màu của người chơi.
*/
int check_color(int color, int giatri){

  if(color == 2){
    if(giatri >= 'a' && giatri <= 'z')
      return 1;
    else return 0;
  }
  else if(color == 1) {
    if(giatri >= 'A' && giatri <= 'Z')
      return 1;
    else return 0;
  }
}
/***********************************************************************/
/* - Hàm kiểm tra các nước đi của quân tốt.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
     vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân tốt là đúng, trả về 0 nếu nước đi là sai.
*/
int check_pawn(int chess[8][8] , int color, int x, int y, int x1, int y1){
  //quân đen
  if(color == 2){
    if((x1-x) >2 || (x1-x) <1)
      return 0;
    else if((x1-x) == 2){
      if(y1 == y && x == 1 && chess[x+1][y1] == '_' && chess[x1][y1] == '_')   /*di chuyển dọc 2 ô*/
        return 1;
      else return 0;
    }
    else {
      if(y1 == y && chess[x1][y1] == '_')                                      /*di chuyển dọc 1 ô*/
        return 1;
      else if(y1 == y-1 && chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z')       /*ăn chéo trái*/
        return 1;
      else if(y1 == y+1 && chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z')       /*ăn chéo phải*/
        return 1;
      else return 0;
    }
  }
  //quân trắng
  else {
    if((x-x1) >2 || (x-x1) <1)
      return 0;
    else if((x-x1) == 2){
      if(y == y1 && x==6 && chess[x-1][y1] == '_' && chess[x1][y1] == '_') {     /*di chuyển dọc 2 ô*/
        printf("vao\n");
        return 1;
      }
      else return 0;
    }
    else {
      if(y1 == y && chess[x1][y1] == '_')                                       /*di chuyển dọc 1 ô*/
        return 1;
      else if(y1 == y-1 && chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z')        /*ăn chéo trái*/
        return 1;
      else if(y1 == y+1 && chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z')        /*ăn chéo phải*/
        return 1;
      else return 0;
    }
  }
}
/*********************************************************************************/
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
/************************************************************************/
/*- Hàm kiểm tra các nước đi của quân xe.
  - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
  vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
  - Hàm trả về 1 nếu nước đi của quân xe là đúng, trả về 0 nếu nước đi là sai.
*/
int check_rock(int chess[8][8], int color, int x, int y, int x1, int y1){
  int i,j;
  int start,finish;
  /*di chuyển theo hàng ngang*/
  if(x == x1){
    if(y > y1) {
      start = y1 +1;
      finish = y;
    }
    else {
      start = y +1;
      finish = y1;
    }
    for(j= start ; j<finish; j++) {
      if(chess[x1][j] != '_')
        return 0;
    }
    //quân đen
    if(color == 2) {
      if((chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
    //quân trắng
    else {
      if((chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
  }
  /*di chuyển theo hàng dọc*/
  else if(y == y1){
    if(x > x1) {
      start = x1 +1;
      finish = x;
    }
    else {
      start = x +1;
      finish =x1;
    }
    for(i= start ; i<finish; i++){
      if(chess[i][y1] != '_')
        return 0;
    }
    //quân đen
    if(color == 2) {
      if((chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
    //quân trắng
    else {
      if((chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
  }
  else return 0;
}
/************************************************************************/
/* - Hàm kiểm tra các nước đi của quân tượng.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
   vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân tượng là đúng, trả về 0 nếu nước đi là sai.
*/
int check_bishop(int chess[8][8], int color, int x, int y, int x1, int y1){
  int i,j;
  if(x > x1) {
    if(y > y1 && x-x1 == y-y1) {
      j=y-1;
      for(i=x-1 ; i>x1 ; i-- ){
        if(chess[i][j] != '_')
          return 0;
        j = j-1;
      }
      if(color == 2) {
        if(chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
      else {
        if(chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
    }
    else if(y < y1 && x-x1 == y1-y) {
      j=y+1;
      for(i=x-1 ; i>x1 ; i-- ){
        if(chess[i][j] != '_')
          return 0;
        j = j+1;
      }
      if(color == 2) {
        if(chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
      else {
        if(chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
    }
    else return 0;
  }
  else if(x1 > x){
    if(y > y1 && x1-x == y-y1) {
      j=y-1;
      for(i=x+1 ; i<x1 ; i++ ){
        if(chess[i][j] != '_')
          return 0;
        j = j-1;
      }
      if(color == 2) {
        if(chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
      else {
        if(chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
    }
    else if(y < y1 && x1-x == y1-y) {
      j=y+1;
      for(i=x+1 ; i<x1 ; i++ ){
        if(chess[i][j] != '_')
          return 0;
        j = j+1;
      }
      if(color == 2) {
        if(chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
      else {
        if(chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z' || chess[x1][y1] == '_')
          return 1;
      else return 0;
      }
    }
    else return 0;
  }
  else return 0;
}
/************************************************************************/
/* - Hàm kiểm tra các nước đi của quân hậu.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
   vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1).
   - Hàm trả về 1 nếu nước đi của quân hậu là đúng, trả về 0 nếu nước đi là sai.
*/
int check_queen(int chess[8][8], int color, int x, int y, int x1, int y1){
  if(x == x1 || y == y1){
    if(check_rock(chess,color,x,y,x1,y1) == 1)
      return 1;
    else return 0;
  }
  else if(x != x1){
    if(check_bishop(chess,color,x,y,x1,y1) == 1)
      return 1;
    else return 0;
  }
  else return 0;
}
/************************************************************************/
/* - Hàm kiểm tra các nước đi của quân tướng.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
   vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân tướng là đúng, trả về 0 nếu nước đi là sai.
*/
int check_king(int chess[8][8], int color, int x, int y, int x1, int y1){
  /*kiem tra xem da het co hay chua*/
  //kiểm tra 8 ô liền kề
  if(y1 == y-1 || y1 == y || y1 == y+1) {
    if(x1 == x-1 || x1 == x || x1 == x+1) {
      //quân đen
      if(color == 2){
        if(chess[x1][y1] == '_' || (chess[x1][y1] > 'A' && chess[x1][y1] <='Z'))
          return 1;
        else return 0;
      }
      //quân trắng
      else {
        if(chess[x1][y1] == '_' || (chess[x1][y1] > 'a' && chess[x1][y1] <='z'))
          return 1;
        else return 0;
      }
    }
    else return 0;
  }
  else return 0;
}
/************************************************************************/
int check_checkmate(int chess[8][8], int color,  int x, int y){
  int i, j;
  for(i=0 ;i<=7 ;i++){
    for(j=0 ; j<=7 ;j++){
      if(color == 1) {
        switch(chess[i][j]){
        case 'o':
          if(check_pawn(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        case 'x':
          if(check_rock(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        case 't':
          if(check_bishop(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        case 'h':
          if(check_queen(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        case 'w':
          if(check_king(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        }
      }
      else {
        switch(chess[i][j]){
        case 'O':
          if(check_pawn(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
        case 'X':
          if(check_rock(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
        case 'T':
          if(check_bishop(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
        case 'H':
          if(check_queen(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
        case 'W':
          if(check_king(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
        }
      }
    }
  }
}
/************************************************************************/
void tot_phong(int chess[8][8], int color, int x1, int y1){
  char value;
  if(color == 1) {
    do {
      printf("Ban muon phong con nao? X,M,T,H :\n");
      scanf("%c%*c",&value);
      if(value != 'X' && value != 'M' && value != 'T' && value != 'H')
        printf("Ban nhap sai quan co,moi nhap lai.\n");
    } while(value != 'X' && value != 'M' && value != 'T' && value != 'H');
    chess[x1][y1] = value;
    paint(chess,color);
  }
  else {
    do {
      printf("Ban muon phong con nao? x,m,t,h :\n");
      scanf("%c%*c",&value);
      if(value != 'x' && value != 'm' && value != 't' && value != 'h')
        printf("Ban nhap sai quan co,moi nhap lai.\n");
    } while(value != 'x' && value != 'm' && value != 't' && value != 'h');
    chess[x1][y1] = value;
    paint(chess,color);
  }
}
/************************************************************************/
int castling(int chess[8][8], int color, int x, int y, int x1, int y1,
             int status_king, int status_rock1, int status_rock2){
  if(status_king == 0) {
    if(color == 1){
      if(y1 == y-2 && chess[7][0] == 'X' && status_rock1 == 0){
        if(check_rock(chess,color,7,0,7,3) == 1 && check_checkmate(chess,color,x1,y1) != 1){
          chess[7][0] = '_';
          chess[7][3] = 'X';
          return 1;
        }
      }
      else if(y1 == y+2 && chess[7][7] == 'X' && status_rock2 == 0){
        if(check_rock(chess,color,7,7,7,5) == 1 && check_checkmate(chess,color,x1,y1) != 1){
          chess[7][7] = '_';
          chess[7][5] = 'X';
          return 1;
        }
      }
      return 0;
    }
    else {
      if(y1 == y-2 && chess[0][0] == 'x' && status_rock1 == 0){
        if(check_rock(chess,color,0,0,0,3) == 1 && check_checkmate(chess,color,x1,y1) != 1){
          chess[0][0] = '_';
          chess[0][3] = 'x';
          return 1;
        }
      }
      else if(y1 == y+2 && chess[0][7] == 'x' && status_rock2 == 0){
        if(check_rock(chess,color,0,7,0,5) == 1 && check_checkmate(chess,color,x1,y1) != 1){
          chess[0][7] = '_';
          chess[0][5] = 'x';
          return 1;
        }
      }
      else return 0;
    }
  }
  else return 0;
}
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
void ai(int chess[8][8], int color){ /*vẫn chưa nghĩ đc*/
  int i,j, color_may;
  int mang[8][8];
  for(i=0 ;i<=7 ;i++ ){
    for(j=0 ;j<=7 ;j++ ){
      mang[i][j] = chess[i][j];
    }
  }

  if(color == 1){
    color_may = 2;

  }
}
/************************************************************************/
void main(){
  int x,y, x1,y1;
  int giatri;
  int color = 1, kiemtra = 0;
  int status_king = 0, status_rock1 = 0, status_rock2 = 0;
  int king_x = 0, king_y = 4, KING_x = 7, KING_y = 4;
  make_chess(chess);
  paint(chess,color);
  while(1){
    do{
      if(color == 1) {
        if(check_checkmate(chess,color,KING_x,KING_y) == 1) {
          printf("chieu tuong \n");

        }
      }
      else {
        if(check_checkmate(chess,color,king_x,king_y) == 1) {
          printf("CHIEU TUONG \n");
        }
      }
      printf("Nhap vi tri quan co can danh: ");
      scanf("%d%*c%d%*c", &x, &y);
      if(x<0 || x>7 || y<0 || y>7)
        printf("Toa do ban nhap khong dung, nhap cac so tu 0-->7.Moi nhap lai\n");
      else if(chess[x][y] == '_') printf("Vi tri ban chon khong co quan co nao.Moi nhap lai\n");
      else {
        giatri = chess[x][y];
        kiemtra = check_color(color, giatri);
        if(kiemtra == 0){
          printf("Ban da danh sai quan co, quan co cua ban la mau ");
          if(color == 2) printf("den\n");
          else printf("trang\n");
        }
      }
    } while(x<0 || x>7 || y<0 || y>7 || kiemtra == 0 || chess[x][y] == '_');

    giatri = chess[x][y];

    do {
      printf("Nhap vi tri can di chuyen: ");
      scanf("%d%*c%d%*c", &x1,&y1);
      if(x1<0 || x1>7 || y1<0 || y1>7)
        printf("Toa do ban nhap khong dung, nhap cac so tu 0-->7.Moi nhap lai\n");
    } while(x1<0 || x1>7 || y1<0 || y1>7);

    switch(giatri){
    case 'o':
      kiemtra = check_pawn(chess,color,x,y,x1,y1);
      break;
    case 'O':
      kiemtra = check_pawn(chess,color,x,y,x1,y1);
      break;
    case 'x':
      kiemtra = check_rock(chess,color,x,y,x1,y1);
      if(kiemtra == 1 && y == 0)
        status_rock1 = 1;
      else if(kiemtra == 1 && y == 7)
        status_rock2 = 1;
      break;
    case 'X':
      kiemtra = check_rock(chess,color,x,y,x1,y1);
      if(kiemtra == 1 && y == 0)
        status_rock1 = 1;
      else if(kiemtra == 1 && y == 7)
        status_rock2 = 1;
      break;
    case 't':
      kiemtra = check_bishop(chess,color,x,y,x1,y1);
      break;
    case 'T':
      kiemtra = check_bishop(chess,color,x,y,x1,y1);
      break;
    case 'h':
      kiemtra = check_queen(chess,color,x,y,x1,y1);
      break;
    case 'H':
      kiemtra = check_queen(chess,color,x,y,x1,y1);
      break;
    case 'w':
      if(x1 == x && (y1 == y-2 || y1 == y+2)) {
        if(castling(chess,color,x,y,x1,y1,status_king,status_rock1,status_rock2)==1)
          kiemtra = 1;
        else kiemtra = 0;
      }
      else kiemtra = check_king(chess,color,x,y,x1,y1);
      if(kiemtra == 1) {
        king_x = x1;
        king_y = y1;
        status_king = 1;
      }
      break;
    case 'W':
      if(x1 == x && (y1 == y-2 || y1 == y+2)) {
        if(castling(chess,color,x,y,x1,y1,status_king,status_rock1,status_rock2)==1)
          kiemtra = 1;
        else kiemtra = 0;
      }
      else kiemtra = check_king(chess,color,x,y,x1,y1);
      if(kiemtra == 1) {
        KING_x = x1;
        KING_y = y1;
        status_king = 1;
      }
      break;
    }

    if(kiemtra == 1) {
      chess[x1][y1] = giatri;
      chess[x][y] = '_';
      paint(chess, color);
      if(color == 1){
        if(chess[x1][y1] == 'O' && x1 == 0){
          tot_phong(chess,color,x1,y1);
        }
      }
      else {
        if(chess[x1][y1] == 'o' && x1 == 7)
          tot_phong(chess,color,x1,y1);
      }
    }
    else printf("Toa do can di chuyen khong dung\n");
  }
}
