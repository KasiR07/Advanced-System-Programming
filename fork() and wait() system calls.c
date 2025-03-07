#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
	int pid = fork();

	if (pid == 0) {
	    
		// Child process...............................................................................
		int option;
		printf("Enter option (1, 2, 3): ");
		int result = scanf("%d", &option); // Check if input is valid

		if (result != 1) {
			printf("Invalid input (not a number)\n");
			exit(1); // Explicitly exit for invalid input
		}

		switch(option) {
		case 1:
			printf("Child PID: %d, PPID: %d\n", getpid(), getppid()); //user input 1
			break; // Exits implicity as mentioned in the question (without using exit)
		case 2:
			printf("Child PID: %d, PPID: %d\n", getpid(), getppid()); //user input 2
			exit(3); // Exit child if execl fails.
		case 3:
			for (int i = 0; i < 3; i++) {
				printf("Child PID: %d, PPID: %d\n", getpid(), getppid()); //user input 3
				sleep(1); //pausing this for a specified duration
			}
			int n = 30/0; // Division by zero (impossible and undefined)
			break;
		default:
			printf("Invalid option\n");
			exit(1);
		}
		return 0; // Implicit exit for case 1
	} else {
		// Parent process.....................................................................................
		
		int status;
		wait(&status);

		if (WIFEXITED(status)) {
			printf("Normal Exit and the exit status is: %d\n", WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("Child terminated by signal: %d\n", WTERMSIG(status));
		}
	}

	return 0;
}



