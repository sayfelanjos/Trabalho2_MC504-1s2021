#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include "rotinas.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void* rotina_imigrante (void *args) {
	int pos_fila; // guarda a posição em que a thread colocou o imigrante na fila para remoção posterior.
	int pos_check_in; // idem pos_fila
	args_imigrante* argumentos = (args_imigrante*) args;
	sem_wait(argumentos->imigrantes); // garante que somente 5 imigrantes entrem na fila por vez.
	if (*argumentos->juiz_dentro == 0) {
		sem_wait(argumentos->inseri_imigrantes_fila); // garante que somente 1 imigrante seja inserido por vez.
		pos_fila = verifica_posicao(argumentos->posicao_imigrante_fila);
		entra_imigrante(pos_fila, argumentos->indice, argumentos->imagem_imigrante, 
							argumentos->tela, argumentos->altera_tela);
		sleep(1);
		sem_post(argumentos->inseri_imigrantes_fila); // permite  que um novo imigrante seja inserido na fila.		
		sleep(1);
		sem_wait(argumentos->check_in); // garante que somente 5 imigrantes façam check-in por vez.
		if (*argumentos->juiz_dentro == 0) {
			sem_post(argumentos->imigrantes);
			(*argumentos->num_imigrantes_check_in)++;
			sem_wait(argumentos->inseri_imigrantes_check_in);
			pos_check_in = verifica_posicao(argumentos->posicao_imigrante_check_in);
			checkin_imigrante(pos_fila, pos_check_in ,argumentos->indice, argumentos->imagem_imigrante, 
								argumentos->vazio, argumentos->tela, argumentos->altera_tela);
			remove_posicao(pos_fila, argumentos->posicao_imigrante_fila);
			sleep(1);
			sem_post(argumentos->inseri_imigrantes_check_in);
			sem_post(argumentos->juiz_na_sala);
			sem_wait(argumentos->pega_certificado);
			sem_post(argumentos->check_in);
			pegar_certificado(pos_check_in, argumentos->indice,argumentos->imagem_imigrante, argumentos->vazio, 
								argumentos->tela, argumentos->altera_tela);
			sleep(2);
			sem_post(argumentos->pegou_certificado);
			sem_wait(argumentos->sair_sala); // libera a inserção de um novo imigrante na fila.
			pos_fila = verifica_posicao(argumentos->posicao_imigrante_fila);
			sem_post(argumentos->sair_sala);
			sai_imigrante_check_in(pos_fila, argumentos->indice, pos_check_in, argumentos->imagem_imigrante, 
									argumentos->vazio, argumentos->tela, argumentos->altera_tela);
			remove_posicao(pos_check_in, argumentos->posicao_imigrante_check_in);
			entra_imigrante(pos_fila, argumentos->indice, argumentos->imagem_imigrante, 
							argumentos->tela, argumentos->altera_tela);
			sleep(1);
			sai_imigrante_fila(pos_fila, argumentos->vazio, argumentos->tela, argumentos->altera_tela);
			remove_posicao(pos_fila, argumentos->posicao_imigrante_fila);
		}
		else {
			sai_imigrante_fila(pos_fila, argumentos->vazio, argumentos->tela, argumentos->altera_tela);
			remove_posicao(pos_fila, argumentos->posicao_imigrante_fila);
			sem_post(argumentos->check_in);
		}
	}
	sem_post(argumentos->imigrantes); // libera a inserção de um novo imigrante na fila.
	return NULL;
}

void* rotina_juiz (void* args) {
	args_juiz* argumentos = (args_juiz*) args;
	sleep(5 + (rand()%5));
	sem_wait(argumentos->juiz_na_sala);
	*argumentos->juiz_dentro = 1;
	entra_juiz(argumentos->imagem_juiz, argumentos->tela, argumentos->altera_tela);
	for (int i = 0; i < *argumentos->num_imigrantes_check_in; i++) {
		sem_post(argumentos->pega_certificado);
		sleep(1);
		juiz_confirma(argumentos->mensagem_confirma, argumentos->mensagem_apaga, 
					argumentos->tela, argumentos->altera_tela);
		sem_wait(argumentos->pegou_certificado);
	}
	sleep(1);
	sai_juiz(argumentos->vazio, argumentos->tela, argumentos->altera_tela);
	sem_post(argumentos->sair_sala);
	return NULL;
}

void* rotina_espectador (void* args) {
	int pos;
	args_espectador* argumentos = (args_espectador*) args;
	sem_wait(argumentos->espectadores_fila); // garante que no máximo 5 espectador entra na sala por vez.
	if (*argumentos->juiz_dentro == 0) {
		sem_wait(argumentos->inseri_espectador); // garante que somente 1 espectador vai ser inserido por vez.
		pos = verifica_posicao(argumentos->posicao_espectador_fila);
		entra_espectador(pos, argumentos->indice,argumentos->imagem_espectador, 
							argumentos->tela, argumentos->altera_tela);
		sleep(1);
		sem_post(argumentos->inseri_espectador);
		sleep(20);
		sai_espectador(pos, argumentos->vazio, argumentos->tela, argumentos->altera_tela);
		remove_posicao(pos, argumentos->posicao_espectador_fila);
		sleep(1);
		sem_post(argumentos->espectadores_fila);
	}
	else {
		sem_post(argumentos->espectadores_fila);
	}
	return NULL;
}

void wait_clear(){
	system("clear");  // should simply write the path to current shell
	printf("\a");
}

void imprime(char** tela, sem_t *altera_tela){
	// linha é o tamanho das linhas
	// coluna é o tamanho das colunas
	sem_wait(altera_tela);
	wait_clear();
	for (int i=0;i<LINHAS;i++){
		for (int j=0;j<COLUNAS;j++) {
			printf("%c",tela[i][j]);
		}
		printf("\n");
	}
	printf("Press Ctrl+C to exit\n");
	sem_post(altera_tela);
}

void insere_texto(int L, int C, int linha, int coluna, char** texto, char** tela){
	//LEGENDA:
        //posicao (2,7) tamanho (7,12) -> espaco de certificado
        //posicao (10,40) tamanho (7,12) -> espectador 4
        //posicao (10, 53) tamanho (7, 12) -> espectador 3
        //posicao (10, 66) tamanho (7, 12) -> espectador 2
        //posicao (10, 79) tamanho (7, 12) -> espectador 1
        //posicao (10, 92) tamanho (7, 12) -> espectador 0
        //posicao (18, 1) tamanho (7, 12) -> checked in 0
        //posicao (18, 14) tamanho (7, 12) -> cheked in 1
        //posicao (18, 27) tamanho (7, 12) -> checked in 2
        //posicao (18, 40) tamanho (7, 12) -> checked in 3
        //posicao (18, 53) tamanho (7, 12) -> checked in 4
        //posicao (27, 1)  tamanho (7, 12) -> fila imigrantes 0
        //posicao (27, 14) tamanho (7, 12) -> fila imigrantes 1
        //posicao (27, 27) tamanho (7, 12) -> fila imigrantes 2
        //posicao (27, 40) tamanho (7, 12) -> fila imigrantes 3
        //posicao (27, 53) tamanho (7, 12) -> fila imigrantes 4
        //posicao (1, 45) tamanho (7, 12) -> juiz

	for (int i=0;i<linha;i++) {
		for (int j=0;j<coluna;j++) {
			tela[L+i][C+j]=texto[i][j];
		}
	}
}

void atualiza_indice(int L, int C, char indice, char** tela){
	int X = 0; //posiçoes fixa da linha do "?" no boneco
	int Y = 10; //posiçoes fixa da coluna do "?" no boneco
	if (indice<10) {
		tela[L+X][C+Y] = '0';
		Y++;
		tela[L+X][C+Y] = '0'+indice;
	}
	else {
		tela[L+X][C+Y] = '0'+indice/10;
		Y++;
		tela[L+X][C+Y] = '0'+indice%10;
	}
}

void confirmed(char* mensagem, char** tela){
	int X = 5;
	int Y = 28;
	for (int j=0;j<16;j++){
		tela[X][Y+j]=mensagem[j];
	}
}

void entra_juiz(char** judge,char** tela, sem_t *altera_tela) {
	//posicao (1, 45) tamanho (7, 12) -> juiz
	insere_texto(1,45, 7, 12, judge, tela);
	imprime(tela, altera_tela);
}

void juiz_confirma(char* mensagem, char* apaga, char** tela, sem_t *altera_tela) {
	confirmed(mensagem,tela);
	imprime(tela, altera_tela);
	sleep(1);
	confirmed(apaga,tela);
	imprime(tela, altera_tela);
}

void sai_juiz(char** vazio, char** tela, sem_t *altera_tela) {
	//posicao (1, 45) tamanho (7, 12) -> juiz
	insere_texto(1,45, 7, 12, vazio, tela);
	imprime(tela, altera_tela);
}

void entra_imigrante(int pos_fila,int id,char** imigrante, char** tela, sem_t *altera_tela) {
	//posicao (27, 1)  tamanho (7, 12) -> fila imigrantes 0
	insere_texto(27,1+13*pos_fila, 7, 12, imigrante, tela);
	atualiza_indice(27, 1+13*pos_fila, id, tela);
	imprime(tela, altera_tela);
}

void checkin_imigrante(int pos_fila, int pos_check_in,int id,char** imigrante, char** vazio, char** tela, sem_t *altera_tela) {
	//posicao (27, 1)  tamanho (7, 12) -> fila imigrantes 0
	//posicao (18, 1) tamanho (7, 12) -> checked in 0
	insere_texto(27,1+13*pos_fila, 7, 12, vazio, tela);
	insere_texto(18,1+13*pos_check_in, 7, 12, imigrante, tela);
	atualiza_indice(18, 1+13*pos_check_in, id, tela);
	imprime(tela, altera_tela);
}

void pegar_certificado(int pos_check_in,int id,char**imigrante,char** vazio, char** tela, sem_t *altera_tela) {
	//posicao (2,7) tamanho (7,12) -> espaco de certificado
	//posicao (18, 1) tamanho (7, 12) -> checked in 0
	insere_texto(18,1+13*pos_check_in, 7, 12, vazio, tela);
	insere_texto(2,7, 7, 12, imigrante, tela);
	atualiza_indice(2, 7, id, tela);
	imprime(tela, altera_tela);
	sleep(2);
	insere_texto(18,1+13*pos_check_in, 7, 12, imigrante, tela);
	atualiza_indice(18, 1+13*pos_check_in, id, tela);
    insere_texto(2,7, 7, 12, vazio, tela);
    imprime(tela, altera_tela);
	
}

void sai_imigrante_check_in(int pos_fila, int id, int pos_check_in, char** imigrante, char** vazio, char** tela, sem_t *altera_tela) {
	//posicao (18, 1) tamanho (7, 12) -> checked in 0
	insere_texto(18,1+13*pos_check_in, 7, 12, vazio, tela);
	imprime(tela, altera_tela);
	insere_texto(27,1+13*pos_fila, 7, 12, imigrante, tela);
	atualiza_indice(27, 1+13*pos_fila, id, tela);
	imprime(tela, altera_tela);
	// insere_texto(27,1+13*pos_fila, 7, 12, vazio, tela);
	// imprime(tela, altera_tela);
}

void sai_imigrante_fila(int pos_fila, char** vazio, char** tela, sem_t * altera_tela) {
	insere_texto(27,1+13*pos_fila, 7, 12, vazio, tela);
	imprime(tela, altera_tela);
}

void entra_espectador(int pos, int id,char** espectator, char** tela, sem_t *altera_tela) {
	//posicao (10, 88) tamanho (7, 13) -> espectador 0
	insere_texto(10,85-13*pos, 7, 12, espectator, tela);
	atualiza_indice(10, 85-13*pos, id, tela);
	imprime(tela, altera_tela);
}

void espectar(int tempo) {
	sleep(tempo);
}

void sai_espectador(int pos, char** vazio, char** tela, sem_t *altera_tela) {
	//posicao (10, 88) tamanho (7, 12) -> espectador 0
    insere_texto(10,85-13*pos, 7, 12, vazio, tela);
    imprime(tela, altera_tela);
}

int verifica_posicao(int * fila) {
	for (int i = 0; i < 5; i++) {
		if (fila[i] == 0) {
			fila[i] = 1;
			return i;
		}
	}
	return -1;
}

void remove_posicao(int pos, int * fila) {
	fila[pos] = 0;

}
