#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	pid_t pid;

	pid = fork();

	const char* binaryPath = "/bin/ls";
	const char* arg1 = "-la";
	const char* arg2 = "/home/bl0nder/a0";

	if (pid < 0) {
		fprintf(stderr, "Error occurred :(");
		return 1;
	}

	else if (pid == 0) {
		printf("I am a child with ID %d\n", getpid());
		printf("My parent process has ID %d\n", getppid());
		execl(binaryPath, binaryPath, arg1, arg2, NULL);
	}

	else {
		wait(NULL);
		printf("Child complete!\n");
	}

	return 0;
}
