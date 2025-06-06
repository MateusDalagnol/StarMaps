#include <stdio.h>
#include <stdlib.h>

#define SS 9 //Planetas incluindo o sol

void inserirAresta(double matriz[][SS], int origem, int destino, double custo){
    matriz[origem][destino] = custo;
    matriz[destino][origem] = custo;
}

void removerAresta(double matriz[][SS], int origem, int destino){
    matriz[origem][destino] = -1;
    matriz[destino][origem] = -1;
}

int main(){

    double matriz[SS][SS];
    
    for (int i = 0; i < SS; i++) {
        for (int j = 0; j < SS; j++) {
            matriz[i][j] = -1;
        }
    }

    inserirAresta(matriz, 4,8,40.1);
    inserirAresta(matriz, 5,1,60.5);
    inserirAresta(matriz, 0,3,60.8);
    inserirAresta(matriz, 3,7,4.32);


    printf("");

    printf("\nMatriz de custos:\n");
    for (int i = 0; i < SS; i++) {
        for (int j = 0; j < SS; j++) {
            if (matriz[i][j] == -1)
                printf(" -- ");
            else
                printf("%2.1lf ", matriz[i][j]);
        }
        printf("\n");
    }
    return 0;

}