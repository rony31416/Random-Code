#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define N 3

int A[N][N] = {{10, 29, 3}, {4, 25, 6}, {71, 48, 9}};
int B[N][N] = {{9, 87, 7}, {69, 5, 4}, {3, 2, 91}};
int C[N][N];

volatile sig_atomic_t child_done = 0;  // Flag to indicate child process completion

// Signal handler for child completion
void child_complete_handler(int signum) {
    if (signum == SIGCHLD) {
        child_done = 1;
    }
}

// Function to perform matrix multiplication in a given row
void multiply_row(int row) {
    for (int col = 0; col < N; ++col) {
        C[row][col] = 0;
        for (int i = 0; i < N; ++i) {
            C[row][col] += A[row][i] * B[i][col];
        }
    }
}

int main() {
    // Register signal handler for child completion
    signal(SIGCHLD, child_complete_handler);

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // This is the child process

        // Perform matrix multiplication in the first row
        multiply_row(0);

        // Notify the parent process about completion
        kill(getppid(), SIGCHLD);

        exit(EXIT_SUCCESS);
    } else {
        // This is the parent process

        // Wait for the child process to complete
        while (!child_done) {
            // Wait for the signal
            sleep(1);
        }

        // Perform matrix multiplication in the second row
        multiply_row(1);

        // Display the result matrix
        printf("Result matrix C:\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }

        // Wait for the child process to finish completely
        wait(NULL);
    }

    return 0;
}
