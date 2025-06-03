#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
volatile sig_atomic_t can = 1; 

void check(int sig) {
    can = 1;
}

int main() {
    char line[10];
    int block_duration = 6;
       
    printf("Натисніть Enter, щоб виконати дію.\n");

    signal(SIGALRM, check);

    while (1) {     
        printf("Статус: %s. Натисніть Enter > ", can ? "ДОЗВОЛЕНО" : "ЗАБЛОКОВАНО");

        if (fgets(line, sizeof(line), stdin) == NULL) {
             if (feof(stdin)) {
                 printf("\nВихід.\n");
                 break;
             }
             printf("Помилка читання введення");
             continue;
        }

        if (can) {          
            printf("Дія виконана успішно! Ви заблоковані на 6 секунд.\n");
            can = 0;
            alarm(block_duration); 
        } else { 
            printf("Будь ласка, зачекайте.\n");
        }
    }
    alarm(0);
    return 0;
}