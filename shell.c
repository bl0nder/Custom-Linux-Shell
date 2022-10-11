#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

const int maxChar = 1000;

void command(char cmd[]) {
	fgets(cmd, maxChar, stdin);	//fgets is better than scanf since scanf stops reading input when it encouters whitespace
	// char *test = strtok(cmd, " ");

	if (cmd[strlen(cmd)-1] == '\n') {
		printf("Last element is a newline :(\n");
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