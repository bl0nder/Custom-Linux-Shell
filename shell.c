#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

const int maxChar = 1000;

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

// void echo(char* split[], char flag1[], char flag2[]) {

// 	//flags -> Upper case (-u) & Meme case (-m)
	
// 	//Detect first flag
// 	if (strlen(flag1) != 0) {
// 		while (split != NULL) {
			
// 			if (strcmp(flag1, "-u") == 0) {
// 				echo_u(split, strlen(flag2) == 0);
// 			}
// 			else if (strcmp(flag1, "-m") == 0) {
// 				echo_m(split, strlen(flag2) == 0);
// 			}
// 			else {
// 				printf("Unrecognised flag %s\n", flag1);
// 			}


// 			//Detect second flag - Second flag can exist only if first flag exists
// 			if (strlen(flag2) != 0 && strcmp(flag1, flag2) != 0) {
// 				if (strcmp(flag2, "-u") == 0) {
// 					echo_u(split, 1);
// 				}
// 				else if (strcmp(flag2, "-m") == 0) {
// 					echo_m(split, 1);
// 				}
// 				else {
// 					printf("Unrecognised flag %s\n", flag2);
// 				}
// 			}
// 			split = strtok(NULL, " ");
// 		}

// 	}

// 	//No flags - print split to console as it is without modification
// 	else {
// 		//Need to run while loop since input string might have whitespace 
// 		while (split != NULL) {
// 			//Handling newline character in last split since that will get printed with a space after it
// 			//If newline is detected => current split is last split
// 			//=> Print last split without whitespace after it
// 			if (split[strlen(split)-1] != '\n')  {
// 				printf("%s ", split);
// 			}
// 			else {
// 				printf("%s", split);
// 			}
// 			split = strtok(NULL, " ");
// 		}
// 	}
// }

// void pwd(char* split[], char flag1[], char flag2[]) {
// 	char dir[100];

// 	getcwd(dir, 100);
// 	printf("%s\n", dir);
// }

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


// void executeCommand(char cmd[], char* split[]) {
	
// 	char flag1[10] = "\0";
// 	char flag2[10] = "\0";


// 	while(split!=NULL && (strlen(flag1) == 0 || strlen(flag2) == 0)) {
// 		//All flags start with a hyphen
// 		if (split[0] == '-') {
			
// 			//Remove newline character from end of split (if it exists)
// 			if (split[strlen(split)-1] == '\n') {
// 				split[strlen(split)-1] = '\0';
// 			}


// 			//Check whether this flag is flag1 or flag2 by checking if length of flag1 is 0 or not
// 			if (strlen(flag1) == 0) {
// 				//Copy -x (x can be anything) to flag1
// 				strcpy(flag1, split);
// 			}
			
// 			else {
// 				//Copy -x (x can be anything) to flag2
// 				strcpy(flag2, split);
// 			}
			
// 			//Go to next split
// 			split = strtok(NULL, " ");
// 		}

// 		else {
// 			break;
// 		}
// 	}

// 	//Exit shell
// 	if (strcmp(cmd, "exit") == 0) {
// 		exit(0);
// 	}

// 	//cd - change directory
// 	else if (strcmp(cmd, "cd") == 0) {
// 		printf("You're trying to change directory!\n");
// 		cd(split, flag1, flag2);
		
// 	}

// 	//pwd - print working directory
// 	else if (strcmp(cmd, "pwd") == 0) {
// 		pwd(split, flag1, flag2);
// 	}

// 	//echo 
// 	else if (strcmp(cmd, "echo") == 0) {
// 		echo(split, flag1, flag2);
// 	}

// 	//unknown command
// 	else {
// 		printf("Unknown command\n");
// 		printf("%s\n", cmd);
// 	}
// }

void command(char cmd[]) {
	fgets(cmd, maxChar, stdin);	//fgets is better than scanf since scanf stops reading input when it encouters whitespace
	char* temp = strtok(cmd, " ");
	char* split[100];

	int splitCounter = 0;
	
	while (splitCounter < 100) {
		if (temp == NULL) {
			split[splitCounter] = NULL;
		}
		else {
			split[splitCounter] = temp;
			temp = strtok(NULL, " \n");
		}
		splitCounter++;
	}

	for (int i=0; split[i] != NULL; i++) {
		printf("%s\n", split[i]);
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
	
	//executeCommand(split);
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