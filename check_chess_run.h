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

/***********************************************************************/
/* - Hàm kiểm tra các nước đi của quân tốt.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
     vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân tốt là đúng, trả về 0 nếu nước đi là sai.
*/
int check_pawn(int **chess, int color, int x, int y, int x1, int y1){
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
/************************************************************************/
/*- Hàm kiểm tra các nước đi của quân xe.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
     vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân xe là đúng, trả về 0 nếu nước đi là sai.
*/
int check_rock(int **chess, int color, int x, int y, int x1, int y1){
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
/* - Hàm kiểm tra các nước đi của quân tướng.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
     vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân tướng là đúng, trả về 0 nếu nước đi là sai.
*/
int check_king(int **chess, int color, int x, int y, int x1, int y1){
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
/* - Hàm kiểm tra các nước đi của quân tượng.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
     vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân tượng là đúng, trả về 0 nếu nước đi là sai.
*/
int check_bishop(int **chess, int color, int x, int y, int x1, int y1){
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
    else if(y < y1 && x1-x == y-y1) {
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
int check_queen(int **chess, int color, int x, int y, int x1, int y1){
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
    if(color == 2) {
      if((chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
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
    if(color == 2) {
      if((chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
    else {
      if((chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
  }
  /*di chuyển theo đường chéo*/
  else if(x > x1) {
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
  /*di chuyển theo đường chéo*/
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
    else if(y < y1 && x1-x == y-y1) {
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
}

#endif