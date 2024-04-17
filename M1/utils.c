#include "utils.h"
int get_parent_pid(int pid){
	char path[40], line[100], *p;
	int ppid = 0;
	
	// construct the file path.
	sprintf(path, "/proc/%d/status", pid);
 
	// open the file.
	FILE* statusf = fopen(path, "r");
	if (!statusf) {
		perror("fopen");
		return -1;	 // fail to get.
	}
	
	while(fgets(line, 100, statusf)){
		if(strncmp(line, "PPid:", 5) == 0){
			p = line + 5;
			while(*p == ' ') p ++;
			ppid = atoi(p);
			break;
		}
	}
	fclose(statusf);
	return ppid;
}
