// Реализовать программу, которая порождает процесс. Родительский
// процесс и дочерний выводят на экран свой pid, ppid. Затем родительский
// ждет завершения дочернего и выводит его статус завершения.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main() {
    pid_t child_pid;
    int status;

    child_pid = fork(); // On success, the PID of the child process is returned in the parent, and 0  is returned in the child.
    // On failure, -1 is returned in the parent, no child process is created, and errno is set appropriately.

    if (child_pid == 0) {
        printf("Child process: pid = %d, ppid = %d\n", getpid(), getppid());
        exit(EXIT_FAILURE);
    } else if (child_pid > 0)
    {

        waitpid(child_pid, &status, 0);

        printf("Main process: pid = %d, ppid = %d\n", getpid(), getppid());

        printf("Child procex completion status: %d\n", WEXITSTATUS(status));

        exit(EXIT_SUCCESS);
    } else 
    {
        // Не удалось запустить дочерний процесс
        perror("[PERROR] fork status:");
        exit(EXIT_FAILURE);
    }

    return 0;
}