#include <stdio.h>
#include <stdlib.h>

int main() {
    while (1) {
        int num1, num2;
        char passos[3][20] = {"PUSH AX", "MOV AX", "HLT"};

        // Terminal de entrada
        printf("Digite o primeiro valor: ");
        scanf("%d", &num1);
        printf("Digite o segundo valor: ");
        scanf("%d", &num2);

        // Cria strings para armazenar as mensagens
        char resultadoMsg[100];
        char passosMsg[100];

        // Formata as mensagens usando snprintf
        snprintf(resultadoMsg, sizeof(resultadoMsg), "Resultado da soma: %d\n", num1 + num2);
        snprintf(passosMsg, sizeof(passosMsg), "Passo: %s\n", passos[0]);

        // Cria um arquivo temporário para armazenar as mensagens
        FILE *outputFile = fopen("output.txt", "w");
        if (outputFile != NULL) {
            fprintf(outputFile, "%s%s", resultadoMsg, passosMsg);
            fclose(outputFile);

            // Abre uma nova janela do terminal para exibir o conteúdo do arquivo
            system("start cmd.exe /K type output.txt");
        } else {
            printf("Erro ao criar o arquivo de saída.\n");
        }

        // Limpa o buffer de entrada
        while (getchar() != '\n');
    }

    return 0;
}
