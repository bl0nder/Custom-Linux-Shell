#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

const int maxChar = 1000;

void command(char cmd[]) {
	fgets(cmd, maxChar, stdin);	//fgets is better than scanf since scanf stops reading input when it encouters whitespace
	char *split = strtok(cmd, " ");
	char mainCmd[20];
	char flags[20][20];
	int flagCounter = 0;

	// if (cmd[strlen(cmd)-1] == '\n') {
	// 	cmd[strlen(cmd)-1] = '\0';
	// }


	while (split != NULL) {
		if (strlen(mainCmd) == 0) {
			strcpy(mainCmd, split);
		}
		else {
			strcpy(flags[flagCounter], split);
			flagCounter++;
		}
		split = strtok(NULL, " ");
	}

	printf("Main command: %s\n", mainCmd);
	printf("Flags: %s\n", flags);
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