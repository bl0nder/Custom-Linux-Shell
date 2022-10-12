#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

const int maxChar = 1000;

void echo_u(char* split) {
	while (split != NULL) {
		
		int counter = 0;
		while (split[counter]) {
			if (split[counter] >= 'a' && split[counter] <= 'z') {
				split[counter] = split[counter] - 32;
			}
			counter++;
		}

		if (split[strlen(split)-1] != '\n')  {	
			printf("%s ", split);
		}
		else {
			printf("\n");
		}
		split = strtok(NULL, " ");
	}
}

void echo(char* split, char flag1[], char flag2[]) {

	//flags -> Upper case (-u) & Meme case (-m)
	int uFlag = 0;
	int mFlag = 0;
	
	//Detect first flag
	if (strlen(flag1) != 0) {
		if (strcmp(flag1, "-u") == 0) {
			printf("-u flag detected as first flag\n");
			uFlag = 1;
			echo_u(split);
		}
		else if (strcmp(flag1, "-m") == 0) {
			printf("-m flag detected as first flag\n");
			mFlag = 1;
		}
		else {
			printf("Unrecognised flag %s\n", flag1);
		}

		//Detect second flag - Second flag can exist only if first flag exists
		if (strlen(flag2) != 0) {
			if (strcmp(flag2, "-u") == 0) {
				printf("-u flag detected as second flag\n");
				uFlag = 1;
			}
			else if (strcmp(flag2, "-m") == 0) {
				printf("-m flag detected as second flag\n");
				mFlag = 1;
			}
			else {
				printf("Unrecognised flag %s\n", flag2);
			}
		}
		else {
			printf("Second flag is NULL\n");
		}

	}

	//No flags - print split to console as it is without modification
	else {
		//Need to run while loop since input string might have whitespace 
		while (split != NULL) {
			//Handling newline character in last split since that will get printed with a space after it
			//If newline is detected => current split is last split
			//=> Print last split without whitespace after it
			if (split[strlen(split)-1] != '\n')  {
				printf("%s ", split);
			}
			else {
				printf("\n", split);
			}
			split = strtok(NULL, " ");
		}
	}
}

void executeCommand(char cmd[], char* split) {
	
	char flag1[10] = "\0";
	char flag2[10] = "\0";
		

	while(split!=NULL && (strlen(flag1) == 0 || strlen(flag2) == 0)) {
		//All flags start with a hyphen
		if (split[0] == '-') {
			
			//Remove newline character from end of split (if it exists)
			if (split[strlen(split)-1] == '\n') {
				split[strlen(split)-1] = '\0';
			}


			//Check whether this flag is flag1 or flag2 by checking if length of flag1 is 0 or not
			if (strlen(flag1) == 0) {
				//Copy -x (x can be anything) to flag1
				strcpy(flag1, split);
			}
			
			else {
				//Copy -x (x can be anything) to flag2
				strcpy(flag2, split);
			}
			
			//Go to next split
			split = strtok(NULL, " ");
		}

		else {
			break;
		}
	}

	//Exit shell
	if (strcmp(cmd, "exit") == 0) {
		exit(0);
	}

	//cd - change directory
	else if (strcmp(cmd, "cd") == 0) {
		printf("You're trying to change directory!\n");
	
	}

	//pwd - path to working directory
	else if (strcmp(cmd, "pwd") == 0) {
		printf("You're trying to print the path to working directory!\n");
	}

	//echo 
	else if (strcmp(cmd, "echo") == 0) {
		echo(split, flag1, flag2);
	}

	//unknown command
	else {
		printf("Unknown command\n");
		printf("%s\n", cmd);
	}
}

void command(char cmd[]) {
	fgets(cmd, maxChar, stdin);	//fgets is better than scanf since scanf stops reading input when it encouters whitespace
	char *split = strtok(cmd, " ");
	char mainCmd[20] = "\0";
	// char flag1[20] = "\0";
	// char flag2[20] = "\0";

	//Removing trailing newline character
	if (strlen(cmd) > 0 && cmd[strlen(cmd)-1] == '\n') {
		cmd[strlen(cmd)-1] = '\0';
	}

	if (strlen(mainCmd) == 0) {
		strcpy(mainCmd, split);
	}

	// while (split != NULL) {
	// 	if (strlen(mainCmd) == 0) {
	// 		strcpy(mainCmd, split);
	// 	}
	// 	// else {
	// 	// 	if (strlen(flag1) == 0) {
	// 	// 		strcpy(flag1, split);
	// 	// 	}
	// 	// 	else {
	// 	// 		strcpy(flag2, split);
	// 	// 	}
	// 	// }
	// 	split = strtok(NULL, " ");
	// }
 
	// printf("Main command: %s\n", mainCmd);
	// printf("Flags: %s %s\n", flag1, flag2);
	split = strtok(NULL, " ");
	
	executeCommand(mainCmd, split);
}

void shell() {
	char cmd[maxChar];
	while (1) {
		printf("bl0nderShell> ");
		command(cmd);
	}
}

int main() {
	shell();
	return 0;
}