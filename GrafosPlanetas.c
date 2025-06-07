#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLANETAS 9 //Planetas incluindo o sol

FILE* abrir_arquivo_Reescrita(char nomeArquivo[]){
    FILE* arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("\nArquivo nao foi possivel abrir o arquivo!\n");
        printf("\nArquivo nao lido. Matriz inicializada com valores padrao!\n");
        return NULL;
    }
    
    return arquivo;
}

FILE* abrir_arquivo_Leitura(char nomeArquivo[]){
    FILE* arquivo = fopen(nomeArquivo, "r");

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
    for (int i = 0; i < MAX_PLANETAS; i++) {
        int visitado[MAX_PLANETAS] = {0};
        int rota[MAX_PLANETAS] = {0};
        double menor_custo = 1e9;
		rotasPossiveis(visitado, matriz, i, rota, &menor_custo, 0, melhor_rota, planetas);
        mostrarRota(melhor_rota, planetas);
	}
    
}

double busca_menor_caminho(double matriz[][MAX_PLANETAS], char* planetas[], int* melhor_rota){
    double menor_custo = 1e9;
    for (int i = 0; i < MAX_PLANETAS; i++) {
        int visitado[MAX_PLANETAS] = {0};
        int rota[MAX_PLANETAS] = {0};
		rotasPossiveis(visitado, matriz, i, rota, &menor_custo, 0, melhor_rota, planetas);
	}
    
    
    return menor_custo;
}

void bloquear_planeta(double matriz[][MAX_PLANETAS], char* planetas[]){
    int origem = busca_indice_planeta(planetas);
    int restricao = busca_indice_planeta(planetas);

    for (int i = 0; i < MAX_PLANETAS; i++){
        if(restricao != i){
            matriz[origem][i] = -1;
        }
    }
       
    imprimir_matriz(matriz, planetas);
    
}

void menu_busca(double matriz[][MAX_PLANETAS], char* planetas[],double matriz_restringida[][MAX_PLANETAS]){
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
            printf("A rota possui restricao? 1 - sim / 2- nao: ");
            int rota_com_bloqueio;
            scanf("%d", &rota_com_bloqueio);

            int melhor_rota[MAX_PLANETAS] = {0};
            if(rota_com_bloqueio == 1){
                printf("\nCusto total: %.2lfM km\n", busca_menor_caminho(matriz_restringida, planetas, melhor_rota));
                mostrarRota(melhor_rota, planetas);
            }else if(rota_com_bloqueio == 2){
                printf("\nCusto total: %.2lfM km\n", busca_menor_caminho(matriz, planetas, melhor_rota));
                mostrarRota(melhor_rota, planetas);
            
            }
            break;
        }
        case '2':{
            printf("A rota possui restricao? 1 - sim / 2- nao: ");
            int rota_com_bloqueio;
            scanf("%d", &rota_com_bloqueio);

            int melhor_rota[MAX_PLANETAS] = {0};
            if(rota_com_bloqueio == 1){
                busca_todos_os_caminho(matriz_restringida, planetas, melhor_rota);
            }else if(rota_com_bloqueio == 2){
                busca_todos_os_caminho(matriz, planetas, melhor_rota);
           
            }
            break;
        }
        default:
            break;
        }
    }while(opcao != '0');
}

int tamanho_arquivo(char* nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL)
        return 0;

    fseek(arquivo, 0, SEEK_END);
    int size = ftell(arquivo);
    fclose(arquivo);

    return size;
}

int atualizar_matriz(double matriz[][MAX_PLANETAS], double matriz_restringida[][MAX_PLANETAS]){
    printf("deseja altera o arquivo da matriz restringida? 1 - sim / 2 - nao ");
    int restringida;
    scanf("%d", &restringida);
    if(restringida == 1){
        FILE* arquivo2 = abrir_arquivo_Reescrita("custoRestricao.txt");
        if(arquivo2 == NULL){return -1;}
        for (int i = 0; i < MAX_PLANETAS; i++) {
            for (int j = 0; j < MAX_PLANETAS; j++) {
                if (matriz_restringida[i][j] == -1){
                    fprintf(arquivo2, "%.2lf ", matriz_restringida[i][j]);
                }else{
                    fprintf(arquivo2, "%.2lf ", matriz_restringida[i][j]);
                
                }
            
            }
        fprintf(arquivo2, "\n");
        }
        fechar_arquivo(arquivo2);
    }else{
         FILE* arquivo = abrir_arquivo_Reescrita("custoPlaneta.txt");
        if(arquivo == NULL){return -1;}
        for (int i = 0; i < MAX_PLANETAS; i++) {
            for (int j = 0; j < MAX_PLANETAS; j++) {
                if (matriz[i][j] == -1){
                    fprintf(arquivo, "%.2lf ", matriz[i][j]);
                }else{
                    fprintf(arquivo, "%.2lf ", matriz[i][j]);
                
                }
            
            }
            fprintf(arquivo, "\n");
        }
        fechar_arquivo(arquivo);
    }
    return 0;
}

void menu(double matriz[][MAX_PLANETAS], char* planetas[], double matriz_restringida[][MAX_PLANETAS]){
    int opcao;
    
    do{
        printf("\n=== MENU PRINCIPAL ===\n");

        printf("\n\
1 - Imprimir a matriz\n\
    11 - Imprimir a matriz restringida\n\
2 - Inserir a aresta\n\
3 - Remover a aresta\n\
4 - Atualizar Matriz\n\
5 - Menu de buscar\n\
6 - Restringir rota\n\
7 - Tirar restricao\n\
0 - Sair do menu\n\n\
Escolha um opcao: ");

        scanf("%i", &opcao);
        switch(opcao){
            case 1:{
                imprimir_matriz(matriz, planetas);
                break;
            }
            case 11:{
                imprimir_matriz(matriz_restringida, planetas);
                break;
            }
            case 2:{
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
            case 3:{
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
            case 4:{
                atualizar_matriz(matriz, matriz_restringida);
                break;
            }
            case 5:{
                menu_busca(matriz, planetas, matriz_restringida);
                break;
            }
            case 6:{
                imprimir_matriz(matriz_restringida, planetas);
                printf("Quantos rotas deseja restringir: ");
                int numero_planetas_bloquear;
                scanf("%i", &numero_planetas_bloquear);
                for (int i = 0; i < numero_planetas_bloquear; i++){
                    bloquear_planeta(matriz_restringida, planetas);
                }
            }
            case 7:{
                printf("Tirar restricao: ");
                for (int i = 0; i < MAX_PLANETAS; i++){
                    for (int j = 0; j < MAX_PLANETAS; j++){
                        matriz_restringida[i][j] = matriz[i][j];
                    }
                    
                }
                
            }
            default:
                break;
        }
    }while (opcao != 0);
}

int main(){

    char* planetas[MAX_PLANETAS] = {"Sol", "Mercurio", "Venus", "Terra", "Marte", "Jupiter",
    "Saturno", "Urano", "Netuno"};

    double matriz[MAX_PLANETAS][MAX_PLANETAS];
    double matriz_restringida[MAX_PLANETAS][MAX_PLANETAS];

    FILE* arquivo = abrir_arquivo_Leitura("custoPlanetas.txt");
        if (arquivo != NULL) {
            ler_arquivo(matriz, arquivo);
        } else {
            inicializar_matriz(matriz);
        }
    FILE* arquivo2 = abrir_arquivo_Leitura("custoRestricao.txt");
        if (arquivo2 != NULL && tamanho_arquivo("custoRestricao.txt") != 0) {
            ler_arquivo(matriz_restringida, arquivo2);
        }else{
            ler_arquivo(matriz_restringida, abrir_arquivo_Leitura("custoPlanetas.txt"));
        }
    

    menu(matriz, planetas, matriz_restringida);

    atualizar_matriz(matriz, matriz_restringida);

    return 0;
}