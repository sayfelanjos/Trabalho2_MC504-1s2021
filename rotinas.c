#include <semaphore.h>
#include <stdio.h>
#include "rotinas.h"
#include <unistd.h>

void* rotina_imigrante (void *args) {
	int pos_fila; // guarda a posição em que a thread colocou o imigrante na fila para remoção posterior.
	int pos_check_in; // idem pos_fila
	args_imigrante* argumentos = (args_imigrante*) args;
	sem_wait(argumentos->imigrantes_fila); // garante que somente 5 imigrantes entrem na fila por vez.
	sem_wait(argumentos->inseri_imigrante_fila); // garante que somente 1 imigrante seja inserido por vez.
		if (*argumentos->juiz_dentro == 0) {
			switch (*argumentos->num_imigrantes_fila)
			{
			case 0:
				// TODO
				/* inseri o imigrante de check-in de posição 0 */
				printf("Imigrante %d entrou na fila.\n", argumentos->indice);
				pos_fila = 0;
				break;
			case 1:
				// TODO
				/* inseri o imigrante de check-in de posição 1 */
				printf("Imigrante %d entrou na fila.\n", argumentos->indice);
				pos_fila = 1;
				break;
			case 2:
				// TODO
				/* inseri o imigrante de check-in de posição 2 */
				printf("Imigrante %d entrou na fila.\n", argumentos->indice);
				pos_fila = 2;
				break;
			case 3:
				// TODO
				/* inseri o imigrante de check-in de posição 3 */
				printf("Imigrante %d entrou na fila.\n", argumentos->indice);
				pos_fila = 3;
				break;								
			case 4:
				// TODO
				/* inseri o imigrante de check-in de posição 4 */
				printf("Imigrante %d entrou na fila.\n", argumentos->indice);
				pos_fila = 4;
				break;							
			default:
				break;
			}
			*argumentos->num_imigrantes_fila++;
			sem_post(argumentos->inseri_imigrante_fila); // libera a inserção de um novo imigrante na fila.
			sem_wait(argumentos->check_in); // garante que somente 5 imigrantes façam check-in por vez.
				sem_post(argumentos->juiz_na_sala); // habilita a entrada do juiz.
				sem_wait(argumentos->inseri_imigrante_check_in); // garante que somente 1 imigrante seja inserido no check in por vez.
					sem_post(argumentos->imigrantes_fila);
					switch (*argumentos->num_imigrantes_check_in)
					{
					case 0:
						// TO DO
						/* inseri o imigrante de check-in de posição 0 */
						printf("Imigrante %d fez check in.\n", argumentos->indice);
						pos_check_in = 0;
						break;
					case 1:
						// TO DO
						/* inseri o imigrante de check-in de posição 1 */
						printf("Imigrante %d fez check in.\n", argumentos->indice);
						pos_check_in = 1;
						break;
					case 2:
						// TO DO
						/* inseri o imigrante de check-in de posição 2 */
						printf("Imigrante %d fez check in.\n", argumentos->indice);
						pos_check_in = 2;
						break;
					case 3:
						// TO DO
						/* inseri o imigrante de check-in de posição 3 */
						printf("Imigrante %d fez check in.\n", argumentos->indice);
						pos_check_in = 3;
						break;								
					case 4:
						// TO DO
						/* inseri o imigrante de check-in de posição 4 */
						printf("Imigrante %d fez check in.\n", argumentos->indice);
						pos_check_in = 4;
						break;							
					default:
						break;
					}
					*argumentos->num_imigrantes_check_in++;
				sem_post(argumentos->inseri_imigrante_check_in);
				sem_wait(argumentos->assentar);
				// TO DO 
				// remove imigrante do check in e inseri na cadeira e aguarda certificado
					sem_wait(argumentos->certificado);
				// TO DO
				// Aqui devo retornar o imigrante para o check in;

				
		}	
}

void* rotina_juiz (void* args) {
	args_juiz* argumentos = (args_juiz*) args;
	sem_wait(argumentos->juiz_na_sala);
		*argumentos->juiz_dentro = 1;
		printf("Juiz entrou na sala.\n");
		// TO DO
		// juiz entra na sala.
		for (int i = 0; i < *argumentos->num_imigrantes_check_in; i++) {
			sem_post(argumentos->assentar); // libera a entrada de um imigrante para juramento e certificação.
			sleep(1);
			sem_post(argumentos->certificado);
			// TO DO 
			// entrega o certificado.
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
						pos = 0;
						break;
					case 1:
					// TO DO
					// inserção do espectador na posição 1
					printf("Espectador %d entrou.\n", argumentos->indice);
						pos = 1;
						break;
					case 2:
					// TO DO
					// inserção do espectador na posição 2
					printf("Espectador %d entrou.\n", argumentos->indice);
						pos = 2;
						break;
					case 3:
					// TO DO
					// inserção do espectador na posição 3
					printf("Espectador %d entrou.\n", argumentos->indice);
						pos = 3;
						break;
					case 4:
					// TO DO
					// inserção do espectador na posição 4
					printf("Espectador %d entrou.\n", argumentos->indice);
						pos = 4;
						break;
					default:
						break;
				}
				*argumentos->num_espectadores++;
				sem_post(argumentos->inseri_espectador);

				// TO DO 
				// remover o espectador na posição pos. 
				// colocar tempo de espera.
				*argumentos->num_espectadores--;

		}

	sem_post(argumentos->espectadores_fila);
}

//função espera e limpa tela
void wait_clear(){
	sleep(1);  //system("sleep 1");
	system("clear");  // should simply write the path to current shell
	printf("\a");
}

//função imprime tela
void imprime(int linha, int coluna, char** tela){
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