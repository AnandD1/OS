#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lruPageReplacement(int pages[], int n, int frameSize) {
    int frames[frameSize];  // Array to simulate frames in memory
    int time[frameSize];    // Array to store last used times of frames
    int pageFaults = 0;     // Counter for page faults
    int isInFrame, pos;     // Flags and variables for tracking
    int counter = 0;        // Counter to track time

    // Initialize frames and time arrays
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("Reference String\tFrames\n");

    // Traverse the reference string
    for (int i = 0; i < n; i++) {
        isInFrame = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == pages[i]) {
                isInFrame = 1;
                time[j] = counter++; // Update usage time
                break;
            }
        }

        // If the page is not in the frame
        if (!isInFrame) {
            if (i < frameSize) {
                // Fill frames initially
                frames[i] = pages[i];
                time[i] = counter++;
            } else {
                // Find the least recently used page
                pos = findLRU(time, frameSize);
                frames[pos] = pages[i];
                time[pos] = counter++;
            }
            pageFaults++; // Increment page fault counter
        }

        // Display the frames after each page reference
        printf("%d\t\t\t", pages[i]);
        for (int k = 0; k < frameSize; k++) {
            if (frames[k] != -1) {
                printf("%d ", frames[k]);
            } else {
                printf("- "); // Empty frame
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);
    int frameSize;

    printf("Enter the number of frames: ");
    scanf("%d", &frameSize);

    lruPageReplacement(referenceString, n, frameSize);

    return 0;
}
