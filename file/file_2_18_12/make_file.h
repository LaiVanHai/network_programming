#ifndef __MAKE_FILE__
#define __MAKE_FILE__

#include "time_machine.h"

int make_file(char file_name[1014],char ip_address[1024]){
	FILE *store_run;
	char stemp[1024];
	char stemp2[1024];
	strcpy(stemp,scan_time()); /*lay thoi gian he thong*/
	strcpy(stemp2,stemp);
	strcpy(file_name,make_name_file(stemp)); /*Tao file luu thong tin tran dau*/
	if((store_run = fopen(file_name,"w+"))==NULL)
	    {
	      printf("**ERROR** Open file error.\n");
		      return 0;
	    }
    else{
    	fprintf(store_run,"Start time: %s",stemp2);
    	fprintf(store_run,"Your IP: %s\n",ip_address);
    	fclose(store_run);
    	return 1;
    }
}
#endif
