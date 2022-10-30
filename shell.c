#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

const int maxChar = 1000;
const int commandSize = 20;
const int flagSize = 20;
const int argSize = 1000;

//Struct args used for pthread-based functions
struct args {
	char path[100];
	char* argv[100];
};

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

int pwd(char flag1[], char flag2[]) {
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

	return 0;
}

int cd(char flag1[], char flag2[], char* argument[]) {
	const char* path = argument[0];
	int ans = chdir(path);

	char dir[100];
	if (ans == 0) {
		getcwd(dir, 100);
		setenv("PWD", dir, 1);	//Set $PWD environment variable to changed path as well
		return 0;
	}
	else {
		printf("[!] Directory %s not found\n", path);
		return -1;
	}
}


void* ls(void* passArgs) {
	// for (int i=0; i<1; i++) {
	// 	printf("%s\n", ((struct args *) passArgs) -> argv[i]);
	// }
	// char* str = (char*) malloc (100*sizeof(char));
	// strcat(str, ((struct args*) passArgs) -> path);
	// strcat(str, "/ls ");

	// for (int i=0; i<100; i++) {
	// 	strcat(str, ((struct args*) passArgs) -> argv[i]);
	// 	strcat(str, " ");
	// }

	system("./ls NO NO");

	printf("Thread created woohoo!\n");
}

void threadExecute(char* split[], int splitLen, char p[]) {
	pthread_t t;

	struct args* passArgs = (struct args*) malloc (sizeof(struct args));

	for (int i=0; i<100; i++) {
		passArgs -> path[i] = p[i];
	}

	for (int i=0; i<splitLen; i++) {
		passArgs -> argv[i] = split[i];
	}

	int test = pthread_create(&t, NULL, ls, (void *) passArgs);
	pthread_join(t, NULL);
	free((void *) passArgs);
	exit(0);
}

int executeCommand(char* split[], int splitLen, char p[]) {
	
	threadExecute(split, splitLen, p);

	// //Get command from split
	// char cmd[commandSize];
	// strcpy(cmd, split[0]);

	// //Strings to store flags
	// char flag1[flagSize];
	// char flag2[flagSize];

	// //Char pointer to store argument (could have multiple substrings in it)
	// char* argument[argSize];

	// //Initialise flag1 and flag2 to be arrays of null characters (helps in checking if flags exist or not)
	// for (int i=0; i<flagSize; i++) {
	// 	flag1[i] = '\0';
	// 	flag2[i] = '\0';
	// }

	// //Initialise argument array to contain null 
	// for (int i=0; i<argSize; i++) {
	// 	argument[i] = NULL;
	// }

	// //Get flags from split and store them in flag1 and flag2
	// if (splitLen >= 2) {
	// 	if (split[1][0] == '-' && strlen(split[1])==2) {
	// 		strcpy(flag1, split[1]);
	// 	}
	// 	if (splitLen >= 3 && split[2][0] == '-' && strlen(split[2])==2) {
	// 		strcpy(flag2, split[2]);
	// 	}
	// }

	// //set argument based on how many flags there are
	// int start = 0;
	// if (flag1[0] == '\0' && flag2[0] == '\0') {
	// 	start = 1;
	// }
	// else if (flag1[0] != '\0' && flag2[0]=='\0') {
	// 	start = 2;
	// }
	// else if (flag1[0] != '\0' && flag2[0] !='\0') {
	// 	start = 3;
	// }

	// int counter = 0;
	// for (int i=start; i<splitLen; i++) {
	// 	argument[counter] = split[i];
	// 	counter++;
	// }

	// //Exit shell
	// if (!strcmp(cmd, "exit")) {
	// 	exit(0);
	// }

	// //cd - change directory
	// else if (!strcmp(cmd, "cd")) {
	// 	cd(flag1, flag2, argument);
	// }

	// //pwd - print working directory
	// else if (!strcmp(cmd, "pwd")) {
	// 	pwd(flag1, flag2);
	// }

	// //echo 
	// else if (!strcmp(cmd, "echo")) {
	// 	echo(flag1, flag2, argument);
	// }

	// else if (!strcmp(cmd, "ls")) {
		
	// 	//Flags
	// 	int m = 0;
	// 	int i = 0;

	// 	//-m flag
	// 	if (!strcmp(flag1, "-m") || !strcmp(flag2, "-m")) {
	// 		m = 1;
	// 	}

	// 	//-i flag
	// 	if (!strcmp(flag1, "-i") || !strcmp(flag2, "-i")) {
	// 		i = 1;
	// 	}

	// 	char tempDir[100];
	// 	getcwd(tempDir, 100);

	// 	const char* dir = tempDir;
		
	// 	pid_t pid;
	// 	pid = fork();

	// 	if (pid < 0) {
	// 		printf("[!] Some error occurred while executing this command");
	// 	}
	// 	else if (pid == 0) {
	// 		if (m && i) {
	// 			execl(strcat(p, "/ls"), "-m", "-i", dir, 0);
	// 		}
	// 		else if (m && !i) {
	// 			execl(strcat(p, "/ls"), "-m", "NO", dir, 0);
	// 		}
	// 		else if (!m && i) {
	// 			execl(strcat(p, "/ls"), "NO", "-i", dir, 0);
	// 		}
	// 		else if (!m && !i) {
	// 			execl(strcat(p, "/ls"), "NO", "NO", dir, 0);
	// 		}
	// 		else {
	// 			printf("[!] Invalid flag(s) entered.\n");
	// 			exit(-1);
	// 		}

	// 		exit(0);
	// 	}
	// 	else {
	// 		wait(NULL);
	// 	}
	// }

	// else if (!strcmp(cmd, "date")) {

	// 	int u = 0;
	// 	int r = 0;

	// 	if (!strcmp(flag1, "-u") || !strcmp(flag2, "-u")) {
	// 		u = 1;
	// 	}

	// 	if (!strcmp(flag1, "-R") || !strcmp(flag2, "-R")) {
	// 		r = 1;
	// 	}

	// 	if (strcmp(flag1, "\0") && strcmp(flag1, "-u") && strcmp(flag1, "-R")) {
	// 		printf("[!] Invalid flag(s) entered.\n");
	// 		return -1;
	// 	}
	// 	else if (strcmp(flag2, "\0") && strcmp(flag2, "-u") && strcmp(flag2, "-R")) {
	// 		return -1;
	// 	}

	// 	pid_t pid;
	// 	pid = fork();

	// 	if (pid < 0) {
	// 		printf("[!] Some error occurred while executing this command\n");
	// 	}
	// 	else if (pid == 0) {
	// 		if (u && r) {
	// 			execl(strcat(p, "/date"), "-u", "-R", 0);
	// 		}
	// 		else if (u && !r) {
	// 			execl(strcat(p, "/date"), "-u", "\0", 0);
	// 		}
	// 		else if (r && !u) {
	// 			execl(strcat(p, "/date"), "\0", "-R", 0);
	// 		}
	// 		else if (!r && !u) {
	// 			execl(strcat(p, "/date"), "\0", "\0", 0);
	// 		}

	// 	}
	// 	else {
	// 		wait(NULL);
	// 	}
	// }

	// else if (!strcmp(cmd, "rm")) {
	// 	int f = 0;
	// 	int i = 0;

	// 	const char* fileName = argument[0];

	// 	if (!strcmp(flag1, "-i") || !strcmp(flag2, "-i")) {
	// 		i = 1;
	// 	}

	// 	if (!strcmp(flag1, "-f") || !strcmp(flag2, "-f")) {
	// 		f = 1;
	// 	}

	// 	pid_t pid;
	// 	pid = fork();

	// 	if (pid < 0) {
	// 		printf("[!] Some error occurred while executing this command\n");
	// 	}
	// 	else if (pid == 0) {
	// 		if (f && i) {
	// 			execl(strcat(p, "/rm"), "-f", "-i", fileName, 0);
	// 		}
	// 		else if (f && !i) {
	// 			execl(strcat(p, "/rm"), "-f", "\0", fileName, 0);
	// 		}
	// 		else if (i && !f) {
	// 			execl(strcat(p, "/rm"), "\0", "-i", fileName, 0);
	// 		}
	// 		else {
	// 			execl(strcat(p, "/rm"), "\0", "\0", fileName, 0);
	// 		}
	// 	}
	// 	else {
	// 		wait(NULL);
	// 	}


	// }

	// else if (!strcmp(cmd, "cat")) {

	// 	int e = 0;
	// 	int t = 0;


	// 	if (!strcmp(flag1, "-E") || !strcmp(flag2, "-E")) {
	// 		e = 1;
	// 	}
	// 	if (!strcmp(flag1, "-T") || !strcmp(flag2, "-T")) {
	// 		t = 1;
	// 	}

	// 	const char* fileName = argument[0];
		
	// 	pid_t pid;
	// 	pid = fork();

	// 	if (pid < 0) {
	// 		printf("[!] Some error occurred while executing this command\n");
	// 		return -1;
	// 	}

	// 	else if (pid == 0) {
	// 		if (e && t) {
	// 			execl(strcat(p, "/cat"), "-E", "-T", fileName, 0);
	// 		}
	// 		else if (e && !t) {
	// 			execl(strcat(p, "/cat"), "-E", "\0", fileName, 0);
	// 		}
	// 		else if (!e && t) {
	// 			execl(strcat(p, "/cat"), "\0", "-T", fileName, 0);
	// 		}
	// 		else {
	// 			execl(strcat(p, "/cat"), "\0", "\0", fileName, 0);
	// 		}
	// 	}

	// 	else {
	// 		wait (NULL);
	// 	}
	// }

	// else if (!strcmp(cmd, "mkdir")) {
	// 	int m = 0;
	// 	int pFlag = 0;



	// 	if (!strcmp(flag1, "-m") || !strcmp(flag2, "-m")) {
	// 		m = 1;
	// 	}
	// 	if (!strcmp(flag1, "-p") || !strcmp(flag2, "-p")) {
	// 		pFlag = 1;
	// 	}

	// 	const char* fileName = argument[0];		

	// 	const char* modeArg = "777";
		
	// 	pid_t pid;
	// 	pid = fork();

	// 	if (pid < 0) {
	// 		printf("[!] Some error occurred while executing this command\n");
	// 		return -1;
	// 	}

	// 	else if (pid == 0) {
	// 		if (m && pFlag) {
	// 			execl(strcat(p, "/mkdir"), "-m", "-p", fileName, modeArg, 0);
	// 		}
	// 		else if (m && !pFlag) {
	// 			execl(strcat(p, "/mkdir"), "-m", "\0", fileName, modeArg, 0);
	// 		}
	// 		else if (!m && pFlag) {
	// 			execl(strcat(p, "/mkdir"), "\0", "-p", fileName, "777", 0);
	// 		}
	// 		else {
	// 			execl(strcat(p, "/mkdir"), "\0", "\0", fileName, "777", 0);
	// 		}
	// 		exit(0);
	// 	}

	// 	else {
	// 		wait (NULL);
	// 	}
	// }

	// //unknown command
	// else {
	// 	printf("[!] Unknown command %s entered\n", cmd);
	// }

	return 0;
}

void command(char cmd[], char p[]) {
	fgets(cmd, maxChar, stdin);	//fgets is better than scanf since scanf stops reading input when it encouters whitespace
	char* temp = strtok(cmd, " \n\t");
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
			temp = strtok(NULL, " \n\t");
		}
		splitCounter++;
	}

	executeCommand(split, splitLen, p);
}

void shell(char p[]) {
	char cmd[maxChar];
	while (1) {
		char dir[100];
		getcwd(dir, 100);
	
		printf("[%s]> ", dir);
		command(cmd, p);
	}
}

int main() {
	char pathForExternalCmd[100];
	getcwd(pathForExternalCmd, 100);
	shell(pathForExternalCmd);
	return 0;
}