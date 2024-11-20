#include <stdio.h>

int findOptimal(int pages[], int n, int frames[], int frameSize, int currentIndex) {
    int farthest = -1, pos = -1;
    int found;

    for (int i = 0; i < frameSize; i++) {
        found = 0;

        // Check when the page will be referenced next
        for (int j = currentIndex + 1; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                found = 1;
                break;
            }
        }

        // If a page is not referenced again, choose it for replacement
        if (!found) {
            return i;
        }
    }

    // If all pages are referenced again, return the one used farthest in the future
    return (pos == -1) ? 0 : pos;
}

void optimalPageReplacement(int pages[], int n, int frameSize) {
    int frames[frameSize];
    int pageFaults = 0;
    int isInFrame;

    // Initialize frames to -1 (indicating empty)
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }

    printf("Reference String\tFrames\n");

    // Traverse the reference string
    for (int i = 0; i < n; i++) {
        isInFrame = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == pages[i]) {
                isInFrame = 1;
                break;
            }
        }

        // If the page is not in the frame
        if (!isInFrame) {
            if (i < frameSize) {
                // Fill frames initially
                frames[i] = pages[i];
            } else {
                // Find the optimal page to replace
                int pos = findOptimal(pages, n, frames, frameSize, i);
                frames[pos] = pages[i];
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

    optimalPageReplacement(referenceString, n, frameSize);

    return 0;
}
