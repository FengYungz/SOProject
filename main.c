#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 20

int memory[MEMORY_SIZE] = {0};
int process[100] = {0};
int processTimeRemaining[100] = {0}; // Array para armazenar o tempo restante de cada processo

void allocateMemory(int size, int index) {
    int aux = 100;
    int PID = 0;
    PID = 0;
    for (int i = 0; i < aux; i++) {
        if (process[i] == 0) {
            PID = i+1;
            process[i] = i+1;
            processTimeRemaining[i] = size; // Define o tempo restante para o novo processo
            aux = 0;
        }
    }
    for (int i = index; i < (size+index); i++) {
        memory[i] = PID; 
    }
}

void createProcess(int size) {
    int memCount = 0;
    int memStart = 0;
    int memControl = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == 0) {
            memCount++;
            if(memControl == 0){
                memStart = i;
                memControl++;
            }
        } else if(memory[i] != 0){
            memCount = 0;
            memStart = 0;
            memControl = 0;
        }
        if (memCount >= size) {
            allocateMemory(size, memStart);
            //printf("Selected Process %d | Remaining cycles: %d\n", process[size - 1], size);
            break;
        }
        if(i == MEMORY_SIZE-1){
            printf("No space available\n");
        }
    }
}

void killProcess(int killID) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if(memory[i] == killID){
            memory[i] = 0;
        }
    }
    process[killID-1] = 0;    
    processTimeRemaining[killID-1] = 0; // Reinicia o tempo restante ao matar o processo
}

int main() {
    char input[50];
    int size, killID;

    while (1) {
        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);
        if (strncmp(input, "create -m", 9) == 0 && sscanf(input + 10, "%d", &size) == 1) {
            if (size == 0) {
                printf("Error: process size = 0\n");
            } else {
                createProcess(size);
                //printf("Selected Process %d | Remaining cycles: %d\n", process[size - 1], size);
            }
        } else if (strncmp(input, "kill", 4) == 0 && sscanf(input + 5, "%d", &killID) == 1) {
            if (process[killID - 1] != 0) {
                //printf("Selected Process %d killed\n", killID);
                killProcess(killID);
                // Zera as alocações correspondentes ao processo com o ID mencionado
                for (int i = 0; i < MEMORY_SIZE; i++) {
                    if (memory[i] == killID) {
                        memory[i] = 0;
                    }
                }
            } else {
                //printf("Process %d not found\n", killID);
            }
        } else {
            printf("Invalid command\n");
        }

        // Captura da saída em um arquivo temporário
        FILE *outputFile = fopen("memory_output.tmp", "w");
        if (outputFile != NULL) {
            for (int i = 0; i < 100; i++) {
                if (process[i] != 0) {
                    fprintf(outputFile, "\n");
                    fprintf(outputFile, "Process (ID: %d) | Size: %d\n", process[i], processTimeRemaining[i]);
                    fprintf(outputFile, "Process (ID: %d) created\n", process[i]);
                    fprintf(outputFile, "TCB: PID = %d, PC = 0, REG AX = ...\n", process[i]);
                    fprintf(outputFile, "Memory Map: ");
                    for (int i = 0; i < MEMORY_SIZE; i++) {
                        fprintf(outputFile, "%d ", memory[i]);
                    }
                    fprintf(outputFile, "\n");
                }
            }

            fclose(outputFile);

            // Executa o código para exibir a saída em um segundo terminal
            #ifdef _WIN32
            system("start cmd.exe /K type memory_output.tmp");
            #elif __linux__
            system("xterm -e cat memory_output.tmp &");
            #endif
        } else {
            printf("Error creating output file.\n");
        }
    }

    return 0;
}
