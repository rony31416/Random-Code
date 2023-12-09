#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#define N 3   // Number of rows in matrix X
#define M 3   // Number of columns in matrix X and rows in matrix Y
#define P 3   // Number of columns in matrix Y

// Function to display a matrix
void displayMatrix(int matrix[N][P], int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to perform matrix multiplication for a specific row
void multiplyRow(int rowNum, int matrixX[N][M], int matrixY[M][P], int matrixZ[N][P]) {
    for (int j = 0; j < P; j++) {
        matrixZ[rowNum][j] = 0;
        for (int k = 0; k < M; k++) {
            matrixZ[rowNum][j] += matrixX[rowNum][k] * matrixY[k][j];
        }
    }
}

int main() {
    int matrixX[N][M];
    int matrixY[M][P];
    int matrixZ[N][P];

    printf("Enter values for Matrix X (%dx%d):\n", N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &matrixX[i][j]);
        }
    }

    printf("Enter values for Matrix Y (%dx%d):\n", M, P);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            scanf("%d", &matrixY[i][j]);
        }
    }

    printf("Matrix X:\n");
    displayMatrix(matrixX, N, M);

    printf("\nMatrix Y:\n");
    displayMatrix(matrixY, M, P);

    // Shared memory key and identifiers
    key_t shm_key = IPC_PRIVATE;
    int shm_id;

    // Create shared memory segment for the result matrix Z
    if ((shm_id = shmget(shm_key, sizeof(matrixZ), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment to the parent process
    int (*sharedMatrixZ)[P] = shmat(shm_id, NULL, 0);

    clock_t start_time = clock();  // Record start time

    int numProcesses = N;  // Number of child processes

    for (int i = 0; i < numProcesses; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            multiplyRow(i, matrixX, matrixY, sharedMatrixZ);
            exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes to complete
    for (int i = 0; i < numProcesses; i++) {
        wait(NULL);
    }

    clock_t end_time = clock();  // Record end time

    // Calculate and display the resulting matrix Z
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nResultant Matrix Z:\n");
    displayMatrix(sharedMatrixZ, N, P);

    printf("\nExecution time: %f seconds\n\n", execution_time);

    // Detach and remove shared memory segment
    shmdt(sharedMatrixZ);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}

