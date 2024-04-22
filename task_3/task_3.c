// Реализовать аналог командного интерпретатора bash. При запуске
// программы пользователю предлагается ввести имя программы и опции
// запуска программы. Программа порождает процесс и в нем выполняет
// введенную программу с заданными опциями, ждет завершения
// дочернего процесса. Снова возвращается к вводу следующей
// программы. Выход из интерпретатора по команде exit.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char command[100];
    pid_t pid;

    while (1) {
        printf("Programm name with startup options: "); 
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        pid = fork();
        if (pid == 0) {
            // Если мы находимся в дочернем процессе, выполняем введенную программу
            system(command);
            exit(EXIT_SUCCESS);
        } else if (pid > 0) {
            // Если мы находимся в родительском процессе, ожидаем завершения дочернего процесса
            wait(NULL);
            exit(EXIT_SUCCESS);
        }
        else
        {
        // Не удалось запустить дочерний процесс
        perror("[PERROR] fork status:");
        exit(EXIT_FAILURE);

        }


        if (strcmp(command, "exit") == 0) {
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}