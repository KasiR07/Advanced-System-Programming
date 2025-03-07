#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t c1_pid, c2_pid, gc_pid;
    int status;
    
    printf("Main process started. Main PID: %d\n", getpid());
    
    c1_pid = fork(); // First fork to create C1
    
    if (c1_pid < 0) {
        perror("First fork failed"); // if the fork fails
        exit(1);
    }
    
    if (c1_pid == 0) {
        // C1 process
        printf("C1 process created. C1 PID: %d, Parent PID: %d\n", 
               getpid(), getppid());
        
        gc_pid = fork(); // Second fork to create GC
        
        if (gc_pid < 0) {
            perror("Second fork failed");
            exit(1);
        }
        
        if (gc_pid == 0) {
            // GC process
            printf("GC process created. GC PID: %d, Parent PID: %d\n", 
                   getpid(), getppid());
            
            sleep(5); // Sleep for 5 seconds
            
            printf("This is from GC and this is my PID %d and PPID %d\n", 
                   getpid(), getppid());
            
            exit(0); // Exit properly instead of SIGSTOP
        }
        else {
            // C1 process continues
            waitpid(gc_pid, &status, 0); // Wait for GC to complete
            
            printf("This is from C1 and this is my PID %d and PPID %d\n", 
                   getpid(), getppid());
            
            exit(0); // Exit properly instead of SIGSTOP
        }
    }
    else {
        // Main process continues
        c2_pid = fork(); // Fork again to create C2
        
        if (c2_pid < 0) {
            perror("Second fork failed"); // if the fork fails
            exit(1);
        }
        
        if (c2_pid == 0) {
            // C2 process
            printf("C2 process created. C2 PID: %d, Parent PID: %d\n", 
                   getpid(), getppid());
            
            printf("This is from C2 and this is my PID %d and PPID %d\n", 
                   getpid(), getppid());
            
            exit(0); // Exit properly instead of SIGSTOP
        }
        else {
            // Main process continues
            sleep(6); // Wait to ensure child processes have time to run
            
            // Wait for child processes to complete
            waitpid(c1_pid, &status, 0);
            waitpid(c2_pid, &status, 0);
            
            printf("This is from Main and this is my PID %d and PPID %d\n", 
                   getpid(), getppid());
            
            return 0; // Exit the main process properly
        }
    }
}