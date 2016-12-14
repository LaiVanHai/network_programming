#ifndef __TIME_MACHINE__
#define __TIME_MACHINE__

#include <stdio.h>
#include <time.h>
#include <string.h>

char* make_name_file(char s[1024]); /*tao ten file luu du lieu*/
char* scan_time(); /*check thoi gian hien tai cua he thong*/

char* make_name_file(char s[1024]){
	char* p;
	char result[1024];
    p = strtok(s," ");
    strcpy(result,p);
    strcat(result,"_");
    p = strtok(NULL," ");
    strcat(result,p);
    strcat(result,"_");
    p = strtok(NULL," ");
    strcat(result,p);
    strcat(result,"_");
    p = strtok(NULL,":");
    strcat(result,p);
    strcat(result,"_");
    p = strtok(NULL,":");
    strcat(result,p);
    strcat(result,"_");
    p = strtok(NULL," ");
    strcat(result,p);
    strcat(result,"_");
    p = strtok(NULL,"\n");
    strcat(result,p);
    strcat(result,".txt");
    strcpy(p,result);
    return p;
}  

char* scan_time(){
    char *p;
    time_t rawtime; 
    struct tm *timeinfo; 

    time(&rawtime); 
    timeinfo = localtime(&rawtime); 

    strcpy(p,asctime(timeinfo));

    return p;
}

#endif