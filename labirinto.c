#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define TAM 30
#define LIVRE 255
#define PAREDE 219
#define VISITADO 46
#define BECO 176
#define ATUAL 175

int labirinto[TAM][TAM];

typedef struct Pilha
{
    int pos;
    struct Pilha *prox;
}Pilha;

Pilha *cria_nodo()
{
    Pilha *p;

    p = (Pilha *) malloc(sizeof(Pilha));
    if(!p)
    {
        printf("\nProblema de alocacao\n\n");
        exit(0);
    }
    return p;
}

void inicializa_lista(Pilha **N)
{
    *N = NULL;
}

void libera_lista(Pilha *N)
{
    Pilha *aux;

    while(N != NULL)
    {
        aux = N;
        N = N->prox;
        free(aux);
    }
}

void push(Pilha **N, int dado)
{
    Pilha *novo;
    novo = cria_nodo();
    novo->pos = dado;
    novo->prox = *N;
    *N = novo;
}

int pop(Pilha **N)
{
    Pilha *aux;
    if(*N == NULL)
        return 0;
    else
    {
        aux = (*N)->prox;
        free(*N);
        *N = aux;
    }
    return 1;
}

int empilha(int i, int j)
{
    return (i*100 +j);
}

void desempilha(int *i, int *j, int pos)
{
    *i = pos / 100;
    *j = pos % 100;
}

int stackpop (Pilha *N)
{
    return N->pos;
}

void mostra_mapa()
{
    int i,j;

    for (i=0; i<TAM; ++i)
    {
        for (j=0; j<TAM; ++j)
        {
            printf("%c", labirinto[i][j]);
        }
        printf("\n");
    }
}

void inicia_mapa()
{
    int i, j, r;

    for (i=1; i<TAM-1; ++i)
    {
        for(j=1; j<TAM-1; ++j)
        {
            r=rand()%3;

            if (!r)
                labirinto[i][j] = PAREDE;
            else
                labirinto[i][j] = LIVRE;
        }
    }

    for (i=0; i<TAM; ++i)
    {
        labirinto[i][0] = labirinto[0][i] = labirinto[TAM-1][i] = labirinto[i][TAM-1] = PAREDE;
    }

    r=rand()%2;
    if(r)
    {
        r = rand()%TAM-2;
        r = r == LIVRE ? PAREDE : r;
        labirinto[TAM-1][rand()%TAM] = LIVRE;
    }
    else
    {
        r = rand()%TAM-2;
        r = r == LIVRE ? PAREDE : r;
        labirinto[r][TAM-1] = LIVRE;
    }
}

void caminhar(Pilha *p)
{
    int i=1,j=1,valor=0,becpar=0;

    inicializa_lista(&p);
    push(&p,empilha(1,1));
    mostra_mapa();

    while (p!=NULL && j<TAM-1 && i<TAM-1)
    {
        becpar=0;
        labirinto[i][j]=VISITADO;
        if(labirinto[i+1][j]==LIVRE)
        {
            i++;
            push(&p,empilha(i,j));
        }
        else if(labirinto[i][j+1]==LIVRE)
        {
            j++;
            push(&p,empilha(i,j));
        }
        else if(labirinto[i-1][j]==LIVRE)
        {
            i--;
            push(&p,empilha(i,j));
        }
        else if(labirinto[i][j-1]==LIVRE)
        {
            j--;
            push(&p,empilha(i,j));
        }
        else
        {
            if(labirinto[i+1][j]==PAREDE||labirinto[i+1][j]==BECO)becpar=1;
            if(labirinto[i][j+1]==PAREDE||labirinto[i][j+1]==BECO)becpar+=1;
            if(labirinto[i-1][j]==PAREDE||labirinto[i-1][j]==BECO)becpar+=1;
            if(labirinto[i][j-1]==PAREDE||labirinto[i][j-1]==BECO)becpar+=1;
            if (becpar==3)
                labirinto[i][j]=BECO;

            valor=pop(&p);

            if(valor==1 && i!=1 || j!=1)
            {
                desempilha(&i,&j,stackpop(p));
            }
            else
            {
                break;
            }
        }
        labirinto[i][j]=ATUAL;
        system("cls");
        mostra_mapa();
    }

    if(p!=NULL)
    {
        printf("Busca completa\n\n");
        printf("             _._\n");
        printf("          .-'   \n");
        printf("        __|__   \n");
        printf("       /     \\ \n");
        printf("       |()_()|   _____ \n");
        printf("       \\{o o}/  /|o  |\n");
        printf("        =\\o/=  /o|  o|\n");
        printf("         ^ ^  /o_|_o_|\n");
    }
    else
    {
        printf("Busca fracassada\n\n");
        printf("             _._\n");
        printf("          .-'   \n");
        printf("        __|__   \n");
        printf("       /     \\ \n");
        printf("       |()_()|  \n");
        printf("       \\{x x}/ \n");
        printf("        =\\o/=  \n");
        printf("         ^ ^    \n");
    }
    libera_lista(p);
}

void main()
{
    char op;
    Pilha *lab;
    srand(time(NULL));

    printf("Entrar no Labirinto (Aperte ENTER)\n");
    scanf("%c", &op);

    inicia_mapa();
    caminhar(lab);
    printf("\nAte a proxima!");
}
