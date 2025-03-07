#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

// Global variables to the track CTRL-C key presses
int ctrl_c_count = 0;          // To count the number of times CTRL-C is pressed
time_t last_ctrl_c_time = 0;   // To store the time when CTRL-C was last pressed

// Function to handle the SIGINT (CTRL-C) signal
void handle_sigint(int sig) {
    time_t curr_time = time(NULL);  // To get the current system time

    // If CTRL-C is pressed for the first time
    if (ctrl_c_count == 0) {
        ctrl_c_count = 1;                // Setting the counter to 1
        last_ctrl_c_time = curr_time; // To record the first time it was pressed
        printf("\nCTRL-C is detected. Press again within 4 seconds to exit.\n");
    } 
    else {
        // If CTRL-C is pressed again within 4 seconds
        if (curr_time - last_ctrl_c_time <= 4) {
            printf("\nCTRL-C is pressed twice within the 4 second interval. It is Exiting. \n");
            exit(0); 
        } 
        else {
            // To reset and treat it as a first press if the 4 second interval has passed
            ctrl_c_count = 1;                // To reset the counter
            last_ctrl_c_time = curr_time; // To record the new time
            printf("\nCTRL-C is detected. Press again within the 4 second interval to exit.\n");
        }
    }
}

int main() {
    // To et up the signal handler for SIGINT (CTRL-C)
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        printf("Error: Unable to set up signal handler.\n");
        return 1; // Return error if signal setup fails
    }

    // Display program instructions to the user
    printf("Program started. Instructions:\n");
    printf("- Pressing CTRL-C once will not exit the program.\n");
    printf("- Press CTRL-C twice within 4 seconds to exit.\n\n");

    // Infinite loop to keep the program running until user exits
    while (1) {
        printf("Waiting... (Press CTRL-C)\n");

        // Check if the 4-second timer has expired since the last CTRL-C press
        if (ctrl_c_count == 1 && time(NULL) - last_ctrl_c_time > 4) {
            ctrl_c_count = 0; // Reset the counter
            printf("(Timeout expired, press CTRL-C again to start over)\n");
        }

        sleep(1); // Pause execution for a 1 second interval before printing again
    }

    return 0; 
}
