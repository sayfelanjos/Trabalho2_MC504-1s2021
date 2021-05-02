#include <semaphore.h>
#include <pthread.h>

int error; //inteiro que checa se ocorreu um erro na criacao das threads
int ids[10]; // vetor com os ids das threads dos espectadores e dos imigrantes
int cadeiras[5];

int main() {
	
	//INICIO CRIA ESTRUTURAS AUXILIARES -----------------------------------
	for (int i=0;i<5;i++) {
		cadeiras[i] = 1;
	}
	for (int i=1;i<=11;i++) {
		ids[i-1] = i;
	}
	//FIM CRIA ESTRUTURAS AUXILIARES --------------------------------------


	// INICIO CRIA SEMAFOROS ----------------------------------------------
	sem_t confirm; //semaforo que indica que o juiz ja confirmou 
	sem_init(&confirm,0,1); //inicializa o semaforo com valor 1

	sem_t juiz_fora; // semaforo que indica que o juiz saiu do predio
	sem_init(&juiz_fora,0,1); // inicializa o semaforo com valor 1

	sem_t vagas_espectadores; // semaforo que indica quantas vagas tem no predio para espectadores
	sem_init(&vagas_espectadores,0,5); // inicializa o semaforo com valor 5

	sem_t vagas_imigrantes; // semaforo que indica quantas vagas tem no predio
	sem_init(&vagas_imigrantes,0,5); // inicializa o semaforo com valor 5

	sem_t escolher_cadeira; // semaforos para as cadeiras de imigrantes
	sem_init(&escolher_cadeira,0,1); // inicializa o semaforo com valor 1

	sem_t check_in[5]; // semaforos que indicam que o imigrante i fez checkin
	for (int i=0;i<5;i++) {
		sem_init(&check_in[i],0,1); //  inicializa os checkin com valor 1
	}

	sem_t certificado[5]; // semaforos que indicam que a pessoa na cadeira i ja pegou seu certificado
	for (int i=0;i<5;i++) {
		sem_init(&certificado[i],0,1); // inicializa os certificados com valor 1
	}
	//FIM CRIA SEMAFOROS --------------------------------------------------
	

	// INICIO CRIA THREADS ------------------------------------------------
        pthread_t imigrantes[10]; //threads para os imigrantes
        pthread_t espectadores[10]; //threads para os espectadores
        pthread_t juiz; //thread para o juiz
        error = pthread_create(&juiz,NULL,rotina_juiz,NULL); // cria a thread do juiz
        if (erro) {
                printf("Erro na criacao da thread do juiz.\n"); //testa se ocorreu um erro na criacao da thread do juiz
        }
        for (int i=0;i<10;i++) {
                error = pthread_create(&imigrante[i],NULL,rotina_imigrante,(void*)ids[i]); // cria a thread do imigrante i
                if (erro) {
                        printf("Erro na criacao da thread do imigrante %d.\n", i); // testa se ocorreu um erro na criacao da thread do imigrante i
                }
                error = pthread_create(&espectador[i],NULL,rotina_espectador,(void*)ids[i]); // cria a threads do espectador i
                if (erro) {
                        printf("Erro na criacao da thread do espectador %d.\n", i); // testa se ocorreu um erro na thread do espectador i
                }
        }
        // FIM CRIA THREADS ---------------------------------------------------

	
}
