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
        
        printf("Memory after operation: ");
        printMemory();
    }

    return 0;
}
