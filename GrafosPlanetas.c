#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9 //Planetas incluindo o sol

void inserirAresta(double matriz[][MAX], int origem, int destino, double custo){
    matriz[origem][destino] = custo;
    matriz[destino][origem] = custo;
}

void removerAresta(double matriz[][MAX], int origem, int destino){
    matriz[origem][destino] = -1;
    matriz[destino][origem] = -1;
}

void inicializa_matriz(double matriz[][MAX]){
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matriz[i][j] = -1;
        }
    }
}

void le_arquivo(double matriz[][MAX], FILE *arquivo){
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (fscanf(arquivo, "%lf", &matriz[i][j]) != 1) {
                printf("Erro ao ler [%d][%d]\n", i, j);
                matriz[i][j] = -1;
            }
        }
    }
}

void imprime_matriz(double matriz[][MAX]){
    printf("\nMatriz de custos:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (matriz[i][j] == -1)
                printf(" -- ");
            else
                printf(" %2.1lf ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main(){

    FILE *arquivo;

    arquivo = fopen("custoPlanetas.txt", "r");

    if (arquivo == NULL) {
    printf("Arquivo nao foi aberto corretamente!\n");
    return 1;
}

    char* planetas[MAX] = {"Sol", "Mercurio", "Venus", "Terra", "Marte", "Jupiter",
         "Saturno", "Urano", "Netuno"};
    double matriz[MAX][MAX];
    
    inicializa_matriz(matriz);

    le_arquivo(matriz, arquivo);

    imprime_matriz(matriz);

    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar o arquivo!\n");
    }

    return 0;

}