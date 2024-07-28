#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_info;

    // Open the directory
    dir = opendir("C:\\Users\\ravul\\Downloads\\collage detiles\\R.collage\\operating system sem-6\\os lab\\DAY4\\Q25");
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Get file information
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", "C:\\Users\\ravul\\Downloads\\collage detiles\\R.collage\\operating system sem-6\\os lab\\DAY4\\Q25", entry->d_name);
        if (stat(filepath, &file_info) == -1) {
            perror("Error getting file info");
            exit(EXIT_FAILURE);
        }

        // Print file information
        printf("Name: %s\n", entry->d_name);
        printf("Inode number: %lu\n", (unsigned long) file_info.st_ino);
        printf("Size: %lld bytes\n", (long long) file_info.st_size);
        printf("Mode: %lo\n", (unsigned long) file_info.st_mode);
        printf("------------------------------\n");
    }

    // Close the directory
    closedir(dir);

    return 0;
}
