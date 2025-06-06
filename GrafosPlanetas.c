#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLANETAS 9 //Planetas incluindo o sol

FILE* abrir_arquivo_Reescrita(){
    FILE* arquivo = fopen("custoPlanetas.txt", "w");

    if (arquivo == NULL) {
        printf("\nArquivo nao foi possivel abrir o arquivo!\n");
        printf("\nArquivo nao lido. Matriz inicializada com valores padrao!\n");
        return NULL;
    }
    
    return arquivo;
}

FILE* abrir_arquivo_Leitura(){
    FILE* arquivo = fopen("custoPlanetas.txt", "r");

    if (arquivo == NULL) {
        printf("\nArquivo nao foi possivel abrir o arquivo!\n");
        printf("\nArquivo nao lido. Matriz inicializada com valores padrao!\n");
        return NULL;
    }

    return arquivo;
}

void fechar_arquivo(FILE* arquivo){
    if(fclose(arquivo) != 0) {
        printf("Erro ao fechar o arquivo!\n");
    }
}

int busca_indice_planeta(char* planetas[]){
    char nome_planeta[9];
    
    printf("\n\nPlanetas e Estrelas disponveis:\n\n");
for (int i = 0; i < MAX_PLANETAS; i++) {
    printf("- %s\n", planetas[i]);
}
    printf("\nNome do planeta desejado: ");
    scanf("%8s", nome_planeta);

    for (int i = 0; i < MAX_PLANETAS; i++){
        if(strcmp(nome_planeta, planetas[i]) == 0){
        return i;
        }
        
    }
    return -1;

}

void inserirAresta(double matriz[][MAX_PLANETAS], int origem, int destino){
    double custo;
    printf("Digite o custo do trajeto: ");
    scanf("%lf", &custo);

    matriz[origem][destino] = custo;
    matriz[destino][origem] = custo;
}

void removerAresta(double matriz[][MAX_PLANETAS], int origem, int destino){
    matriz[origem][destino] = -1;
    matriz[destino][origem] = -1;
}

void inicializar_matriz(double matriz[][MAX_PLANETAS]){
    for (int i = 0; i < MAX_PLANETAS; i++) {
        for (int j = 0; j < MAX_PLANETAS; j++) {
            matriz[i][j] = -1;
        }
    }
}

void ler_arquivo(double matriz[][MAX_PLANETAS], FILE *arquivo){
    for (int i = 0; i < MAX_PLANETAS; i++) {
        for (int j = 0; j < MAX_PLANETAS; j++) {
            if (fscanf(arquivo, "%lf", &matriz[i][j]) != 1) {
                printf("Erro ao ler [%d][%d]\n", i, j);
                matriz[i][j] = -1;
            }
        }
    }

    fechar_arquivo(arquivo);
}

void imprimir_matriz(double matriz[][MAX_PLANETAS]){
    printf("\nMatriz de custos:\n");
    for (int i = 0; i < MAX_PLANETAS; i++) {
        for (int j = 0; j < MAX_PLANETAS; j++) {
            if (matriz[i][j] == -1)
                printf("--       | ");
            else
                printf("%-8.2lf | ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void menu_busca(double matriz[][MAX_PLANETAS], char* planetas[]){

}

int atualizar_matriz(double matriz[][MAX_PLANETAS]){
    FILE* arquivo = abrir_arquivo_Reescrita();

    for (int i = 0; i < MAX_PLANETAS; i++) {
        for (int j = 0; j < MAX_PLANETAS; j++) {
            if (matriz[i][j] == -1){
                fprintf(arquivo, "%.0lf ", matriz[i][j]);
            }else{
                fprintf(arquivo, "%.2lf ", matriz[i][j]);
                
            }
            
        }
        fprintf(arquivo, "\n");
    }

    fechar_arquivo(arquivo);
    return 0;
}

void menu(double matriz[][MAX_PLANETAS], char* planetas[]){
    char opcao;
    
    do{
        printf("\nMenu de opcoes: \n\n\
1 - Imprimir a matriz\n\
2 - Inserir a aresta\n\
3 - Remover a aresta\n\
4 - Atualizar Matriz\n\
5 - Menu de buscar\n\
0 - Sair do menu\n\n\
Escolha um opcao: ");

        scanf(" %c", &opcao);
        switch(opcao){
            case '1':{
                imprimir_matriz(matriz);
                break;
            }
            case '2':{
                printf("\nAdd aresta");
                int origem = busca_indice_planeta(planetas);
                int destino = busca_indice_planeta(planetas);

                if (origem == -1 || destino == -1) {
                    printf("\nPlaneta nao encontrado! Operacao cancelada.\n");
                } else {
                    inserirAresta(matriz, origem, destino);
                }
                break;  
            }
            case '3':{
                printf("\nRemove aresta\n\n");
                int origem = busca_indice_planeta(planetas);
                int destino = busca_indice_planeta(planetas);

                if (origem == -1 || destino == -1) {
                    printf("\nPlaneta nao encontrado! Operacao cancelada.\n");
                } else {
                    removerAresta(matriz, origem, destino);
                }
                break;
            }
            case '4':{
                atualizar_matriz(matriz);
                break;
            }
            case '5':{
                menu_busca(matriz, planetas);
                break;
            }
            default:
                break;
        }
    }while (opcao != '0');
}

int main(){

    char* planetas[MAX_PLANETAS] = {"Sol", "Mercurio", "Venus", "Terra", "Marte", "Jupiter",
    "Saturno", "Urano", "Netuno"};

    double matriz[MAX_PLANETAS][MAX_PLANETAS];

    inicializar_matriz(matriz);

    ler_arquivo(matriz, abrir_arquivo_Leitura());

    menu(matriz, planetas);

    atualizar_matriz(matriz);

    return 0;
}