#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

const int maxChar = 1000;

void executeCommand(char cmd[]) {
	if (strcmp(cmd, "cd") == 0) {
		printf("You're trying to change directory!\n");
	}
	else if (strcmp(cmd, "pwd") == 0) {
		printf("You're trying to print the path to working directory!\n");
	}
	else if (strcmp(cmd, "echo") == 0) {
		printf("You're trying to write something to the console!\n");
	}
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

	//Extracting main command name and passing to executeCommand()
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
 
	printf("Main command: %s\n", mainCmd);
	// printf("Flags: %s %s\n", flag1, flag2);

	executeCommand(mainCmd);
}

void shell() {
	char cmd[maxChar];	 
	int counter = 0;
	while (counter < 1) {
		printf("bl0nderShell> ");
		command(cmd);
		counter++;
	}
}

int main() {
	shell();
	return 0;
}