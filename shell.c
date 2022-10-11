#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void command(char* cmd[]) {
	fgets(cmd, sizeof(cmd), stdin);	//gets is better than scanf since scanf stops reading input when it encouters whitespace
	printf("Here is what you entered: %s", cmd);
}

void shell() {
	char* cmd[10];	 
	int counter = 0;
	while (counter < 0) {
		printf("bl0nderShell> ");
		command(cmd);
		counter++;
	}
}

int main() {
	shell();
	return 0;
}