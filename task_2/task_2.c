// Реализовать программу, которая порождает процесс1 и процесс2, ждет
// завершения дочерних процессов. Процесс1 в свою очередь порождает
// процесс3 и процесс4 и ждет их завершения. Процесс2 порождает
// процесс5 и ждет его завершения. Все процессы выводят на экран свой
// pid, ppid.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    pid_t child_pid_1, pid2, pid3, pid4, pid5;

    // Создаем процесс1
    child_pid_1 = fork();

    if (child_pid_1 == 0) {
        // Если мы находимся в процессе 1, создаем процесс 3
        pid3 = fork();
        if (pid3 == 0) {
            // Если мы находимся в процессе 3, выводим pid и ppid
            printf("Process3: pid = %d, ppid = %d\n", getpid(), getppid());
            // Завершаем процесс3
            exit(0);
        } else {
            // Если мы находимся в процессе 1, ожидаем завершения процесса3
            wait(NULL);
            // После завершения процесса3, выводим pid и ppid процесса1
            printf("Process1: pid = %d, ppid = %d\n", getpid(), getppid());
            // Завершаем процесс1
            exit(EXIT_SUCCESS);
        }
    } else if (child_pid_1 > 0){
        // Если мы находимся в основном процессе, создаем процесс4
        pid4 = fork();
        if (pid4 == 0) {
            // Если мы находимся в процессе4, выводим pid и ppid
            printf("Process4: pid = %d, ppid = %d\n", getpid(), getppid());
            // Завершаем процесс4
            exit(EXIT_SUCCESS);
        } else {
            // Если мы находимся в основном процессе, ожидаем завершения процесса4
            wait(NULL);
            // После завершения процесса4, создаем процесс2
            pid2 = fork();
            if (pid2 == 0) {
                // Если мы находимся в процессе2, создаем процесс5
                pid5 = fork();
                if (pid5 == 0) {
                    // Если мы находимся в процессе5, выводим pid и ppid
                    printf("Process5: pid = %d, ppid = %d\n", getpid(), getppid());
                    // Завершаем процесс5
                    exit(EXIT_SUCCESS);
                } else {
                    // Если мы находимся в процессе2, ожидаем завершения процесса5
                    wait(NULL);
                    // После завершения процесса5, выводим pid и ppid процесса2
                    printf("Process2: pid = %d, ppid = %d\n", getpid(), getppid());
                    // Завершаем процесс2
                    exit(EXIT_SUCCESS);
                }
            } else {
                // Если мы находимся в основном процессе, ожидаем завершения процесса2
                wait(NULL);
                // После завершения процесса2, ожидаем завершения процесса1
                wait(NULL);
                // После завершения всех дочерних процессов, выводим pid и ppid основного процесса
                printf("Main process: pid = %d, ppid = %d\n", getpid(), getppid());
                // Завершаем основной процесс
                exit(EXIT_SUCCESS);
            }
        }
    }
    else
    {
        // Не удалось запустить дочерний процесс
        perror("[PERROR] fork status:");
        exit(EXIT_FAILURE);

    }

    return 0;
}