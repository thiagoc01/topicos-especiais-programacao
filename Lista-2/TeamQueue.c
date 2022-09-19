#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _no_fila no_fila;

typedef struct _time
{
    no_fila *ultimo_fila; 
	int tamanho; 
	int *membros; 
}time;


struct _no_fila 
{
    int time; 
    int valor; 
    no_fila *prox; 

};

int retorna_time_membro(time *times, int tamanho_times, int membro) 
{
    int i = 0, j = 0;

    for (i = 0 ; i < tamanho_times ; i++) 
    {
        for (j = 0 ; j < (times + i)->tamanho ; j++) 
        {
            if (membro == (times + i)->membros[j]) 
                return i; 
        }
    }

    return -1; 
}

int le_entrada_inteiro(int *alvo) 
{
    return scanf("%d", alvo);
}

int le_entrada_string(char *alvo) 
{
    return scanf("%s", alvo);
}


void realiza_enqueue(no_fila **fila, time **times, int tamanho_times, int membro)
{

    int posicao_time_membro = retorna_time_membro(*times, tamanho_times, membro); 

    no_fila *anterior = NULL, *ponteiro = *fila;


    if ( (*times + posicao_time_membro) -> ultimo_fila == NULL) 
    {
        while (ponteiro != NULL) 
        {
            anterior = ponteiro;
            ponteiro = ponteiro -> prox;
        }

        no_fila *novo = (no_fila *) malloc(sizeof(no_fila)); 

        if (!novo) 
            return;



        novo->valor = membro;
        novo->time = posicao_time_membro;
        novo->prox = ponteiro;

        if (anterior != NULL) 
            anterior->prox = novo; 
        else
            *fila = novo; 

        (*times + posicao_time_membro)->ultimo_fila = novo; 
    }

    else
    {
    	

        ponteiro = (*times + posicao_time_membro) -> ultimo_fila; 
        anterior = ponteiro; 
        ponteiro = ponteiro->prox;

        no_fila *novo = (no_fila *) malloc(sizeof(no_fila));

        if (!novo)
            return;

        novo->valor = membro;
        novo->time = posicao_time_membro;
        novo->prox = ponteiro;

        anterior->prox = novo; 

        (*times + posicao_time_membro) -> ultimo_fila = novo;
    }
}

void realiza_dequeue(no_fila **fila, time **times, int tamanho_times)
{
    if (*fila == NULL) 
        return;

    
    int membro = (*fila)->valor; 

    no_fila *eliminado = *fila;
    

    int posicao_time_membro = retorna_time_membro(*times, tamanho_times, membro); 

    no_fila *prox = (*fila)->prox; 

    if (prox != NULL) 
    {
    	if ( prox->time != posicao_time_membro) 
    		(*times + posicao_time_membro)->ultimo_fila = NULL; 
    }

    else
    {
    	(*times + posicao_time_membro)->ultimo_fila = NULL; 
    }

    printf("%d\n", (*fila)->valor); 

    *fila = prox; 

    free(eliminado);

}


void recebe_comandos(time *times, int tamanho_times) 
{
    no_fila *fila = NULL;
    char comando[20];

    while(strstr(comando, "STOP") == NULL)
    {
        if (le_entrada_string(comando) != 0)
        {

            if ( strstr(comando, "ENQUEUE" ) != NULL) 
            {
                int membro;
                le_entrada_inteiro(&membro); 
                realiza_enqueue(&fila, &times, tamanho_times, membro);
            }

            else if ( strstr(comando, "DEQUEUE" ) != NULL ) 
               realiza_dequeue(&fila, &times, tamanho_times);
        }

    }


}

void inicializa_cenarios()
{
    int tamanho_times, i, j, num_cenarios = 1;
    time *times;

    while(!feof(stdin))
    {
        if (le_entrada_inteiro(&tamanho_times) != 0) 
        {
            if (tamanho_times == 0)
                return;
        }

        printf("Scenario #%d\n", num_cenarios);
        num_cenarios++;

        times = (time *) malloc(sizeof(time) * tamanho_times);

        if (!times)
            return;

        for (i = 0 ; i < tamanho_times ; i++) 
        {
            if (le_entrada_inteiro(&((times + i) -> tamanho)) != 0) 
            {
                (times + i ) -> membros = (int *) malloc(sizeof(int) * (times + i) -> tamanho); 

                if (!((times + i)-> membros)) 
                    return;

                (times + i)->ultimo_fila = NULL; 

                for (j = 0 ; j < (times + i) -> tamanho ; j++)
                {
                    le_entrada_inteiro((times + i)->membros + j); 
                }
            }
        }

        recebe_comandos(times, tamanho_times); 

        puts(""); 

        free(times); 
    }
}

int main()
{
    inicializa_cenarios();

    return 0;
}

