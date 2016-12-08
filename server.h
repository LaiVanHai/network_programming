#ifndef __SERVER__
#define __SERVER__

int Check_Mess(char recv_data[1024], int conn_soc);/*Xac thuc nhung yeu cau cua ben client gui toi*/
void sig_chld(int signo); /*xu ly goi tin sig*/
int Check_Send(int conn_soc, int bytes_sent);/*kiem tra trang thai gui du lieu toi client*/
int Check_Recv(int conn_soc, int bytes_recv);/*kiem tra trang thai nhan du lieu tu client*/
char* encode(char* str);/*ma hoa mat khau*/
char* decode(char* str);/*giai ma mat khau*/
void Clear();/*xoa bien luu tai khoan hien hanh*/
//int Find_User(char s1[1024]);/*tim kiem username trong database*/
int Exit_Connect(int conn_sock);/*huy ket noi voi client*/
int Send_Result(int conn_sock);/*gui file log ve client*/
int Check_Run(char string[1024], int conn_soc);/*kiem tra duong di nuoc co ma client gui toi*/
int End_Game(int conn_soc);/*xu ly khi client chiu thua server*/
int Check_Color(char str[1024], int conn_soc);/*kiem tra va xac nhan mau quan co ben phia client*/
int Check_Logout(char recv_data[1024], int conn_soc);/*xac thuc yeu cau thoat dang nhap cua client*/
int Start_Game(int conn_soc);/*xu ly yeu cau bat dau tro choi tu phia client*/
int Signup_Pass(char str[1024], int conn_soc, int confirm);/*xu ly dang ky mat khau cho tai khoan moi*/
//void Update_Database(char user[1024],char pass[1024]);/*cap nhat du lieu nguoi dung vao database*/
int Select_Work(char str[1024], int conn_soc);/*kiem tra tuy chon ban dau cua client gui toi server*/
int Check_User(char str[1024], int conn_soc);/*kiem tra tai khoan co yeu cau dang nhap*/
int Check_Login_Pass(char str[1024], int conn_soc);/*kiem tra mat khau dang nhap*/
int Ready_Signup(int conn_soc);/*xu ly yeu cau dang ky tai khoan moi tu phia client*/
int Signup_User(char str[1024], int conn_soc);/*dang ky tai khoan moi*/

#endif 