#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    // Variable declarations for file operations
    int fd;
    char buff1[21]; 
    ssize_t bytes_read, bytes_written;
    off_t offset;

    // Create new file with read-write permissions
    umask(0);
    fd = open("lab5.txt", O_RDWR | O_CREAT | O_TRUNC, 0755);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    // STEP 1: Write initial text: "Welcome to COMP 8567, University of Windsor"
    char *initial_str = "Welcome to COMP 8567, University of Windsor";
    bytes_written = write(fd, initial_str, strlen(initial_str));
    if (bytes_written == -1) {
        perror("initial write failed");
        close(fd);
        return 1;
    }

    // STEP 2: Save the text after position 22 (after "COMP 8567")
    offset = lseek(fd, 22, SEEK_SET); 
    bytes_read = read(fd, buff1, sizeof(buff1)); 
    if (bytes_read != sizeof(buff1)) {
        perror("read failed");
        close(fd);
        return 1;
    }

    // STEP 3: Insert "School of Computer Science" and restore saved text
    offset = lseek(fd, 22, SEEK_SET);
    char *school_str = "School of Computer Science, ";
    bytes_written = write(fd, school_str, strlen(school_str));
    if (bytes_written == -1) {
        perror("school write failed");
        close(fd);
        return 1;
    }
    bytes_written = write(fd, buff1, sizeof(buff1)); 
    if (bytes_written == -1) {
        perror("buff1 write failed");
        close(fd);
        return 1;
    }

    // STEP 4: Add hyphen between COMP and 8567
    offset = lseek(fd, 15, SEEK_SET); 
    bytes_written = write(fd, "-", 1);
    if (bytes_written == -1) {
        perror("hyphen write failed");
        close(fd);
        return 1;
    }

    // STEP 5: Add "Winter 2025" at the end with 12 byte offset
    offset = lseek(fd, 12, SEEK_END);
    char *winter_str = "Winter 2025";
    bytes_written = write(fd, winter_str, strlen(winter_str));
    if (bytes_written == -1) {
        perror("winter write failed");
        close(fd);
        return 1;
    }

    // STEP 6: Replace all null characters with spaces
    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("lseek to SEEK_END failed");
        close(fd);
        return 1;
    }
    lseek(fd, 0, SEEK_SET);
    char *buffer = malloc(file_size);
    if (!buffer) {
        perror("malloc failed");
        close(fd);
        return 1;
    }
    bytes_read = read(fd, buffer, file_size);
    if (bytes_read != file_size) {
        perror("read for null replacement failed");
        free(buffer);
        close(fd);
        return 1;
    }
    for (int i = 0; i < file_size; i++) {
        if (buffer[i] == '\0') {
            buffer[i] = ' ';
        }
    }
    lseek(fd, 0, SEEK_SET);
    bytes_written = write(fd, buffer, file_size);
    if (bytes_written != file_size) {
        perror("write after null replacement failed");
        free(buffer);
        close(fd);
        return 1;
    }
    free(buffer);

    close(fd);
    return 0;
}