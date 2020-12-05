#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <sys/wait.h>

int main() {
    int f, status;

    // First Fork
    printf("Parent PID [%d]\n\nBefore first forking\n", getpid());
    f = fork();

    // Second Fork
    if(f) {
        printf("Before second forking\n\n");
        f = fork();
    }

    if(f) {
        // parent behavior

        int childPID = wait(&status);
       
        printf("Child with PID [%d] has completed and woke up after [%d] seconds\n", childPID, WEXITSTATUS(status));
       
        printf("Parent is now done\n\n");
        return 0;
    } else {
        // child behavior

        int childPID = getpid();
        srand(childPID + time(NULL));

        printf("Forked Child with PID [%d]\n", childPID);
        
        int stime = (rand() % 9) + 2;
        sleep(stime);
        
        printf("\nChild with PID [%d] has awoken\n", childPID);
        return stime;
    }
}