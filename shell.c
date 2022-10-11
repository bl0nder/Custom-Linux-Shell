#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

const int maxChar = 1000;

void command(char cmd[]) {
	fgets(cmd, maxChar, stdin);	//fgets is better than scanf since scanf stops reading input when it encouters whitespace
	// char *test = strtok(cmd, " ");

	for (int i=0; i<strlen(cmd); i++) {
		char c = cmd[i];

		char mainCmd[20] = "\0";
		char flags[20] = "\0";

		if (c == ' ' || c == '\n') {
			continue;
		}

		else {
			if (strlen(mainCmd) == 0) {
				mainCmd[strlen(mainCmd)-1] = c;
			}
			else {
				flags[strlen(flags)-1] = c;
			}
		}

		printf("Main command: %s\n", mainCmd);
		printf("Flags: %s\n", flags);

	}

	// while (test != NULL) {
	// 	if ((*test) != '\n') {
	// 		printf("%s ", test);
	// 		test = strtok(NULL, " ");	
	// 	}
	// }
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