#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int frameSize) {
    int frames[frameSize];  // Array to simulate frames in memory
    int front = 0;          // Pointer to the oldest page
    int pageFaults = 0;     // Counter for page faults
    int isInFrame;          // Flag to check if a page is already in the frame

    // Initialize frames to -1 (indicating empty)
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }

    printf("Reference String\tFrames\n");

    // Traverse the reference string
    for (int i = 0; i < n; i++) {
        isInFrame = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == pages[i]) {
                isInFrame = 1;
                break;
            }
        }

        // If the page is not in the frame, replace the oldest page
        if (!isInFrame) {
            frames[front] = pages[i];         // Replace page at front
            front = (front + 1) % frameSize; // Move front to the next position
            pageFaults++;                    // Increment page fault count
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

    fifoPageReplacement(referenceString, n, frameSize);

    return 0;
}
