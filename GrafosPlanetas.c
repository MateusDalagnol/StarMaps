#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9 //Planetas incluindo o sol

int busca_indice_planeta(char* planetas[]){
    char nome_planeta[9];
    printf("Nome do planeta a ser buscado: ");
    scanf("%s", nome_planeta);

    for (int i = 0; i < MAX; i++){
        if(strcmp(nome_planeta, planetas[i]) == 0){
        return i;
        }
        
        
    }
    return -1;
    

}

void inserirAresta(double matriz[][MAX], int origem, int destino){
    double custo;
    printf("Digite o custo do trajeto: ");
    scanf("%lf", &custo);

    matriz[origem][destino] = custo;
    matriz[destino][origem] = custo;
}

void removerAresta(double matriz[][MAX], int origem, int destino){
    matriz[origem][destino] = -1;
    matriz[destino][origem] = -1;
}

void inicializar_matriz(double matriz[][MAX]){
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matriz[i][j] = -1;
        }
    }
}

void ler_arquivo(double matriz[][MAX], FILE *arquivo){
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (fscanf(arquivo, "%lf", &matriz[i][j]) != 1) {
                printf("Erro ao ler [%d][%d]\n", i, j);
                matriz[i][j] = -1;
            }
        }
    }
}

void imprimir_matriz(double matriz[][MAX]){
    printf("\nMatriz de custos:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (matriz[i][j] == -1)
                printf("--       | ");
            else
                printf("%-8.2lf | ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}



int main(){

    FILE *arquivo;

    arquivo = fopen("custoPlanetas.txt", "r");

    if (arquivo == NULL) {
    printf("Arquivo nao foi possivel abrir o arquivo!\n");
    return 1;
} 

    char* planetas[MAX] = {"Sol", "Mercurio", "Venus", "Terra", "Marte", "Jupiter",
         "Saturno", "Urano", "Netuno"};
    double matriz[MAX][MAX];
    
    inicializar_matriz(matriz);

    ler_arquivo(matriz, arquivo);

    imprimir_matriz(matriz);

    printf("Add aresta\n\n");
    inserirAresta(matriz, busca_indice_planeta(planetas), busca_indice_planeta(planetas));
    imprimir_matriz(matriz);

    printf("Remove aresta\n\n");
    removerAresta(matriz, busca_indice_planeta(planetas), busca_indice_planeta(planetas));

    imprimir_matriz(matriz);

    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar o arquivo!\n");
    }

    return 0;
}