#include <stdio.h>    // This lets us print things
#include <stdlib.h>   // This gives us exit() function
#include <unistd.h>   // This gives us fork() function
#include <sys/wait.h> // This gives us wait() function

int main() {
    
    int child1;     // for first child
    int child2;     // for second child
    int grandson1;  // for first grandchild
    int grandson2;  // for second grandchild
    int status;     // to check if processes ended properly

    // STEP 1: Create first child
    printf("\nStarting the program...\n");
    child1 = fork();  // fork() creates a copy of our program

    // Check if fork worked for first child
    if (child1 < 0) {
        printf("Couldn't create first child\n");
        exit(1);
    }

    // If we're in the first child process
    if (child1 == 0) {
        printf("Hello from first child!\n");
        
        // Now first child creates its own child (grandson1)
        grandson1 = fork();

        if (grandson1 < 0) {
            printf("Couldn't create first grandson\n");
            exit(1);
        }

        if (grandson1 == 0) {
            // This is grandson1's code
            printf("from first grandson!\n");
            
            // Try to change directory to GC1
            if (chdir("./chapters5/GC1") < 0) {
                printf("Couldn't find GC1 directory!\n");
                exit(1);
            }
            
            // List files in the directory
            printf("Listing files in GC1:\n");
            system("ls -l");
            exit(0);
        } else {
            // First child waits for its child (grandson1)
            printf("C1 is waiting for GC1\n");
            wait(&status);
            exit(0);
        }
    }

    // STEP 2: Create second child
    child2 = fork();

    if (child2 < 0) {
        printf("Couldn't create second child\n");
        exit(1);
    }

    if (child2 == 0) {
        printf("from second child!\n");
        
        // Second child creates its child (grandson2)
        grandson2 = fork();

        if (grandson2 < 0) {
            printf("Couldn't create second grandson\n");
            exit(1);
        }

        if (grandson2 == 0) {
            // This is grandson2's code
            printf("from second grandson!\n");
            
            // Try to change directory to GC2
            if (chdir("./chapters5/GC2") < 0) {
                printf("Couldn't find GC2 directory!\n");
                exit(1);
            }
            
            // List files in the directory
            printf("Listing files in GC2:\n");
            system("ls -l");
            exit(0);
        } else {
            // Second child waits for its child (grandson2)
            printf("C2 waiting for GC2\n");
            wait(&status);

            // Check how grandson2 ended
            if (WIFEXITED(status)) {
                printf("GC2 exited normally with status %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("GC2 was terminated by signal %d\n", WTERMSIG(status));
            }
            exit(0);
        }
    }

    // STEP 3: Parent waits for both children to finish
    printf("Parent is waiting for children...\n");
    wait(&status);  // wait for first child
    wait(&status);  // wait for second child
    printf("Parent: All child processes completed\n");

    return 0;
}