#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>	// EXIT_SUCCESS
#include <stdbool.h> // bool, true, false
#include <ctype.h> // isdigit
#include "utils.h"
typedef struct {
	int PID;	
	int parentPID;
	char name [40];
} Process;

void printVersion(){
	printf("rPstree UNKNOWN\n");
	printf("Copyright (C) 1993-2019 Werner Almesberger and CragiSmall\n\n");
	printf("rPstree version 0.0.1 (Ubuntu 9.4.0-Ubuntu 22.04.3)\n");
}

void printHelp(){
	printf("Display a tree of processes.\n");
	printf(" -v, --version\t\tdisplay version information\n");
	printf(" -h, --help\t\tdisplay help information\n");
	printf(" -p, --show-pids\tshow PIDs; implies -c\n");
}

bool isNumeric(const char* str){
	if (*str == '\0') {
		return false;
	}
	while (*str){
		if(!isdigit((unsigned char)*str)){
			return false;
		}
		str ++;
	}
	return true;
}

void readFiles(const char* filepath, char* content) {
	FILE* file = fopen(filepath, "r");
	char ch;
	int pointer = 0;
	if(file == NULL){
		return;
	}
	while((ch = fgetc(file)) != EOF){
		content[pointer++] = ch;
	}
	content[pointer] = '\0';
	fclose(file);
}

void test(){
	DIR *proc_dir;	// the pointer of the directory instream.
	struct dirent *entry; // used for the struct of the category.
	proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        perror("Failed to open /proc directory");
        return;
    }
	if (proc_dir) {
		while((entry = readdir(proc_dir)) != NULL){
			if(isNumeric(entry->d_name)) {
				char destination[50] = "";
				char content[1024] = "";
				int pid = atoi(entry->d_name);
				int ppid = get_parent_pid(pid);
				// concat the path of the process.
				strcat(destination, "/proc/");
				strcat(destination, entry->d_name);
				strcat(destination, "/comm");
				
				readFiles(destination, content);
				
				printf("pid:%d ", pid);
				printf("ppid:%d ", ppid);
				printf("%s\n", content);
			}
		}
		closedir(proc_dir);
	}
}

int main(int argc, char* argv[]){
	int help = 0, version = 0;
	for(int i = 0; i < argc; i++){
		assert(argv[i]);  // C standard
		if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) version = 1; 
		if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) help = 1;
	}
	assert(!argv[argc]); // C standard
	if(version == 1) {
		printVersion(); 
		return EXIT_SUCCESS; 
	}
	if(help == 1) {
		printHelp(); 
		return EXIT_SUCCESS;
	}
	// Process pcs[1024];
	test();
	return EXIT_SUCCESS;
}
