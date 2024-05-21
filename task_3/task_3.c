#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char command[100];
    char *args[10];
    pid_t pid;

    while (1) {
        printf("Program name with startup options: "); 
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        // Проверка на команду выхода
        if (strcmp(command, "exit") == 0) {
            exit(EXIT_SUCCESS);
        }

        // Разбиваем команду на аргументы
        int i = 0;
        args[i] = strtok(command, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        pid = fork();
        if (pid == 0) {
            // Если мы находимся в дочернем процессе, выполняем введенную программу
            if (execvp(args[0], args) == -1) {
                perror("exec");
                exit(EXIT_FAILURE);
            }
        } else if (pid > 0) {
            // Если мы находимся в родительском процессе, ожидаем завершения дочернего процесса
            wait(NULL);
        } else {
            // Не удалось запустить дочерний процесс
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
