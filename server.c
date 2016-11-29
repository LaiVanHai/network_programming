

typedef struct{
	char[1024] username;
	char[1024] password;
	int online;
}UserType;

int UserType user;
char username[1024];
char password[1024]; 

void Clear(){
	strcpy(user.username," ");
	strcpy(user.password," ");
	user.online=0;
}
int Check_Send(int conn_soc, int bytes_sent){
	if(bytes_sent>0)
	{
		return 1; 
	}
	else{
		close(conn_soc);
		return 0;
	}
}

int Check_Recv(int conn_soc, int bytes_recv){
	if(bytes_recv>0)
	{
		return 1;
	}
	else{
		close(conn_soc);
		return 0;
	}
}
int Select_Work(char[1024] string, int conn_soc){  /*tuy chon ban dau giua client va server*/
	// co 2 tuy chon
	// 1: dang nhap
	// 2: tao tai khoan moi
	// 3: huy ket noi
	char *p;
	p = strtok(string,"|");
	p = strtok(NULL,"\0"); // lay phan du lieu ma client gui ve
	int check = atoi(p); // lua chon cua client gui ve
	switch(check){
		case 1: // lua chon dang nhap
		{
			retry = 0;
			send("LOGIN")
			return 1; 
		}
		case 2: // lua chon dang ki
		{
			retry = 0;
			send("READY_SIGNUP")
			return 1; 
		}
		case 3:
		{
			retry = 0;
			return 0; // lua chon huy ket noi
		}
		default:
		{
			retry++;
			if(retry<5) // cho nhap sai toi da 5 lan
			{
				send("SELECT_ERROR");
				return 1;
			}
			else
				send("BLOCK");// huy ket noi
				return 0; // nhap sai qua nhieu, huy ket noi
		}
	}

}

Find_User(char[1024] string)
{
	TIM KIEM USER TRONG DATABASE
	Cap nhat mat khau va tai khoan  vao trong bien user
	password luu lai trong bien nay la password da duoc giai ma
}

int Check_User(char[1024] string, int conn_soc){ // kiem tra khi client gui ve username
	char *p;
	p = strtok(string,"|");
	p = strtok(NULL,"\0"); // lay phan du lieu ma client gui ve
	strcpy(username,p);
	if(Find_User(username))
	{
		send("LOGIN_USER_ID_OK");
		return 1;
	}
	else
	{
		send("LOGIN_USER_NOT_EXIST");
		/*
			Client se dua ra 3 lua chon
			- 1 tiep tuc dang nhap lai
			- 2 tao tai khoan moi
			- 3 thoat
		*/
		return 1;
	}
	
}

int Check_Login_Pass(char[1024] string, int conn_soc){
	char *p;
	char password[1024];
	p = strtok(string,"|");
	p = strtok(NULL,"\0"); // lay phan password ma client gui ve
	strcpy(password,p); // luu lai pass dang ki cua nguoi dung
	if(strcmp(password,user.password)==0)
	{
		retry=0;
		strcpy(user.username,username);
		strcmp(user.password,password);
		user.online=1;/*dat trang thai user thanh online*/
		send("LOGIN_SUCCESS");
		return 1;
	}
	else{
		retry++;
		if(retry<5) // cho nhap sai toi da 5 lan
			{
				send("PASS_NOT_MATCH");
				return 1;
			}
			else
			{
				Clear();
				send("BLOCK");// huy ket noi
				return 0; // nhap sai qua nhieu, huy ket noi
			}
	}
}

int Ready_Signup(int conn_soc){
	// Chuan bi cho cong viec dang ki tai khoan moi
	// Dua bien luu user hien tai ve trang thai rong
	send("READY_SIGNUP");
	return 1;
}

int Signup_User(char[1024] string, int conn_soc){
	char *p;
	p = strtok(string,"|");
	p = strtok(NULL,"\0"); // lay phan du lieu ma client gui ve
	strcpy(username,p);
	if(Find_User(username))
	{
		send("USER_ID_EXISTED");
		return 1;
	}
	else
	{
		send("SIGNUP_USER_ID_OK");
		return 1;
	}
}


int Signup_Pass(char[1024] string, int conn_soc, int confirm){
	char *p;
	char confirm_password[1024];
	p = strtok(string,"|");
	p = strtok(NULL,"\0"); // lay phan du lieu ma client gui ve
	if(strlen(p)<6){
		if(retry<5){
			retry++;
			send("PASS_SHORT");/*mat khau client nhap vao qua ngan*/
			return 1;
		}else
		{
			Clear();
			send("BLOCK"); // nhap sai qua nhieu lan
			return 0; 
		}
	}else{
		retry=0;
		if(confirm==0)// mat khau moi nhap lan dau
		{
			send("CONFIRM_PASS"); /*gui yeu cau nhap mat khau xac thuc*/
			strcmp(password,p);
			return 1;
		}
		else
		{
		// day la mat khau confirm
			strcmp(confirm_password,p);
			if(strcmp(password,confirm_password)==0){
				retry = 0;
				send("SIGNUP_USER_SUCCESS");/*thong bao cho ben client biet la da tao thanh cong tai khoan*/
				/*Client: goi lai menu giong luc moi dang nhap vao*/
				return 1;
			}	
			else{
				if(retry<5){
					retry++;
					send("CONFIRM_NOT_MATCH"); /*gui yeu cau ben client nhap lai mat khau xac nhan*/
					return 1;
				}else
				{
					Clear();
					send("BLOCK"); // nhap sai qua nhieu lan
					return 0; 
				}
			}
		}
	}
	
}

int Check_Logout(char[1024] recv_data, int conn_soc){
	if(user.online==0){
		// nguoi dung chua dang nhap
		send("LOGOUT_NOT_SUCCESS"); 
		/* thong bao nguoi dung chua dang nhap
		va quay lai trang thai nhu khi nhan thong diep HELLO
		*/
		return 1;
	}
	else
	{
		Clear();// xoa tai khoan dang dang nhap
		send("LOGOUT_SUCCESS");
		/* thong bao nguoi dung thoat dang nhap thanh cong
 		va quay lai trang thai nhu khi nhan thong diep HELLO
		*/
		return 0;
	}
}

int Exit_Connect(int conn_soc){
	// Thong bao cho nguoi dung biet da san sang cho thoat
	send("EXIT_OK");
	return 0;// tra ve 0 de ngat ket noi
}

int Start_Game(int conn_soc){
	send("GAME_READY"); 
	/* nhan duoc thong diep nay client cho nguoi dung chon mau quan co*/
	return 1;
}

int Check_Color(char[1024] string, int conn_soc){
	char *p;
	int number;
	p = strtok(string,"|");
	p = strtok(NULL,"\0"); // lay phan du lieu ma client gui ve
	number = atoi(p);
	if(number == 1 || number == 0){ // 1: den, 0: trang
		/*mau trang di truoc*/
		if(number == 1){
			// may se la nguoi danh truoc
		}
	}
	
}

int Check_Mess(char[1024] recv_data, int conn_soc){
	char *p;
	p = strtok(recv_data,"|");
	if(strcmp(p,"SELECT_WORK")){
		// lua chon cong viec khi moi vao
		return(Select_Work(recv_data, conn_soc);
	}
	if(strcmp(p,"LOGIN_USER")){
		// tim user trong he thong
		return Check_User(recv_data, conn_soc); 
	}
	if(strcmp(p,"LOGIN_PASS")){
		// kiem tra pass co trung khop hay khong
		return Check_Login_Pass(recv_data,conn_soc);
	}
	if(strcmp(p,"SIGNUP")==0){
		// chuan bi cho viec tao tai khoan moi
		return Ready_Signup(conn_soc);
	}
	if(strcmp(p,"SIGNUP_USER")==0){
		// kiem tra ten tai khoan dang ky moi
		return Signup_User(recv_data, conn_soc);
	}
	if(strcmp(p,"SIGNUP_PASS")==0){
		//	tao mat khau cho tai khoan dang ki moi
		return Signup_Pass(recv_data, conn_soc,0);
	}
	if(strcmp(p,"CONFIRM_PASS")==0){
		// xac nhan lai mat khau dang ki
		return Signup_Pass(recv_data,conn_soc,1);
	}
	if(strcmp(p,"LOGOUT")==0){
		// nguoi dung muon thoat dang nhap
		// suy tinh xem co nen bat nguoi dung truyen user muon thoat khong nhi
		return Check_Logout(recv_datam,conn_soc);
	}
	if(strcmp(p,"EXIT")==0){
		// nguoi dung muon huy ket noi voi server
		return Exit_Connect(conn_soc);
	}
	if(strcmp(p,"START_GAME")==0){
		// nhan yeu cau bat dau tro choi cua nguoi dung
		return Start_Game(conn_soc);
	}
	if(strcmp(p,"COLOR")==0){
		// nguoi choi da chon mau quan co, bat dau tro choi
		return Check_Color(recv_data,conn_soc);
	}
	
		
}

int main()
{
	int retry=0;
	
	if(Co yeu cau ket noi tu client){
		send("HELLO");
		Check_Send();// kiem tra trang thai gui
		int check_status=1;
		
		do{// bat dau phien lam viec voi client
			NHAN THONG DIEP TU PHIA CLIENT
			Check_Recv();// kiem tra trang thai nhan du lieu
			if(Check_Mess(recv_data, conn_soc)==0){
				check_status=0;
			}
			
		}while(check_status>0)

		
	}
}
