#include <semaphore.h>
#include <stdio.h>
#include "rotinas.h"


void* rotina_imigrante (void* parametros_i) {

	params_imigrante* parametros = (params_imigrante*) parametros_i;
	int ind = parametros->indice;
        sem_t* confirm = parametros->confirm;
        sem_t* juiz_fora = parametros->juiz_fora;
        sem_t* vagas_imigrantes = parametros->vagas_imigrantes;
        sem_t* escolher_cadeira = parametros->escolher_cadeira;
	sem_t* check_in[5];
        sem_t* certificado[5];
	for (int i=0;i<5;i++) {
		check_in[i] = parametros->check_in[i];
		certificado[i] = parametros->check_in[i];
	}
	int cadeira;

	while (1) {
		sem_wait(juiz_fora);
		sem_post(juiz_fora);
		sem_wait(vagas_imigrantes);
		printf("Thread %d entrou na sala.\n", ind);//enter();
		sem_wait(escolher_cadeira);
		for (int i=0;i<5;i++) {
			if (cadeiras[i]== -1) {
				cadeiras[i] = ind;
				cadeira = i;
				sem_wait(check_in[i]);
				sem_wait(certificado[i]);
				break;
			}
		}
		for (int i=0;i<5;i++) {
			if (cadeiras[i] == -1) {
				printf("  ");
			}
			else {
				printf("%d ", cadeiras[i]);
			}
		}
		printf("\n");
		sem_post(escolher_cadeira);
		printf("Thread %d deu checkin.\n", ind);//checkin();
		sem_post(check_in[cadeira]);
		sem_wait(confirm);
		printf("Thread %d fez o juramento.\n", ind);//swear();
		printf("Thread %d pegou o certificado.\n", ind);//getCertificate();
		sem_post(certificado[cadeira]);
		cadeiras[cadeira] = -1;
		sem_wait(juiz_fora);
		sem_post(juiz_fora);
		printf("Thread %d saiu do predio", ind);//leave();
		for (int i=0;i<5;i++) {
                        if (cadeiras[i] == -1) {
                                printf("  ");
                        }
                        else {
                                printf("%d ", cadeiras[i]);
                        }
                }
                printf("\n");
		sem_post(vagas_imigrantes);
	}
}

void* rotina_juiz (void* parametros_j) {

	params_juiz* parametros = (params_juiz*) parametros_j;
        sem_t* confirm = parametros->confirm;
        sem_t* juiz_fora = parametros->juiz_fora;
	sem_t* check_in[5];
	sem_t* certificado[5];
	for (int i=0;i<5;i++) {
        	check_in[i] = parametros->check_in[i];
        	certificado[i] = parametros->certificado[i];
	}

	while (1) {
		printf("Juiz entrou na casa.\n");//enter();
		sem_wait(juiz_fora);
		for (int i=0;i<5;i++) {
			sem_wait(check_in[i]);
		}
		printf("Juiz confirmou.\n");//confirm();
		for (int i=0;i<5;i++) {
			sem_post(check_in[i]);
		}
		for (int i=0;i<5;i++) {
			sem_wait(certificado[i]);
			sem_post(certificado[i]);
		}
		printf("Juiz saiu.\n");//leave();
		sem_post(juiz_fora);
	}
}

void* rotina_espectador (void* parametros_e) {

	params_espectador* parametros = (params_espectador*) parametros_e;
	int ind = parametros->indice;
        sem_t* juiz_fora = parametros->juiz_fora;
        sem_t* vagas_espectadores = parametros->vagas_espectadores;
	while (1) {
		sem_wait(juiz_fora);
		sem_post(juiz_fora);
		printf("Espectador %d entrou.\n", ind);//enter();
		//spectate();
		printf("Espectador %d saiu.\n", ind);//leave();
	}
}
