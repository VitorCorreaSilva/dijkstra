#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int menorDistancia(int *menor_distancia, int *vertice_processado, int vertices)
{
    int i, menor_index;
    int min = INT_MAX;
 
    for (i = 0; i < vertices; i++){
        if (vertice_processado[i] == 0 && menor_distancia[i] <= min){
            min = menor_distancia[i];
            menor_index = i;
        }
    }

    return menor_index;
}

void imprimirCaminho(int *caminho, int contador)
{
    if (caminho[contador] == -1){
        return;
    }
    imprimirCaminho(caminho, caminho[contador]);
    printf("%d ", contador);
}

void imprimirSolucao(int *menor_distancia, int vertices, int *caminho, int inicio)
{
    int i;
    printf("Vertice\t Distancia\tCaminho");
    for (i = 0; i < vertices; ++i)
    {
        printf("\n%d -> %d \t\t %d\t%d ", inicio, i, menor_distancia[i], inicio);
        imprimirCaminho(caminho, i);
    }
    printf("\n");
}
 
void dijkstra(int **matriz_distancias, int vertices, int inicio)
{
    int i, j;
    int vertice_menor_distancia;
    int *menor_distancia;
    int *vertice_processado;
    int *caminho;

    /* Array de saida. distancia[i] guarda a menor distancia de inicio até i */
    menor_distancia = (int *)calloc(vertices,sizeof(int));
 
    /* vertice_processado[i] será 1 se o vertice i for processado */
    vertice_processado = (int *)calloc(vertices,sizeof(int)); 
 
    /* Menor caminho */
    caminho = (int *)calloc(vertices,sizeof(int)); 

    for(i = 0; i < vertices; ++i){
        caminho[i] = -1;
    }
 
    /* Inicia todo o array menor_distancia com um valor muito alto */
    for(i = 0; i < vertices; i++) {
        menor_distancia[i] = INT_MAX;
    }
 
    /* Distancia para o vertice inicial sempre vai ser 0*/
    menor_distancia[inicio] = 0;
 
    /* Lçao para procurar a menor distancia para todos os vertices */
    for(i = 0; i < vertices - 1; i++) {

        /* Pega o vertice com a menor distancia dos vertices ainda não processados  */
        vertice_menor_distancia = menorDistancia(menor_distancia, vertice_processado, vertices);

        /* Marca o vertice testado como processado */
        vertice_processado[vertice_menor_distancia] = 1;

        /* Atualiza o valor menor_distancia dos vertices com adjacencia com o vertice escolhido. */
        for(j = 0; j < vertices; j++)
            /* Atualiza menor_distancia[j] somente se não estiver em vertice_processado,
               se há uma aresta de vertice_menor_distancia para j, 
               se o valor do inicio para j através de vertice_menor_distancia é menor que o valor atual de menor_distancia[j] */
            if (!vertice_processado[j] && matriz_distancias[vertice_menor_distancia][j] && menor_distancia[vertice_menor_distancia] + matriz_distancias[vertice_menor_distancia][j] < menor_distancia[j]) {
                caminho[j] = vertice_menor_distancia;
                menor_distancia[j] = menor_distancia[vertice_menor_distancia] + matriz_distancias[vertice_menor_distancia][j];
            }
    }
    /* print the constructed distance array */
    imprimirSolucao(menor_distancia, vertices, caminho, inicio);
}

int **alocarMatrizDistancias(int vertices){
    int **matriz;
    int i;
    matriz = (int**)calloc(vertices,sizeof(int*));
    for (i = 0; i < vertices; ++i)
    {
        matriz[i] = (int *)calloc(vertices,sizeof(int));
    }

    return matriz;
}
 
int main()
{
    int vertices, i, j, inicio;
    int **matriz_distancias;
    FILE *arq;

    arq = fopen("entrada.txt", "r");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    fscanf(arq,"%i",&vertices);

    matriz_distancias = alocarMatrizDistancias(vertices);
    for (i = 0; i < vertices; ++i)
    {
        for (j = 0; j < vertices; ++j)
        {
            fscanf(arq,"%i",&matriz_distancias[i][j]);
        }
    }

    fscanf(arq,"%i",&inicio);
 
    dijkstra(matriz_distancias, vertices, inicio);
 
    return 0;
}