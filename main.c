#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include "rotinas.h"

int error; //inteiro que checa se ocorreu um erro na criacao das threads
int ids[10]; // vetor com os ids das threads dos espectadores e dos imigrantes
int cadeiras[5];

sem_t confirm; //semaforo que indica que o juiz ja confirmou
sem_t juiz_fora; // semaforo que indica que o juiz saiu do predio
sem_t vagas_espectadores; // semaforo que indica quantas vagas tem no predio para espectadores
sem_t vagas_imigrantes; // semaforo que indica quantas vagas tem no predio
sem_t escolher_cadeira; // semaforos para as cadeiras de imigrantes
sem_t check_in[5]; // semaforos que indicam que o imigrante i fez checkin
sem_t certificado[5]; // semaforos que indicam que a pessoa na cadeira i ja pegou seu certificado


int main() {
	
	//INICIO CRIA ESTRUTURAS AUXILIARES -----------------------------------
	for (int i=0;i<5;i++) {
		cadeiras[i] = -1;
	}
	for (int i=1;i<=11;i++) {
		ids[i-1] = i;
	}
	//FIM CRIA ESTRUTURAS AUXILIARES --------------------------------------


	// INICIO CRIA SEMAFOROS ----------------------------------------------
	sem_init(&confirm,0,1); //inicializa o semaforo com valor 1

	sem_init(&juiz_fora,0,1); // inicializa o semaforo com valor 1

	sem_init(&vagas_espectadores,0,5); // inicializa o semaforo com valor 5

	sem_init(&vagas_imigrantes,0,5); // inicializa o semaforo com valor 5

	sem_init(&escolher_cadeira,0,1); // inicializa o semaforo com valor 1

	for (int i=0;i<5;i++) {
		sem_init(&check_in[i],0,1); //  inicializa os checkin com valor 1
	}

	for (int i=0;i<5;i++) {
		sem_init(&certificado[i],0,1); // inicializa os certificados com valor 1
	}
	//FIM CRIA SEMAFOROS --------------------------------------------------
	

	//INICIO CRIA PARAMETROS THREADS --------------------------------------
	params_imigrante parametros_i[10];
	params_espectador parametros_e[10];
	params_juiz parametros_j;
	for (int i=0;i<10;i++) {
		parametros_i[i].indice = i;
		parametros_i[i].confirm = &confirm;
        	parametros_i[i].juiz_fora = &juiz_fora;
        	parametros_i[i].vagas_imigrantes = &vagas_imigrantes;
        	parametros_i[i].escolher_cadeira = &escolher_cadeira;
		for (int j=0;j<5;j++) {
        		parametros_i[i].check_in[j] = &check_in[j];
        		parametros_i[i].certificado[j] = &certificado[j];
		}
		parametros_e[i].indice = i;
		parametros_e[i].juiz_fora = &juiz_fora;
        	parametros_e[i].vagas_espectadores = &vagas_espectadores;
	}
	parametros_j.confirm = &confirm;
        parametros_j.juiz_fora = &juiz_fora;
	for (int i=0;i<5;i++) {
        	parametros_j.check_in[i] = &check_in[i];
        	parametros_j.certificado[i] = &certificado[i];
	}
 

	//FIM CRIA PARAMETROS THREADS -----------------------------------------

	
	// INICIO CRIA THREADS ------------------------------------------------
        pthread_t imigrantes[10]; //threads para os imigrantes
        pthread_t espectadores[10]; //threads para os espectadores
        pthread_t juiz; //thread para o juiz
        error = pthread_create(&juiz,NULL,rotina_juiz,&parametros_j); // cria a thread do juiz
        if (error) {
                printf("Erro na criacao da thread do juiz.\n"); //testa se ocorreu um erro na criacao da thread do juiz
        }
        for (int i=0;i<10;i++) {
                error = pthread_create(&imigrantes[i],NULL,rotina_imigrante,&parametros_i[i]); // cria a thread do imigrante i
                if (error) {
                        printf("Erro na criacao da thread do imigrante %d.\n", i); // testa se ocorreu um erro na criacao da thread do imigrante i
                }
                error = pthread_create(&espectadores[i],NULL,rotina_espectador,&parametros_e[i]); // cria a threads do espectador i
                if (error) {
                        printf("Erro na criacao da thread do espectador %d.\n", i); // testa se ocorreu um erro na thread do espectador i
                }
        }
        // FIM CRIA THREADS ---------------------------------------------------

	
}
