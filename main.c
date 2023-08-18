#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MEMORY_SIZE 20

int memory[MEMORY_SIZE] = {0};
int process[100] = {0};
int processNumber = 0;
int selected = -1;
char instructions[4][10] = {"NOP","HALT", "ADD", "SUB","MOV"};

int next = -1;
int last = -1;
int selectStack[100] = {0};

void desFrag() {
    if(processNumber>=1){
        for (int i = 0; i < 20; i++) {
            if(memory[i] == 0){
                for (int j = i; j < 20-i; j++) {
                    if(j+1 < 20){
                        memory[j] = memory[j+1];
                    }else memory[j] = 0;
                }
                i--;
            }
        }
    }

}

void allocateMemory(int size, int index) {
    int aux = 100;
    int PID = 0;
    PID = 0;

    for (int i = 0; i < aux; i++) {
        if (process[i] == 0) {
            PID = i+1;
            process[i] = 4;
            processNumber++;
            selectStack[next+1]=i;
            next++;
            aux = 0;
        }
    }
    for (int i = index; i < (size+index); i++) {
        memory[i] = PID;
        if(selected == -1){
            selected = 0;
            last=0;
        }
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
            return;
        }
        if(i == MEMORY_SIZE-1){
            printf("No space available\n");
        }
    }
}

void selectProcess() {

    if(processNumber==0){
        selected = -1;
        printf("No process to escalonar");
    }
    selected = selectStack[last+1];
    last++;
}

void killProcess(int killID) {
    if(process[selected] == 1){
        selectProcess();
    }
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if(memory[i] == killID){
            memory[i] = 0;
        }
    }
    process[killID-1] = 0;
    processNumber--;

}

void showProcess(int n){
    int numeros[5];
    int i, j, num_aleatorio, repetido;

    char inst1[50] = "MOV AX, 0";
    char inst2[50] = "ADD AX, 4";
    char inst3[50]= "MOV BX, AX";
    char inst4[50] = "PUSH AX";
    char inst5[50] = "MOV AX, 10";

    // Inicializa o gerador de números aleatórios com base no tempo atual
    srand(time(NULL));

    printf("Instrucoes do Processo: \n");
    if (n > 6){
        n = 5;
    }
    for (i = 0; i < (n - 1); i++) {
        do {
            repetido = 0;
            num_aleatorio = 1 + rand() % 5;  // Gera um número aleatório entre 1 e 5

            // Verifica se o número já foi gerado anteriormente
            for (j = 0; j < i; j++) {
                if (numeros[j] == num_aleatorio) {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);  // Gera novo número se o atual já estiver na lista

        numeros[i] = num_aleatorio;
        if(num_aleatorio == 1){
            printf("%s\n", inst1);    
         }
        if(num_aleatorio == 2){
            printf("%s\n",inst2);
        }
        if(num_aleatorio == 3){
            printf("%s\n",inst3);
        }
        if(num_aleatorio == 4){
            printf("%s\n",inst4);
        }
        if(num_aleatorio == 5){
        printf("%s\n",inst5);
        }
    }

    printf("HLT");
    printf("\n");
}

int main() {
    char input[50];
    int size, killID;
    int id = 0;
    int counter = 0;
    bool creat = false;

    while (1) {
        // printa cois
        if(selected>=0){
            
        }

        // IMPORTANTE logica de ciclos
        if(selected >= 0){
            //printf("\nslec  %d\n ",selected);
            if(process[selected] == 1){
                printf("\nkill\n");

                killProcess(selected+1);
            }else process[selected]--;
        }

        // printa coisa
        //printf("\n");
        //printf("Selecionado: %d\nFaltam  %d ciclos \nIntrução: %d ",selected,process[selected],instructions[process[selected]]);
        //printf("\n");


        // Teste para printar instrução: nao foi direito
        // for (int i = 4; i > 0; i--) {
        //     printf("\n");
        //     for (int j = 0; j < 10; j++) {
        //         printf("\n %c ",instructions[process[selected]][j]);
        //     }
        //     printf("\n %c ",instructions[process[selected]]);
        //     if(process[selected] == i){
        //         printf(" <--- ");
        //     }
        // }
        // printf("\n");
        

        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);
        if (strncmp(input, "create -m", 9) == 0 && sscanf(input + 10, "%d", &size) == 1) {
            id++;
            creat = true;
            if (size == 0) {
                printf("Error: process size = 0\n");
            } else {
                createProcess(size);
                //printf("Selected Process %d | Remaining cycles: %d\n", process[size - 1], size);
            }
        } else if (strncmp(input, "kill", 4) == 0 && sscanf(input + 5, "%d", &killID) == 1) {
            creat = false;
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
        } else if (strncmp(input, "defrag", 4)){
            desFrag();
        } else {
            printf("Invalid command\n");
        }

        printf("\n");
        if(creat == true){
           showProcess(4);
            printf("\n");
        }

        // Captura da saída em um arquivo temporário
        FILE *outputFile = fopen("memory_output.tmp", "w");
        if (outputFile != NULL) {
            for (int i = 0; i < 100; i++) {
                if (process[i] != 0) {
                    fprintf(outputFile, "\n");
                    fprintf(outputFile, "Process (ID: %d) | Size: %d\n", id, size);
                    fprintf(outputFile, "Process (ID: %d) created\n", id);
                    fprintf(outputFile, "Processo Selecionado: %d\nFaltam  %d ciclos\n",id,process[selected]);
                    fprintf(outputFile, "Memory Map: ");
                    for (int i = 0; i < MEMORY_SIZE; i++) {
                        fprintf(outputFile, "%d ", memory[i]);
                    }
                    fprintf(outputFile, "\n");
                    fprintf(outputFile, "Lista de Processos: \n");
                    for (int i = 0; i < MEMORY_SIZE; i++) {
                    fprintf(outputFile,"| %d ",process[i]);
                    }
                    fprintf(outputFile, "\n");
                }
            }

            fclose(outputFile);

            // Executa o código para exibir a saída em um segundo terminal
            #ifdef _WIN32
            system("start cmd.exe /K type memory_output.tmp");
            #elif linux
            system("xterm -e cat memory_output.tmp &");
            #endif
        } else {
            printf("Error creating output file.\n");
        }
        if(counter == 5){
            selectProcess();
            counter = 0;
        }
        counter++;
    }

    return 0;
}