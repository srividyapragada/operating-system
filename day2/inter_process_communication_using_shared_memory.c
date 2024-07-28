#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    HANDLE hMapFile;
    LPVOID lpMapAddress;
    char buff[100];

    // Creating or opening a named shared memory object
    hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, "Local\\MySharedMemory");
    if (hMapFile == NULL) {
        perror("CreateFileMapping");
        exit(EXIT_FAILURE);
    }

    // Mapping the shared memory object into the process's address space
    lpMapAddress = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 1024);
    if (lpMapAddress == NULL) {
        perror("MapViewOfFile");
        CloseHandle(hMapFile);
        exit(EXIT_FAILURE);
    }

    printf("Process attached at %p\n", lpMapAddress);

    // Reading data from the user
    printf("Enter some data to write to shared memory\n");
    read(0, buff, 100);

    // Copying data to shared memory
    strcpy((char*)lpMapAddress, buff);

    printf("You wrote: %s\n", (char*)lpMapAddress);

    // Unmapping the shared memory object
    UnmapViewOfFile(lpMapAddress);

    // Closing the handle to the shared memory object
    CloseHandle(hMapFile);

    return 0;
}
