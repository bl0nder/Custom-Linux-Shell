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
	char* path;
	// char* argv[100];
	char* flag1;
	char* flag2;
	char** argument;
	char* fileName;
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


void* lsT(void* passArgs) {
	// for (int i=0; i<1; i++) {
	// 	printf("%s\n", ((struct args *) passArgs) -> argv[i]);
	// }
	char str[2000];
	// strcat(str, ((struct args*) passArgs) -> path);
	// strcat(str, "/ls ");

	// for (int i=0; i<100; i++) {
	// 	strcat(str, ((struct args*) passArgs) -> argv[i]);
	// 	strcat(str, " ");
	// }

	int strLen;

	if (*((((struct args*)passArgs)) -> argument) != NULL) {
		strLen = snprintf(str, 2000, "%s%s %s %s %s", ((struct args*)passArgs) -> path, "/ls", ((struct args*)passArgs) -> flag1, ((struct args*)passArgs) -> flag2, *((((struct args*)passArgs)) -> argument));
	}
	else {
		strLen = snprintf(str, 2000, "%s%s %s %s", ((struct args*)passArgs) -> path, "/ls", ((struct args*)passArgs) -> flag1, ((struct args*)passArgs) -> flag2);
	}
	
	system((const char*) str);
	return NULL;
}

void* dateT(void* passArgs) {
	char str[2000];

	int strLen;

	if (*((((struct args*)passArgs)) -> argument) != NULL) {
		strLen = snprintf(str, 2000, "%s%s %s %s %s", ((struct args*)passArgs) -> path, "/date", ((struct args*)passArgs) -> flag1, ((struct args*)passArgs) -> flag2, *((((struct args*)passArgs)) -> argument));
	}
	else {
		strLen = snprintf(str, 2000, "%s%s %s %s", ((struct args*)passArgs) -> path, "/date", ((struct args*)passArgs) -> flag1, ((struct args*)passArgs) -> flag2);
	}
	
	system((const char*) str);
	return NULL;
}

void* catT(void* passArgs) {

	if (*(((struct args*) passArgs) -> argument) == NULL) {
		printf("[!] Enter the name of the file you want to read.\n");
	}
	// for (int i=0; i<1; i++) {
	// 	printf("%s\n", ((struct args *) passArgs) -> argv[i]);
	// }
	else {
		char str[2000];
		int strLen;
		strLen = snprintf(str, 2000, "%s%s %s %s %s", ((struct args*)passArgs) -> path, "/cat", ((struct args*)passArgs) -> flag1, ((struct args*)passArgs) -> flag2, *((((struct args*)passArgs)) -> argument));		
		system((const char*) str);
	}
	return NULL;
}

void* rmT(void* passArgs) {

	if (*(((struct args*) passArgs) -> argument) == NULL) {
		printf("[!] Enter the name of the file you want to remove.\n");
	}
	// for (int i=0; i<1; i++) {
	// 	printf("%s\n", ((struct args *) passArgs) -> argv[i]);
	// }
	else {
		char str[2000];
		int strLen;
		strLen = snprintf(str, 2000, "%s%s %s %s %s", ((struct args*)passArgs) -> path, "/rm", ((struct args*)passArgs) -> flag1, ((struct args*)passArgs) -> flag2, *((((struct args*)passArgs)) -> argument));		
		system((const char*) str);
	}
	return NULL;
}

void* mkdirT(void* passArgs) {

	if (*(((struct args*) passArgs) -> argument) == NULL) {
		printf("[!] Enter the name of the folder you want to create.\n");
		return NULL;
	}
	// for (int i=0; i<1; i++) {
	// 	printf("%s\n", ((struct args *) passArgs) -> argv[i]);
	// }
	const char* modeArg = "777";
	const char* folderName =  (((struct args*)passArgs) -> argument)[0];
	char str[2000];
	int strLen;
	strLen = snprintf(str, 2000, "%s%s %s %s %s %s", ((struct args*)passArgs) -> path, "/mkdir", ((struct args*)passArgs) -> flag1, ((struct args*)passArgs) -> flag2, folderName, modeArg);		
	system((const char*) str);
	
	return NULL;
}


void threadExecute(char cmd[], char flag1[], char flag2[], char* argument[], char p[]) {
	pthread_t t;

	struct args* passArgs = (struct args*) malloc (sizeof(struct args));

	// for (int i=0; i<100; i++) {
	// 	passArgs -> path[i] = p[i];
	// }

	// for (int i=0; i<splitLen; i++) {
	// 	passArgs -> argv[i] = split[i];
	// }

	passArgs -> path = p;
	
	if (flag1[0] == '\0') {
		passArgs -> flag1 = "NO";
	}
	else {
		passArgs -> flag1 = flag1;
	}
	
	if (flag2[0] == '\0') {
		passArgs -> flag2 = "NO";
	}
	else {
		passArgs -> flag2 = flag2;
	}

	if (argument == NULL) {
		passArgs -> argument = NULL;
	}
	else {
		passArgs -> argument = argument;
	}


	int test;

	if (!strcmp(cmd, "ls&t")) {
		test = pthread_create(&t, NULL, lsT, (void *) passArgs);
		pthread_join(t, NULL);
	}
	else if (!strcmp(cmd, "cat&t")) {
		test = pthread_create(&t, NULL, catT, (void *) passArgs);
		pthread_join(t, NULL);
	}
	else if (!strcmp(cmd, "date&t")) {
		test = pthread_create(&t, NULL, dateT, (void *) passArgs);
		pthread_join(t, NULL);
	}
	else if (!strcmp(cmd, "rm&t")) {
		test = pthread_create(&t, NULL, rmT, (void *) passArgs);
		pthread_join(t, NULL);
	}
	else if (!strcmp(cmd, "mkdir&t")) {
		test = pthread_create(&t, NULL, mkdirT, (void *) passArgs);
		pthread_join(t, NULL);
	}
	else {
		printf("[!] Invalid command entered.\n");
	}

	free((void *) passArgs);
}

int executeCommand(char* split[], int splitLen, char p[]) {
	

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

	char f1[flagSize];
	char f2[flagSize];

	if (flag1[0] != '\0' && flag2[0] != '\0') {
		strcpy(f1, flag1);
		strcpy(f2, flag2);
	}
	else if (flag1[0] != '\0' && flag2[0] == '\0') {
		strcpy(f1, flag1);
		strcpy(f2, "NO");
	}
	else {
		strcpy(f1, "NO");
		strcpy(f2, "NO");
	}

	//Exit shell
	if (!strcmp(cmd, "exit")) {
		exit(0);
	}	

	int threadFlag = 0;
	int cmds = 0;
	for (int i=0; i<commandSize; i++) {
		// if (cmd[i] == '\0') {
		// 	cmds = i;
		// }
		if (cmd[i-2] == '&' && cmd[i-1] == 't' && cmd[i] == '\0') {
			threadFlag = 1;
		}
	}

	if (threadFlag) {
		threadExecute(cmd, f1, f2, argument, p);
		threadFlag = 0;
		printf("hello\n");
	}

	else {
		//cd - change directory
		if (!strcmp(cmd, "cd")) {
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
			
			// //Flags
			// int m = 0;
			// int i = 0;

			// //-m flag
			// if (!strcmp(flag1, "-m") || !strcmp(flag2, "-m")) {
			// 	m = 1;
			// }

			// //-i flag
			// if (!strcmp(flag1, "-i") || !strcmp(flag2, "-i")) {
			// 	i = 1;
			// }

			if (argument[0] != NULL) {
				printf("[!] This command does not take any arguments.\n");
				return -1;
			}

			char tempDir[100];
			getcwd(tempDir, 100);

			const char* dir = tempDir;
			
			pid_t pid;
			pid = fork();

			if (pid < 0) {
				printf("[!] Some error occurred while executing this command");
			}
			else if (pid == 0) {
				// if (m && i) {
				// 	execl(strcat(p, "/ls"), "-m", "-i", dir, 0);
				// }
				// else if (m && !i) {
				// 	execl(strcat(p, "/ls"), "-m", "NO", dir, 0);
				// }
				// else if (!m && i) {
				// 	execl(strcat(p, "/ls"), "NO", "-i", dir, 0);
				// }
				// else if (!m && !i) {
				// 	execl(strcat(p, "/ls"), "NO", "NO", dir, 0);
				// }
				// else {
				// 	printf("[!] Invalid flag(s) entered.\n");
				// 	exit(-1);
				// }

				char pathToBinary[100];
				snprintf(pathToBinary, 100, "%s%s", p, "/ls");

				execl(pathToBinary, pathToBinary, (const char*) f1, (const char*) f2, dir, 0);

				// if ((!strcmp(flag1, "-m") || !strcmp(flag2, "-m")) && (!strcmp(flag1, "-i") || !strcmp(flag2, "-i"))) {
				// 	execl(pathToBinary, pathToBinary, "-m", "-i", dir, 0);
				// }
				// else if ((!strcmp(flag1, "-m") || !strcmp(flag2, "-m")) && (flag1[0] == '\0' || flag2[0] == '\0')) {
				// 	execl(pathToBinary, pathToBinary, "-m", "NO", dir, 0);
				// }
				// else if ((!strcmp(flag1, "-i") || !strcmp(flag2, "-i")) && (flag1[0] == '\0' || flag2[0] == '\0')) {
				// 	execl(pathToBinary, pathToBinary, "-i", "NO", dir, 0);
				// }
				// else if (flag1[0] == '\0' && flag2[0] == '\0') {
				// 	execl(pathToBinary, pathToBinary, "NO", "NO", dir, 0);
				// }
				// else {
				// 	printf("[!] Invalid flag(s) entered.\n");
				// 	exit(-1);
				// }

				exit(0);
			}
			else {
				wait(NULL);
			}
		}

		else if (!strcmp(cmd, "date")) {

			if (argument[0] != NULL) {
				printf("[!] This command does not take any arguments.\n");
				return -1;
			}

			
			pid_t pid;
			pid = fork();

			if (pid < 0) {
				printf("[!] Some error occurred while executing this command\n");
			}
			else if (pid == 0) {

				char pathToBinary[100];
				snprintf(pathToBinary, 100, "%s%s", p, "/date");

				execl(pathToBinary, pathToBinary, (const char*) f1, (const char*) f2, 0);

			}
			else {
				wait(NULL);
			}
		}

		else if (!strcmp(cmd, "rm")) {

			if (argument[0] == NULL) {
				printf("[!] Enter the name of the file to be removed.\n");
				return -1;

			}
			const char* fileName = argument[0];

			pid_t pid;
			pid = fork();

			if (pid < 0) {
				printf("[!] Some error occurred while executing this command\n");
			}
			else if (pid == 0) {
				char pathToBinary[100];
				snprintf(pathToBinary, 100, "%s%s", p, "/rm");

				execl(pathToBinary, pathToBinary, (const char*) f1, (const char*) f2, fileName, 0);
			}
			else {
				wait(NULL);
			}


		}

		else if (!strcmp(cmd, "cat")) {

			if (argument[0] == NULL) {
				printf("[!] Enter the name of the file you want to read.\n");
				return -1;
			}

			const char* fileName = argument[0];
			
			pid_t pid;
			pid = fork();

			if (pid < 0) {
				printf("[!] Some error occurred while executing this command\n");
				return -1;
			}

			else if (pid == 0) {
				char pathToBinary[100];
				snprintf(pathToBinary, 100, "%s%s", p, "/cat");

				execl(pathToBinary, pathToBinary, (const char*) f1, (const char*) f2, fileName, 0);
			}

			else {
				wait (NULL);
			}
		}

		else if (!strcmp(cmd, "mkdir")) {
			// int m = 0;
			// int pFlag = 0;



			// if (!strcmp(flag1, "-m") || !strcmp(flag2, "-m")) {
			// 	m = 1;
			// }
			// if (!strcmp(flag1, "-p") || !strcmp(flag2, "-p")) {
			// 	pFlag = 1;
			// }

			if (argument[0] == NULL) {
				printf("[!] Enter the name of the file you want to read.\n");
				return -1;
			}

			const char* folderName = (const char*) argument[0];		

			const char* modeArg = "777";
			
			pid_t pid;
			pid = fork();

			if (pid < 0) {
				printf("[!] Some error occurred while executing this command\n");
				return -1;
			}

			else if (pid == 0) {
				char pathToBinary[100];
				snprintf(pathToBinary, 100, "%s%s", p, "/mkdir");

				execl(pathToBinary, pathToBinary, (const char*) f1, (const char*) f2, folderName, modeArg, 0);
				exit(0);
			}

			else {
				wait (NULL);
			}
		}

		//unknown command
		else {
			printf("[!] Unknown command %s entered\n", cmd);
		}
	}

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