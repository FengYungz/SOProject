#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 20

int memory[MEMORY_SIZE] = {0};
int current_value = 1;

void allocateMemory(int count) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (count == 0) {
            break;
        }
        
        if (memory[i] == 0) {
            memory[i] = current_value;
            count--;
        }
    }
    current_value++;
}

void clearMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }
    current_value = 1;
}

void printMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

void printMemoryToFile(FILE *outputFile) {
    fprintf(outputFile, "Memory after operation: ");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        fprintf(outputFile, "%d ", memory[i]);
    }
    fprintf(outputFile, "\n");
}

int main() {
    char input[50];
    int count;

    while (1) {
        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);
        if (strncmp(input, "create -m", 9) == 0 && sscanf(input + 10, "%d", &count) == 1) {
            allocateMemory(count);
        } else if (strcmp(input, "kill\n") == 0) {
            clearMemory();
        } else {
            printf("Invalid command\n");
        }

        // Captura da saída em um arquivo temporário
        FILE *outputFile = fopen("memory_output.tmp", "w");
        if (outputFile != NULL) {
            printMemoryToFile(outputFile); //Printa o mapa de bits no terminal
            fclose(outputFile);

            // Execução do código para exibir a saída em um segundo terminal
            #ifdef _WIN32
            system("start cmd.exe /K type memory_output.tmp");
            #elif __linux__
            system("xterm -e cat memory_output.tmp");
            #endif
        } else {
            printf("Error creating output file.\n");
        }

        // Limpa o buffer de entrada
        while (getchar() != '\n');
    }

    return 0;
}
