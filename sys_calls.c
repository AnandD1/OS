#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Function to handle the process creation and execution
void createChildProcess() {
    // Information about the child process
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    // Initialize the structure
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create the child process (example: running the current program again)
    if (!CreateProcess(
            NULL,               // No module name (use command line)
            "sys_calls.exe",     // Command line
            NULL,               // Process handle not inheritable
            NULL,               // Thread handle not inheritable
            FALSE,              // Set handle inheritance to FALSE
            0,                  // No creation flags
            NULL,               // Use parent's environment block
            NULL,               // Use parent's starting directory
            &si,                // Pointer to STARTUPINFO structure
            &pi)                // Pointer to PROCESS_INFORMATION structure
    ) {
        printf("CreateProcess failed (%d)\n", GetLastError());
        return;
    }

    // Wait for the child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

// Main function to demonstrate system calls
int main() {
    // Get and print the current process ID
    printf("Current Process ID: %d\n", GetCurrentProcessId());

    // Create a child process and wait for it to complete
    createChildProcess();

    // Sleep for 5 seconds (Windows equivalent of sleep)
    printf("Sleeping for 5 seconds...\n");
    Sleep(5000); // Sleep in milliseconds

    // Get and print the parent process ID
    printf("Parent Process ID: %d\n", GetCurrentProcessId());

    return 0;
}
