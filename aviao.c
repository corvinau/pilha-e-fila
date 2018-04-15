#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct Node
{
    int num;
    char nome[20], tipo[20], origem[20], destino[20];
    struct Node *prox;
} aviao;

int tamd=0, tamp=0, tam=0;

void inicia(aviao *FILA);
int vazia(aviao *FILA);
aviao *aloca();
void insere(aviao *estado);
aviao *retira(aviao *FILA);
void exibe(aviao *estado);
void libera(aviao *FILA);
void lista(aviao *estado);
int primeiro(aviao *estado);
void animapouso();
void animadecolar();

int main()
{
    aviao *decolagem, *pousar, *tmp;
    int opt;
    inicia(&decolagem);
    inicia(&pousar);
    do
    {
        printf("\n                             \\   /");
        printf("\n                              \\_/");
        printf("\n                               |");
        printf("\n                               |");
        printf("\n                              ###");
        printf("\n                              ###   ");
        printf("\n                  ##########################");
        printf("\n                  \\                       /");
        printf("\n                   \\                     /");
        printf("\n #########################################################");
        printf("\n  \\                                                      /");
        printf("\n   \\                   AEROPORTO F&T                    /");
        printf("\n    \\                                                  /");
        printf("\n     \\  |##########################################|  /");
        printf("\n      \\ |  |________|________||________|________|  | /");
        printf("\n       \\|__|________|________||________|________|__|/ ");
        printf("\n          |                                      |  ");
        printf("\n          |                                      |");
        printf("\n          |                                      |");
        printf("\n          |             DECOLAGEM                |");
        printf("\n          |1. Adicionar aviao na fila de         |");
        printf("\n          |decolagem                             |");
        printf("\n          |2. Autorizar aviao para decolagem     |");
        printf("\n          |3. Listar avioes na fila de decolagem |");
        printf("\n          |4. Listar numero de avioes na fila    |");
        printf("\n          |de decolagem                          |");
        printf("\n          |                                      |");
        printf("\n          |                POUSO                 |");
        printf("\n          |5. Adicionar aviao na fila de pouso   |");
        printf("\n          |6. Autorizar aviao da fila de pouso   |");
        printf("\n          |7. Listar avioes na fila de pouso     |");
        printf("\n          |8. Listar numero de avioes na fila    |");
        printf("\n          |de pouso                              |");
        printf("\n          |                                      |");
        printf("\n          |                                      |");
        printf("\n          |0.Sair                                |");
        printf("\n          |                                      |\n");

        scanf("%d", &opt);
        system("cls");
        switch(opt)
        {
        case 1:
            insere(&decolagem);
            break;
        case 2:
            if(primeiro(&decolagem)== 1)
            {
                if(!vazia(&decolagem))
                {
                    tmp = retira(&decolagem);
                    system("cls");
                    animadecolar();
                }
            }
            else
            {
                opt=9;
            }

            if(tmp!=NULL)
            {
                free(tmp);
            }
            break;
        case 3:
            exibe(&decolagem);
            break;
        case 4:
            lista(&decolagem);
            break;
        case 5:
            insere(&pousar);
            break;
        case 6:
            if(primeiro(&pousar)== 1)
            {
                if(!vazia(&pousar))
                {
                    tmp = retira(&pousar);
                    system("cls");
                    animapouso();
                }
            }
            else
            {
                opt=9;
            }

            if(tmp!=NULL)
            {
                free(tmp);
            }
            break;
        case 7:
            exibe(&pousar);
            break;
        case 8:
            lista(&pousar);
            break;
        case 0:
            break;
        default:
            printf("\n");
        }
    }
    while(opt!=0);
}

void inicia(aviao *FILA)
{
    FILA->prox = NULL;
    tam=0, tamd=0, tamp=0;
}

int vazia(aviao *FILA)
{
    if(FILA->prox == NULL)
        return 1;
    else
        return 0;
}

aviao *aloca()
{
    aviao *novo=(aviao *) malloc(sizeof(aviao));
    if(!novo)
    {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    else
    {
        printf("Codigo Aviao: ");
        scanf("%d", &novo->num);
        fflush(stdin);
        printf("Nome Piloto: ");
        scanf("%s",&novo->nome);
        fflush(stdin);
        printf("Origem de Partida: ");
        scanf("%s",&novo->origem);
        fflush(stdin);
        printf("Destino da Viagem: ");
        scanf("%s",&novo->destino);
        return novo;
    }
}

void insere(aviao *estado)
{
    aviao *novo=aloca();
    novo->prox = NULL;
    if(vazia(estado))
        estado->prox=novo;
    else
    {
        aviao *tmp = estado->prox;
        while(tmp->prox != NULL)
            tmp = tmp->prox;
        tmp->prox = novo;
    }
}

aviao *retira(aviao *FILA)
{
    if(FILA->prox == NULL)
    {
        printf("Fila ja esta vazia\n");
        return NULL;
    }
    else
    {
        aviao *tmp = FILA->prox;
        FILA->prox = tmp->prox;
        return tmp;
    }
}

void exibe(aviao *estado)
{
    if(vazia(estado))
    {
        printf("Fila vazia!\n\n");
        return ;
    }
    aviao *tmp;
    tmp = estado->prox;
    printf("Fila: ");
    while(tmp != NULL)
    {
        printf("Aviao: %d ", tmp->num);
        printf("Piloto: %s ", tmp->nome);
        printf("Origem de Partida: %s ", tmp->origem);
        printf("Destino da Viagem: %s;\n", tmp->destino);
        tmp = tmp->prox;
    }
    printf("\n");
}

void libera(aviao *FILA)
{
    if(!vazia(FILA))
    {
        aviao *proxNode,*atual;

        atual = FILA->prox;
        while(atual != NULL)
        {
            proxNode = atual->prox;
            free(atual);
            atual = proxNode;
        }
    }
}

void lista(aviao *estado)
{
    int tama=0;
    if(vazia(estado))
    {
        printf("Fila vazia!\n\n");
        return ;
    }
    aviao *tmp;
    tmp = estado->prox;
    printf("Fila: ");
    while(tmp != NULL)
    {
        printf("Piloto: %s ", tmp->nome);
        printf("Aviao: %d;", tmp->num);
        tmp = tmp->prox;
        tama++;
    }
    printf("\n%d",tama);
}

int primeiro(aviao *estado)
{
    char opt;
    if(vazia(estado))
    {
        printf("Fila vazia!\n\n");
        return ;
    }
    aviao *tmp;
    tmp = estado->prox;
    printf("\nAviao: %d;   ", tmp->num);
    printf("\nPiloto: %s ", tmp->nome);
    printf("\nOrigem de Partida: %s; ", tmp->origem);
    printf("\nDestino da Viagem: %s; ", tmp->destino);
    tmp = tmp->prox;
    printf("\nAutorizar? (s/n)\n");
    scanf("%*c%c", &opt);
    if(opt == 's')
    {
        return 1;
    }
    else
    {
        opt= 'n';
        system("cls");
        return 0;
        system("cls");
    }
}

void animapouso()
{
    int i;

    for(i = 0; i<2; i++)
    {
        printf("\n           _____");
        printf("\n           \\ U \\__      _____");
        printf("\n            \\   \\/_______\\___\\_____________");
        printf("\n           < /_/   .....................  `-.");
        printf("\n            `-----------,----,--------------'");
        printf("\n                       _/____/");
        Sleep(1000);
        system("cls");

        for(i = 0; i<2; i++)
        {
            printf("\n\n\n\t           _____");
            printf("\n\t           \\ U \\__      _____");
            printf("\n\t            \\   \\/_______\\___\\_____________");
            printf("\n\t           < /_/   .....................  `-.");
            printf("\n\t            `-----------,----,--------------'");
            printf("\n\t                       _/____/");
            Sleep(1000);
            system("cls");

            for(i = 0; i<2; i++)
            {
                printf("\n\n\n\n\n\t\t           _____");
                printf("\n\t\t           \\ U \\__      _____");
                printf("\n\t\t            \\   \\/_______\\___\\_____________");
                printf("\n\t\t           < /_/   .....................  `-.");
                printf("\n\t\t            `-----------,----,--------------'");
                printf("\n\t\t                       _/____/");
                Sleep(1000);
                system("cls");

                for(i = 0; i<2; i++)
                {
                    printf("\n\n\n\n\n\t\t\t           _____");
                    printf("\n\t\t\t           \\ U \\__      _____");
                    printf("\n\t\t\t            \\   \\/_______\\___\\_____________");
                    printf("\n\t\t\t           < /_/   .....................  `-.");
                    printf("\n\t\t\t            `-----------,----,--------------'");
                    printf("\n\t\t\t                       _/____/");
                    Sleep(1000);
                    system("cls");
                }
            }
        }
    }
}

void animadecolar()
{
    int i;
    for(i = 0; i<2; i++)
    {
        printf("\n\n\n\n\n\n\n           _____");
        printf("\n           \\ U \\__      _____");
        printf("\n            \\   \\/_______\\___\\_____________");
        printf("\n           < /_/   .....................  `-.");
        printf("\n            `-----------,----,--------------'");
        printf("\n                       _/____/");
        Sleep(1000);
        system("cls");

        for(i = 0; i<2; i++)
        {
            printf("\n\n\n\n\n\t           _____");
            printf("\n\t           \\ U \\__      _____");
            printf("\n\t            \\   \\/_______\\___\\_____________");
            printf("\n\t           < /_/   .....................  `-.");
            printf("\n\t            `-----------,----,--------------'");
            printf("\n\t                       _/____/");
            Sleep(1000);
            system("cls");

            for(i = 0; i<2; i++)
            {
                printf("\n\n\t\t           _____");
                printf("\n\t\t           \\ U \\__      _____");
                printf("\n\t\t            \\   \\/_______\\___\\_____________");
                printf("\n\t\t           < /_/   .....................  `-.");
                printf("\n\t\t            `-----------,----,--------------'");
                printf("\n\t\t                       _/____/");
                Sleep(1000);
                system("cls");

                for(i = 0; i<2; i++)
                {
                    printf("\n\t\t\t           _____");
                    printf("\n\t\t\t           \\ U \\__      _____");
                    printf("\n\t\t\t            \\   \\/_______\\___\\_____________");
                    printf("\n\t\t\t           < /_/   .....................  `-.");
                    printf("\n\t\t\t            `-----------,----,--------------'");
                    printf("\n\t\t\t                       _/____/");
                    Sleep(1000);
                    system("cls");
                }
            }
        }
    }
}
