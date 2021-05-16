#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include "rotinas.h"
#include <unistd.h>

void* rotina_imigrante (void *args) {
	int pos_fila; // guarda a posição em que a thread colocou o imigrante na fila para remoção posterior.
	int pos_check_in; // idem pos_fila
	args_imigrante* argumentos = (args_imigrante*) args;
	int * valor = malloc(sizeof(int));
	sem_getvalue(argumentos->imigrantes, valor);
	printf("O valor atual do semáforo é %d\n", *valor);
	sem_wait(argumentos->imigrantes); // garante que somente 5 imigrantes entrem na fila por vez.
	printf("PASSEI AQUI!\n");
	sem_wait(argumentos->inseri_imigrantes_fila); // garante que somente 1 imigrante seja inserido por vez.
	if (*argumentos->juiz_dentro == 0) {
		switch (*argumentos->num_imigrantes_fila)
		{
		case 0:
			// TODO
			/* inseri o imigrante de check-in de posição 0 */
			printf("Imigrante %d entrou na fila.\n", argumentos->indice);
			sleep(2);
			pos_fila = 0;
			break;
		case 1:
			// TODO
			/* inseri o imigrante de check-in de posição 1 */
			printf("Imigrante %d entrou na fila.\n", argumentos->indice);
			sleep(2);
			pos_fila = 1;
			break;
		case 2:
			// TODO
			/* inseri o imigrante de check-in de posição 2 */
			printf("Imigrante %d entrou na fila.\n", argumentos->indice);
			sleep(2);
			pos_fila = 2;
			break;
		case 3:
			// TODO
			/* inseri o imigrante de check-in de posição 3 */
			printf("Imigrante %d entrou na fila.\n", argumentos->indice);
			sleep(2);
			pos_fila = 3;
			break;								
		case 4:
			// TODO
			/* inseri o imigrante de check-in de posição 4 */
			printf("Imigrante %d entrou na fila.\n", argumentos->indice);
			sleep(2);
			pos_fila = 4;
			break;							
		default:
			break;
		}
		(*argumentos->num_imigrantes_fila)++;
		printf("O número atual de imigrantes na fila é %d\n", *argumentos->num_imigrantes_fila);				
	}
	sem_post(argumentos->inseri_imigrantes_fila); // garante que somente 1 imigrante seja inserido no check in por vez.		
	sleep(2);
	sem_wait(argumentos->check_in); // garante que somente 5 imigrantes façam check-in por vez.
	sem_wait(argumentos->inseri_imigrantes_check_in);
	switch (*argumentos->num_imigrantes_check_in)
	{
	case 0:
		// TO DO
		/* inseri o imigrante de check-in de posição 0 */
		printf("Imigrante %d fez check in.\n", argumentos->indice);
		(*argumentos->num_imigrantes_fila)--;
		printf("O número de imigrantes na fila é %d.\n", *argumentos->num_imigrantes_fila);
		sleep(2);
		pos_check_in = 0;
		break;
	case 1:
		// TO DO
		/* inseri o imigrante de check-in de posição 1 */
		printf("Imigrante %d fez check in.\n", argumentos->indice);
		(*argumentos->num_imigrantes_fila)--;
		printf("O número de imigrantes na fila é %d.\n", *argumentos->num_imigrantes_fila);
		sleep(2);
		pos_check_in = 1;
		break;
	case 2:
		// TO DO
		/* inseri o imigrante de check-in de posição 2 */
		printf("Imigrante %d fez check in.\n", argumentos->indice);
		(*argumentos->num_imigrantes_fila)--;
		printf("O número de imigrantes na fila é %d.\n", *argumentos->num_imigrantes_fila);
		sleep(2);
		pos_check_in = 2;
		break;
	case 3:
		// TO DO
		/* inseri o imigrante de check-in de posição 3 */
		printf("Imigrante %d fez check in.\n", argumentos->indice);
		(*argumentos->num_imigrantes_fila)--;
		printf("O número de imigrantes na fila é %d.\n", *argumentos->num_imigrantes_fila);
		sleep(2);
		pos_check_in = 3;
		break;								
	case 4:
		// TO DO
		/* inseri o imigrante de check-in de posição 4 */
		printf("Imigrante %d fez check in.\n", argumentos->indice);
		(*argumentos->num_imigrantes_fila)--;
		printf("O número de imigrantes na fila é %d.\n", *argumentos->num_imigrantes_fila);
		sleep(2);
		pos_check_in = 4;
		break;							
	default:
		break;
		}
	(*argumentos->num_imigrantes_check_in)++;
	printf("Valor atual de imigrantes no check_in é %d\n", *argumentos->num_imigrantes_check_in);
	sem_post(argumentos->inseri_imigrantes_check_in);
	sem_post(argumentos->imigrantes); // libera a inserção de um novo imigrante na fila.
	printf("Aguardando o juiz.");
	sem_post(argumentos->juiz_na_sala);
	sem_wait(argumentos->assentar);
	printf("Imigrante %d fez juramento.", argumentos->indice);
	// TO DO 
	// remove imigrante do check in e inseri na cadeira e aguarda certificado
	sem_wait(argumentos->certificado);
	printf("Imigrante %d recebeu certificado.", argumentos->indice);
	// TO DO
	// Aqui devo retornar o imigrante para o check in;
}

void* rotina_juiz (void* args) {
	args_juiz* argumentos = (args_juiz*) args;
	sleep(3);
	sem_wait(argumentos->juiz_na_sala);
		*argumentos->juiz_dentro = 1;
		printf("Juiz entrou na sala.\n");
		// TO DO
		// juiz entra na sala.
		for (int i = 0; i < *argumentos->num_imigrantes_check_in; i++) {
			sem_post(argumentos->assentar); // libera a entrada de um imigrante para juramento e certificação.
			sleep(2);
			sem_post(argumentos->certificado);
			// TO DO 
			// entrega o certificado
			printf("Voltando para o check in.");
		}
		// TO DO 
		// juiz confirma e sai da sala.
 

}

void* rotina_espectador (void* args) {
	int pos; // posição onde será inserido o espectador na tela.
	args_espectador* argumentos = (args_espectador*) args;
	sem_wait(argumentos->espectadores_fila); // garante que no máximo 5 espectador entra na sala por vez.
		if (*argumentos->juiz_dentro == 0) {
			sem_wait(argumentos->inseri_espectador); // garante que somente 1 espectador vai ser inserido por vez.
				switch (*argumentos->num_espectadores)
				{
					case 0:
					// TO DO
					// inserção do espectador na posição 0
					printf("Espectador %d entrou.\n", argumentos->indice);
					sleep(3);
						pos = 0;
						break;
					case 1:
					// TO DO
					// inserção do espectador na posição 1
					printf("Espectador %d entrou.\n", argumentos->indice);
					sleep(3);
						pos = 1;
						break;
					case 2:
					// TO DO
					// inserção do espectador na posição 2
					printf("Espectador %d entrou.\n", argumentos->indice);
					sleep(3);
						pos = 2;
						break;
					case 3:
					// TO DO
					// inserção do espectador na posição 3
					printf("Espectador %d entrou.\n", argumentos->indice);
					sleep(3);
						pos = 3;
						break;
					case 4:
					// TO DO
					// inserção do espectador na posição 4
					printf("Espectador %d entrou.\n", argumentos->indice);
					sleep(3);
						pos = 4;
						break;
					default:
						break;
				}
				(*argumentos->num_espectadores)++;
				printf("O número atual de espectadores na sala é %d\n", *argumentos->num_espectadores);
				sleep(3);
				sem_post(argumentos->inseri_espectador);
				// TO DO 
				// remover o espectador na posição pos. 
				// colocar tempo de espera.
		}
	sem_post(argumentos->espectadores_fila);
	(*argumentos->num_espectadores)--;
	printf("Espectador %d saiu da sala.\n", argumentos->indice);
}

//função espera e limpa tela
void wait_clear(){
	sleep(1);  //system("sleep 1");
	system("clear");  // should simply write the path to current shell
	printf("\a");
}

//função imprime tela
void imprime(char** tela){
	int linha = 35;
	int coluna = 100;
	// linha é o tamanho das linhas
	// coluna é o tamanho das colunas
	for (int i=0;i<linha;i++){
		for (int j=0;j<coluna;j++) {
			printf("%c",tela[i][j]);
		}
		printf("\n");
	}
	wait_clear();
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
	int Y = 10; //posiçoes fixa da linha do "?" no boneco
	tela[L+X][C+Y] = indice;
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

void entra_imigrante(int posfila,char** immigrant, char** tela) {
	//posicao (27, 1)  tamanho (7, 11) -> fila imigrantes 0
	insere_texto(27,1+12*posfila, 7, 11, immigrant, tela);
	imprime(tela);
}

void checkin_imigrante(int posfila, int poschekin,char** immigrant, char** vazio, char** tela) {
	//posicao (27, 1)  tamanho (7, 11) -> fila imigrantes 0
	//posicao (18, 1) tamanho (7, 11) -> checked in 0
	insere_texto(27,1+12*posfila, 7, 11, vazio, tela);
	insere_texto(18,1+12*poscheckin, 7, 11, immigrant, tela);
	imprime(tela);
}

void pegar_certificado(int poscheckin,char**immigrant,char** vazio, char** tela) {
	//posicao (2,7) tamanho (7,11) -> espaco de certificado
	//posicao (18, 1) tamanho (7, 11) -> checked in 0
	insere_texto(18,1+12*poscheckin, 7, 11, vazio, tela);
	insere_texto(2,7, 7, 11, immigrant, tela);
	imprime(tela);
	insere_texto(18,1+12*poscheckin, 7, 11, immigrant, tela);
        insere_texto(2,7, 7, 11, vazio, tela);
        imprime(tela);
	
}

void sai_imigrante(int poscheckin, char** vazio, char** tela) {

	//posicao (18, 1) tamanho (7, 11) -> checked in 0
	insere_texto(18,1+12*poscheckin, 7, 11, vazio, tela);
	imprime(tela);
}

void entra_espectador(int pos, char** spectator, char** tela) {
	//posicao (10, 88) tamanho (7, 11) -> espectador 0
	insere_texto(10,88-12*pos, 7, 11, spectator, tela);
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
