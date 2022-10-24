#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

const int maxChar = 1000;
const int commandSize = 20;
const int flagSize = 20;
const int argSize = 1000;

void echo(char flag1[], char flag2[], char* argument[]) {

	//Flags -> (-n) and TBD

	//Vanilla - no flags
	if (flag1[0] == '\0' && flag2[0] == '\0') {
		for (int i=0; argument[i] != NULL; i++) {
			printf("%s ", argument[i]);
		}

		printf("\n");
	}

	//1 flag 
	if (flag1[0] != '\0' && flag2[0] == '\0') {
		if (!strcmp(flag1, "-n")) {
			for (int i=0; argument[i] != NULL; i++) {
				if (i+1 < argSize)  {
					if (argument[i+1] != NULL) {
						printf("%s ", argument[i]);
					}
					else {
						printf("%s", argument[i]);
					}
				}
			}
		}
		else {
			printf("[!] Unknown flag %s entered\n");
		}
	}
}

void pwd(char flag1[], char flag2[]) {
	char dir[100];

	//No flags
	if (flag1[0] == '\0' && flag2[0] == '\0') {
		getcwd(dir, 100);
		printf("%s\n", dir);
	}

	//1 flag present 
	else if (flag2[0] == '\0') {

		//L flag - outputs contents of $PWD environment variable
		if (!strcmp(flag1, "-L")) {
			char* envName = getenv("PWD");
			printf("%s\n", envName);
		}

		//P flag - path to working directory without symlinks
		else if (!strcmp(flag1, "-P")) {
			const int size = 1000;
			char path_noSymbolicLinks[size];
			int flag = 0;
			getcwd(dir, 100);
			flag = readlink(dir, path_noSymbolicLinks, size);
			
			//print dir if no symlink
			if (flag < 0) {
				printf("%s\n", dir);
			}

			//print path with resolved symlinks if they exist
			else {
				printf("%s\n", path_noSymbolicLinks);
			}
		}
	}

	//Both flags present
	else if (!strcmp(flag1, "-L")) {
		printf("[!] Both flags cannot be used at the same time with this command\n");
	}
}

void cd(char flag1[], char flag2[], char* argument[]) {
	const char* path = argument[0];
	int ans = chdir(path);

	char dir[100];
	if (ans == 0) {
		getcwd(dir, 100);
		setenv("PWD", dir, 1);	//Set $PWD environment variable to changed path as well
	}
	else {
		printf("[!] Directory %s not found\n", path);
	}
}


void executeCommand(char* split[], int splitLen) {
	
	//Get command from split
	char cmd[commandSize];
	strcpy(cmd, split[0]);

	//Strings to store flags
	char flag1[flagSize];
	char flag2[flagSize];

	//Char pointer to store argument (could have multiple substrings in it)
	char* argument[argSize];

	//Initialise flag1 and flag2 to be arrays of null characters (helps in checking if flags exist or not)
	for (int i=0; i<flagSize; i++) {
		flag1[i] = '\0';
		flag2[i] = '\0';
	}

	//Initialise argument array to contain null 
	for (int i=0; i<argSize; i++) {
		argument[i] = NULL;
	}

	//Get flags from split and store them in flag1 and flag2
	if (splitLen >= 2) {
		if (split[1][0] == '-' && strlen(split[1])==2) {
			strcpy(flag1, split[1]);
		}
		if (splitLen >= 3 && split[2][0] == '-' && strlen(split[2])==2) {
			strcpy(flag2, split[2]);
		}
	}

	//set argument based on how many flags there are
	int start = 0;
	if (flag1[0] == '\0' && flag2[0] == '\0') {
		start = 1;
	}
	else if (flag1[0] != '\0' && flag2[0]=='\0') {
		start = 2;
	}
	else if (flag1[0] != '\0' && flag2[0] !='\0') {
		start = 3;
	}

	int counter = 0;
	for (int i=start; i<splitLen; i++) {
		argument[counter] = split[i];
		counter++;
	}

	//Exit shell
	if (!strcmp(cmd, "exit")) {
		exit(0);
	}

	//cd - change directory
	else if (!strcmp(cmd, "cd")) {
		cd(flag1, flag2, argument);
	}

	//pwd - print working directory
	else if (!strcmp(cmd, "pwd")) {
		pwd(flag1, flag2);
	}

	//echo 
	else if (!strcmp(cmd, "echo")) {
		echo(flag1, flag2, argument);
	}

	else if (!strcmp(cmd, "ls")) {
		
		char* args[] = {"./ls","\0","\0", 0};

		//-m flag
		if (!strcmp(flag1, "-m") || !strcmp(flag2, "-m")) {
			strcpy(args[1], "-m");
		}
		
		pid_t pid;
		pid = fork();

		if (pid < 0) {
			printf("[!] Some error occurred while executing this command");
		}
		else if (pid == 0) {
			execl(args[0], (const char*) args[0], (const char*) args[1], (const char*) args[2]);
		}
		else {
			wait(NULL);
			printf("Child complete!\n");
		}
	}

	//unknown command
	else {
		printf("[!] Unknown command %s entered\n", cmd);
	}
}

void command(char cmd[]) {
	fgets(cmd, maxChar, stdin);	//fgets is better than scanf since scanf stops reading input when it encouters whitespace
	char* temp = strtok(cmd, " \n");
	char* split[100];

	int splitCounter = 0;
	int splitLen = 0;
	
	while (splitCounter < 100) {
		if (temp == NULL) {
			split[splitCounter] = NULL;
		}
		else {
			split[splitCounter] = temp;
			splitLen++;
			temp = strtok(NULL, " \n");
		}
		splitCounter++;
	}


	// char mainCmd[100] = "\0";

	// //Removing trailing newline character
	// if (strlen(cmd) > 0 && cmd[strlen(cmd)-1] == '\n') {
	// 	cmd[strlen(cmd)-1] = '\0';
	// }

	// if (strlen(mainCmd) == 0) {
	// 	strcpy(mainCmd, split);
	// }

	// split = strtok(NULL, " ");
	executeCommand(split, splitLen);
}

void shell() {
	char cmd[maxChar];
	while (1) {
		char dir[100];
		getcwd(dir, 100);
	
		printf("[%s]> ", dir);
		command(cmd);
	}
}

int main() {
	shell();
	return 0;
}