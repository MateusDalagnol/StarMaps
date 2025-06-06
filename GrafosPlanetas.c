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

void imprimir_matriz(double matriz[][MAX_PLANETAS], char* planetas[]){
    printf("\nMatriz de custos:\n\n");
    printf("\n------------------------------------------------------------------------\
-------------------------------------------------------------------------\n");
    printf("             ");
    for (int i = 0; i < MAX_PLANETAS; i++){
            printf("%-14s ", planetas[i]);
    }

    printf("\n------------------------------------------------------------------------\
-------------------------------------------------------------------------");
    printf("\n");
    for (int i = 0; i < MAX_PLANETAS; i++){
        printf("|%-8s - ", planetas[i]);
        for (int j = 0; j < MAX_PLANETAS; j++) {
            if (matriz[i][j] == -1)
                printf("     --      | ");
            else
                printf("%-8.2lfM km | ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("------------------------------------------------------------------------\
-------------------------------------------------------------------------");
    printf("\n\n");
}

double calcularCusto(double matriz[][MAX_PLANETAS], int rota[]) {
	double custo = 0;
	for (int i = 0; i < MAX_PLANETAS - 1; i++) {
		custo += matriz[rota[i]][rota[i+1]];
	}
	return custo;
}

void mostrarRota(int* rota, char* planetas[]) {
	for (int i = 0; i < MAX_PLANETAS; i++) {
		printf("%s", planetas[rota[i]]);
		if (i != MAX_PLANETAS - 1) printf (" -> ");
	}
	printf("\n");
}

void rotasPossiveis(int* visitados, double matriz[][MAX_PLANETAS], int planeta_atual, int* rota, double* menor_custo, int tamanho, int* melhor_caminho, char* planetas[]) {
	rota[tamanho++] = planeta_atual;
	visitados[planeta_atual] = 1;

	if (tamanho == MAX_PLANETAS) {
		double custo = calcularCusto(matriz, rota);

		if (custo < *menor_custo) {
			*menor_custo = custo;
			for (int i = 0; i < MAX_PLANETAS; i++) melhor_caminho[i] = rota[i];
		}

	} else {
		for (int i = 0; i < MAX_PLANETAS; i++) {
			if (matriz[planeta_atual][i] != -1 && !visitados[i]) {
				rotasPossiveis(visitados, matriz, i, rota, menor_custo, tamanho, melhor_caminho, planetas);
			}
		}
	}

	visitados[planeta_atual] = 0;
}

void busca_todos_os_caminho(double matriz[][MAX_PLANETAS], char* planetas[], int* melhor_rota){
    int visitado[MAX_PLANETAS] = {0};
   
    int rota[MAX_PLANETAS] = {0};
    double menor_custo = 1e9;

    for (int i = 0; i < MAX_PLANETAS; i++) {
		rotasPossiveis(visitado, matriz, i, rota, &menor_custo, 0, melhor_rota, planetas);
        mostrarRota(melhor_rota, planetas);
	}
    
}

double busca_menor_caminho(double matriz[][MAX_PLANETAS], char* planetas[], int* melhor_rota){
    int visitado[MAX_PLANETAS] = {0};
   
    int rota[MAX_PLANETAS] = {0};
    double menor_custo = 1e9;

    for (int i = 0; i < MAX_PLANETAS; i++) {
		rotasPossiveis(visitado, matriz, i, rota, &menor_custo, 0, melhor_rota, planetas);
	}
    
    
    return menor_custo;
}

void menu_busca(double matriz[][MAX_PLANETAS], char* planetas[]){
    char opcao;
    do{

        printf("\nMenu de Busca:\n\
1 - Mostrar menor rota\n\
2 - mostrar menor caminha a partir de um planeta\n\
0 - Voltar ao menu principal\n\
Escolha: \n\n");

        scanf(" %c", &opcao);
        switch (opcao)
        {
        case '1':{
            int melhor_rota[MAX_PLANETAS] = {0};
            printf("\nCusto total: %.2lfM km\n", busca_menor_caminho(matriz, planetas, melhor_rota));
            mostrarRota(melhor_rota, planetas);
            break;
        }
        case '2':{
            int melhor_rota[MAX_PLANETAS] = {0};
            busca_todos_os_caminho(matriz, planetas, melhor_rota);
            break;
        }
        default:
            break;
        }
    }while(opcao != '0');
}

int atualizar_matriz(double matriz[][MAX_PLANETAS]){
    FILE* arquivo = abrir_arquivo_Reescrita();

    if(arquivo == NULL){return -1;}
    for (int i = 0; i < MAX_PLANETAS; i++) {
        for (int j = 0; j < MAX_PLANETAS; j++) {
            if (matriz[i][j] == -1){
                fprintf(arquivo, "%lf ", matriz[i][j]);
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
        printf("\n=== MENU PRINCIPAL ===\n");

        printf("\n\
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
                imprimir_matriz(matriz, planetas);
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

    FILE* arquivo = abrir_arquivo_Leitura();
        if (arquivo != NULL) {
        ler_arquivo(matriz, arquivo);
        } else {
        inicializar_matriz(matriz);
    }

    menu(matriz, planetas);

    atualizar_matriz(matriz);

    return 0;
}