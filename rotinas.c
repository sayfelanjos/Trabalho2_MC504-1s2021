#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include "rotinas.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void* rotina_imigrante (void *args) {
	char pos_fila; // guarda a posição em que a thread colocou o imigrante na fila para remoção posterior.
	int pos_check_in; // idem pos_fila
	args_imigrante* argumentos = (args_imigrante*) args;
	int * valor = malloc(sizeof(int));
	sem_getvalue(argumentos->imigrantes, valor);
	sem_wait(argumentos->imigrantes); // garante que somente 5 imigrantes entrem na fila por vez.
	sem_wait(argumentos->inseri_imigrantes_fila); // garante que somente 1 imigrante seja inserido por vez.
	if (*argumentos->juiz_dentro == 0) {
		switch (*argumentos->num_imigrantes_fila)
		{
		case 0:
			entra_imigrante(0, argumentos->imagem_imigrante, argumentos->tela);
			sleep(1);
			pos_fila = 0;
			break;
		case 1:
			entra_imigrante(1, argumentos->imagem_imigrante, argumentos->tela);
			sleep(1);
			pos_fila = 1;
			break;
		case 2:
			entra_imigrante(2, argumentos->imagem_imigrante, argumentos->tela);
			sleep(1);
			pos_fila = 2;
			break;
		case 3:
			entra_imigrante(3, argumentos->imagem_imigrante, argumentos->tela);
			sleep(1);
			pos_fila = 3;
			break;								
		case 4:
			entra_imigrante(4, argumentos->imagem_imigrante, argumentos->tela);
			sleep(1);
			pos_fila = 4;
			break;							
		default:
			break;
		}
		(*argumentos->num_imigrantes_fila)++;
	}
	sem_post(argumentos->inseri_imigrantes_fila); // garante que somente 1 imigrante seja inserido no check in por vez.		
	sleep(1);
	sem_wait(argumentos->check_in); // garante que somente 5 imigrantes façam check-in por vez.
	sem_wait(argumentos->inseri_imigrantes_check_in);
	switch (*argumentos->num_imigrantes_check_in)
	{
	case 0:
		checkin_imigrante(pos_fila, 0 , argumentos->imagem_imigrante, argumentos->vazio, argumentos->tela);
		(*argumentos->num_imigrantes_fila)--;
		sleep(1);
		pos_check_in = 0;
		break;
	case 1:
		checkin_imigrante(pos_fila, 1 , argumentos->imagem_imigrante, argumentos->vazio, argumentos->tela);
		(*argumentos->num_imigrantes_fila)--;
		sleep(1);
		pos_check_in = 1;
		break;
	case 2:
		checkin_imigrante(pos_fila, 2 , argumentos->imagem_imigrante, argumentos->vazio, argumentos->tela);
		(*argumentos->num_imigrantes_fila)--;
		sleep(1);
		pos_check_in = 2;
		break;
	case 3:
		checkin_imigrante(pos_fila, 3 , argumentos->imagem_imigrante, argumentos->vazio, argumentos->tela);
		(*argumentos->num_imigrantes_fila)--;
		sleep(1);
		pos_check_in = 3;
		break;								
	case 4:
		checkin_imigrante(pos_fila, 4 , argumentos->imagem_imigrante, argumentos->vazio, argumentos->tela);
		(*argumentos->num_imigrantes_fila)--;
		sleep(1);
		pos_check_in = 4;
		break;							
	default:
		break;
		}
	(*argumentos->num_imigrantes_check_in)++;
	sem_post(argumentos->inseri_imigrantes_check_in);
	sem_post(argumentos->imigrantes); // libera a inserção de um novo imigrante na fila.
	sem_post(argumentos->juiz_na_sala);
	sem_wait(argumentos->assentar);
	pegar_certificado(pos_check_in, argumentos->imagem_imigrante, argumentos->vazio, argumentos->tela);
	sem_wait(argumentos->certificado);
	pegar_certificado(pos_check_in, argumentos->imagem_imigrante, argumentos->vazio, argumentos->tela);
}

void* rotina_juiz (void* args) {
	args_juiz* argumentos = (args_juiz*) args;
	sleep(5);
	sem_wait(argumentos->juiz_na_sala);
	*argumentos->juiz_dentro = 1;
	entra_juiz(argumentos->imagem_juiz, argumentos->tela);
	for (int i = 0; i < *argumentos->num_imigrantes_check_in; i++) {
		sem_post(argumentos->assentar); // libera a entrada de um imigrante para juramento e certificação.
		sleep(1);
		sem_post(argumentos->certificado);
		sleep(1);
	}
	juiz_confirma(argumentos->mensagem_confirma, argumentos->mensagem_apaga, argumentos->tela);
}

void* rotina_espectador (void* args) {
	args_espectador* argumentos = (args_espectador*) args;
	sem_wait(argumentos->espectadores_fila); // garante que no máximo 5 espectador entra na sala por vez.
	if (*argumentos->juiz_dentro == 0) {
		sem_wait(argumentos->inseri_espectador); // garante que somente 1 espectador vai ser inserido por vez.
		entra_espectador(verifica_posicao(argumentos->posicao_espectador_fila), argumentos->imagem_espectador, argumentos->tela);
		sleep(1);
		sem_post(argumentos->inseri_espectador);
	}
	sleep(2);
	sai_espectador(verifica_posicao(argumentos->posicao_espectador_fila), argumentos->vazio, argumentos->tela);
	remove_posicao(verifica_posicao(argumentos->posicao_espectador_fila), argumentos->posicao_espectador_fila);
	sem_post(argumentos->espectadores_fila);
}

//função espera e limpa tela
void wait_clear(){
	sleep(1);  //system("sleep 1");
	system("clear");  // should simply write the path to current shell
	printf("\a");
}

//função imprime tela
void imprime(char** tela){
	// linha é o tamanho das linhas
	// coluna é o tamanho das colunas
	wait_clear();
	for (int i=0;i<LINHAS;i++){
		for (int j=0;j<COLUNAS;j++) {
			printf("%c",tela[i][j]);
		}
		printf("\n");
	}
}

//função insere boneco na tela
void insere_texto(int L, int C, int linha, int coluna, char** texto, char** tela){
	// L é linha de origem
	// C é coluna de origem
	// linha é tamanho das linhas
	// coluna é tamanho das colunas
	//LEGENDA:
        //posicao (2,7) tamanho (7,11) -> espaco de certificado
        //posicao (10,40) tamanho (7,11) -> espectador 4
        //posicao (10, 52) tamanho (7, 11) -> espectador 3
        //posicao (10, 64) tamanho (7, 11) -> espectador 2
        //posicao (10, 76) tamanho (7, 11) -> espectador 1
        //posicao (10, 88) tamanho (7, 11) -> espectador 0
        //posicao (18, 1) tamanho (7, 11) -> checked in 0
        //posicao (18, 13) tamanho (7, 11) -> cheked in 1
        //posicao (18, 25) tamanho (7, 11) -> checked in 2
        //posicao (18, 37) tamanho (7, 11) -> checked in 3
        //posicao (18, 49) tamanho (7, 11) -> checked in 4
        //posicao (27, 1)  tamanho (7, 11) -> fila imigrantes 0
        //posicao (27, 13) tamanho (7, 11) -> fila imigrantes 1
        //posicao (27, 25) tamanho (7, 11) -> fila imigrantes 2
        //posicao (27, 37) tamanho (7, 11) -> fila imigrantes 3
        //posicao (27, 49) tamanho (7, 11) -> fila imigrantes 4
        //posicao (1, 45) tamanho (7, 11) -> juiz

	for (int i=0;i<linha;i++) {
		for (int j=0;j<coluna;j++) {
			tela[L+i][C+j]=texto[i][j];
		}
	}
}

//função que atualiza indice dos bonecos
void atualiza_indice(int L, int C, char indice, char** tela){
	int X = 0; //posiçoes fixa da linha do "?" no boneco
	int Y = 9; //posiçoes fixa da coluna do "?" no boneco
	if (indice<10) {
		tela[L+X][C+Y] = '0';
		Y++;
		tela[L+X][C+Y] = indice;
	}
	else {
		tela[L+X][C+Y] = indice/10;
		Y++;
		tela[L+X][C+Y] = indice%10;
	}
}

//funçao imprime mensagem de confirmação
void confirmed(char* mensagem, char** tela){
	int X = 5;
	int Y = 28;
	for (int j=0;j<16;j++){
		tela[X][Y+j]=mensagem[j];
	}
}

void entra_juiz(char** judge,char** tela) {
	//posicao (1, 45) tamanho (7, 11) -> juiz
	insere_texto(1,45, 7, 11, judge, tela);
	imprime(tela);
}

void juiz_confirma(char* mensagem, char* apaga, char** tela) {
	confirmed(mensagem,tela);
	imprime(tela);
	confirmed(apaga,tela);
	imprime(tela);
}

void sai_juiz(char** vazio, char** tela) {
	//posicao (1, 45) tamanho (7, 11) -> juiz
	insere_texto(1,45, 7, 11, vazio, tela);
	imprime(tela);
}

void entra_imigrante(int pos_fila,int id,char** immigrante, char** tela) {
	//posicao (27, 1)  tamanho (7, 11) -> fila imigrantes 0
	insere_texto(27,1+12*pos_fila, 7, 11, immigrante, tela);
	atualiza_indice(27, 1+12*pos_fila, id, tela);
	imprime(tela);
}

void checkin_imigrante(int pos_fila, int pos_chekin,int id,char** imigrante, char** vazio, char** tela) {
	//posicao (27, 1)  tamanho (7, 11) -> fila imigrantes 0
	//posicao (18, 1) tamanho (7, 11) -> checked in 0
	insere_texto(27,1+12*pos_fila, 7, 11, vazio, tela);
	insere_texto(18,1+12*pos_chekin, 7, 11, imigrante, tela);
	atualiza_indice(18, 1+12*pos_checkin, id, tela);
	imprime(tela);
}

void pegar_certificado(int pos_checkin,int id,char**imigrante,char** vazio, char** tela) {
	//posicao (2,7) tamanho (7,11) -> espaco de certificado
	//posicao (18, 1) tamanho (7, 11) -> checked in 0
	insere_texto(18,1+12*pos_checkin, 7, 11, vazio, tela);
	insere_texto(2,7, 7, 11, imigrante, tela);
	atualiza_indice(2, 7, id, tela);
	imprime(tela);
	insere_texto(18,1+12*pos_checkin, 7, 11, imigrante, tela);
	atualiza_indice(18, 1+12*pos_checkin, id, tela);
    	insere_texto(2,7, 7, 11, vazio, tela);
    	imprime(tela);
	
}

void sai_imigrante(int pos_checkin, char** vazio, char** tela) {
	//posicao (18, 1) tamanho (7, 11) -> checked in 0
	insere_texto(18,1+12*pos_checkin, 7, 11, vazio, tela);
	imprime(tela);
}

void entra_espectador(int pos, int id,char** espectator, char** tela) {
	//posicao (10, 88) tamanho (7, 11) -> espectador 0
	insere_texto(10,88-12*pos, 7, 11, espectator, tela);
	atualiza_indice(10, 88-12*pos, id, tela);
	imprime(tela);
}

void espectar(int tempo) {
	sleep(tempo);
}

void sai_espectador(int pos, char** vazio, char** tela) {
	//posicao (10, 88) tamanho (7, 11) -> espectador 0
    insere_texto(10,88-12*pos, 7, 11, vazio, tela);
    imprime(tela);
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

void remove_posicao(char pos, char * fila) {
	fila[(int)pos] = 0;
}