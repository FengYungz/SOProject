#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawSquareWithTitle(int x, int y, int width, int height, const char* title) {
    gotoxy(x, y);
    printf("%c", 201); // Top-left corner
    for (int i = 1; i < width; i++) printf("%c", 205); // Top border
    printf("%c", 187); // Top-right corner

    for (int i = 1; i < height; i++) {
        gotoxy(x, y + i);
        printf("%c", 186); // Left border
        gotoxy(x + width, y + i);
        printf("%c", 186); // Right border
    }

    gotoxy(x, y + height);
    printf("%c", 200); // Bottom-left corner
    for (int i = 1; i < width; i++) printf("%c", 205); // Bottom border
    printf("%c", 188); // Bottom-right corner

    // Centralizar o título dentro do quadrado
    int titleLength = strlen(title);
    int titleX = x + (width - titleLength) / 2;
    gotoxy(titleX, y);
    printf("%s", title); // Title
}

int main() {
    // Set the console window size
    system("mode con: cols=100 lines=25");

    // Draw the STATUS square
    drawSquareWithTitle(2, 2, 30, 10, "STATUS");
    gotoxy(4, 4);
    printf("MOV AX, 10");
    gotoxy(4, 5);
    printf("MOV BX, AX <---");
    gotoxy(4, 6);
    printf("JMP 0");
    gotoxy(4, 7);
    printf("HTL");

    // Draw the TCB square
    drawSquareWithTitle(35, 2, 30, 10, "TCB");
    gotoxy(37, 4);
    printf("PID: 3");
    gotoxy(37, 5);
    printf("REG AX:");
    gotoxy(37, 6);
    printf("REG BX:");
    gotoxy(37, 7);
    printf("PC: 1");
    gotoxy(37, 8);
    printf(".......");

    // Draw the BITS square
    drawSquareWithTitle(68, 2, 20, 9, "BITS\n");
    gotoxy(70, 4);
    printf("1 | 1 | 1 | 1 | 1 \n");
    gotoxy(70, 5);
    printf("-----------------\n");
    gotoxy(70, 6);
    printf("1 | 1 | 1 | 1 | 1 \n");
    gotoxy(70, 7);
    printf("-----------------\n");
    gotoxy(70, 8);
    printf("1 | 1 | 1 | 1 | 1 \n");
    gotoxy(70, 9);
    printf("-----------------\n");
    gotoxy(70, 10);
    printf("1 | 1 | 1 | 1 | 1 \n");

    // Draw the QUEUE square
    drawSquareWithTitle(2, 15, 70, 6, "QUEUE");

    // Draw the QUEUE labels
    gotoxy(5, 17);
    printf("PID10");

    gotoxy(20, 17);
    printf("PID9");

    gotoxy(35, 17);
    printf("KILL");

    gotoxy(50, 17);
    printf("PID7");

    gotoxy(65, 17);
    printf("CREATE");

    // Calcular a posição vertical para a mensagem "Pressione Enter para sair..."
    int windowHeight = 25;
    int messageHeight = 1;
    int messageY = windowHeight - messageHeight - 1;

    // Imprimir a mensagem "Pressione Enter para sair..." na posição calculada
    int messageX = 2; // Defina a posição horizontal desejada
    gotoxy(messageX, messageY);
    printf("Pressione Enter para sair...");

    // Pausa antes de retornar, esperando que o usuário pressione Enter
    getchar();

    return 0;
}