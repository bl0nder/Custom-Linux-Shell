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
// void echo_u(char* split[], int print) {
// 	for (int i=0; i<strlen(split); i++) {
// 		if (split[i] >= 'a' && split[i] <= 'z') {
// 			split[i] -= 32;
// 		}
// 	}

// 	if (print) {
// 		if (split[strlen(split)-1] != '\n')  {	
// 			printf("%s ", split);
// 		}
// 		else {
// 			printf("%s", split);
// 		}
// 	}
// }

// void echo_m(char* split[], int print) {
// 	int prevCase = 0;	//0 -> lower case; 1 -> upper case
	
// 	//printf("%s", split);
// 	//Toggle case
// 	for (int i=0; i<strlen(split); i++) {
// 		if (prevCase == 0) {
// 			if (split[i] >= 'a' && split[i] <= 'z') {
// 				split[i] -= 32;
// 			}		
// 			prevCase = 1;
// 		}
// 		else {
// 			if (split[i] >= 'A' && split[i] <= 'Z') {
// 				split[i] += 32;
// 			}
// 			prevCase = 0;
// 		}
	
// 	}

// 	if (print) {
// 		if (split[strlen(split)-1] != '\n')  {	
// 			printf("%s ", split);
// 		}
// 		else {
// 			printf("%s", split);
// 		}
// 	}

// }

void echo(char flag1[], char flag2[], char* argument[]) {

	//Vanilla - no flags
	if (flag1[0] == '\0' && flag2[0] == '\0') {
		for (int i=0; i<strlen(argument); i++) {
			printf("%s ", argument[i]);
		}
	}
	
	//Detect first flag
	// if (strlen(flag1) != 0) {
	// 	while (split != NULL) {
			
	// 		if (strcmp(flag1, "-u") == 0) {
	// 			echo_u(split, strlen(flag2) == 0);
	// 		}
	// 		else if (strcmp(flag1, "-m") == 0) {
	// 			echo_m(split, strlen(flag2) == 0);
	// 		}
	// 		else {
	// 			printf("Unrecognised flag %s\n", flag1);
	// 		}


	// 		//Detect second flag - Second flag can exist only if first flag exists
	// 		if (strlen(flag2) != 0 && strcmp(flag1, flag2) != 0) {
	// 			if (strcmp(flag2, "-u") == 0) {
	// 				echo_u(split, 1);
	// 			}
	// 			else if (strcmp(flag2, "-m") == 0) {
	// 				echo_m(split, 1);
	// 			}
	// 			else {
	// 				printf("Unrecognised flag %s\n", flag2);
	// 			}
	// 		}
	// 		split = strtok(NULL, " ");
	// 	}

	// }

	// //No flags - print split to console as it is without modification
	// else {
	// 	//Need to run while loop since input string might have whitespace 
	// 	while (split != NULL) {
	// 		//Handling newline character in last split since that will get printed with a space after it
	// 		//If newline is detected => current split is last split
	// 		//=> Print last split without whitespace after it
	// 		if (split[strlen(split)-1] != '\n')  {
	// 			printf("%s ", split);
	// 		}
	// 		else {
	// 			printf("%s", split);
	// 		}
	// 		split = strtok(NULL, " ");
	// 	}
	// }
}

void pwd(char flag1[], char flag2[], char* argument[]) {
	
	//Vanilla - no flags
	char dir[100];
	getcwd(dir, 100);
	printf("%s\n", dir);
}

// void cd(char* split[], char flag1[], char flag2[]) {
// 	const char* path = (const char*) split;

// 	int ans = chdir(path);

// 	if (ans == 0) {
// 		pwd(split, flag1, flag2);
// 	}
// 	else {
// 		printf("oh no\n");
// 	}
// }


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

	//Get flags from split and store them in flag1 and flag2
	if (splitLen > 2) {
		if (split[1][0] == '-' && strlen(split[1])==2) {
			strcpy(flag1, split[1]);
		}
		if (splitLen > 3 && split[2][0] == '-' && strlen(split[2])==2) {
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

	// while(split!=NULL && (strlen(flag1) == 0 || strlen(flag2) == 0)) {
	// 	//All flags start with a hyphen
	// 	if (split[0] == '-') {
			
	// 		//Remove newline character from end of split (if it exists)
	// 		if (split[strlen(split)-1] == '\n') {
	// 			split[strlen(split)-1] = '\0';
	// 		}


	// 		//Check whether this flag is flag1 or flag2 by checking if length of flag1 is 0 or not
	// 		if (strlen(flag1) == 0) {
	// 			//Copy -x (x can be anything) to flag1
	// 			strcpy(flag1, split);
	// 		}
			
	// 		else {
	// 			//Copy -x (x can be anything) to flag2
	// 			strcpy(flag2, split);
	// 		}
			
	// 		//Go to next split
	// 		split = strtok(NULL, " ");
	// 	}

	// 	else {
	// 		break;
	// 	}
	// }

	// //Exit shell
	// if (strcmp(cmd, "exit") == 0) {
	// 	exit(0);
	// }

	// //cd - change directory
	// else if (strcmp(cmd, "cd") == 0) {
	// 	printf("You're trying to change directory!\n");
	// 	cd(split, flag1, flag2);
		
	// }

	//pwd - print working directory
	if (strcmp(cmd, "pwd") == 0) {
		pwd(flag1, flag2, argument);
	}

	//echo 
	else if (strcmp(cmd, "echo") == 0) {
		echo(flag1, flag2, argument);
	}

	// //unknown command
	// else {
	// 	printf("Unknown command\n");
	// 	printf("%s\n", cmd);
	// }
}

void command(char cmd[]) {
	fgets(cmd, maxChar, stdin);	//fgets is better than scanf since scanf stops reading input when it encouters whitespace
	char* temp = strtok(cmd, " ");
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
		printf("bl0nderShell> ");
		command(cmd);
		break;
	}
}

int main() {
	shell();
	return 0;
}