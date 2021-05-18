#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "rotinas.h"
#include <stdlib.h>
#include <unistd.h>


sem_t sair_sala; //semaforo que indica que o juiz ja confirmou

sem_t juiz_na_sala; // semaforo que indica que o juiz saiu do predio

sem_t espectadores_fila; // permite a entrada de novos espectadores

sem_t imigrantes_fila; // permite a entrada de novos imigrantes

sem_t assentar; // permite que somente um imigrante se assente por vez para certificação.

sem_t imigrantes_check_in; // permite a entrada de novos imigrantes para fazer o check-in

sem_t pega_certificado; // semaforos que indicam que a pessoa na cadeira i ja pegou seu certificado

sem_t inseri_espectador;

sem_t altera_tela;

sem_t inseri_imigrantes;

sem_t inseri_imigrantes_fila;

sem_t inseri_imigrantes_check_in;

sem_t pegou_certificado;


int main() {

	system("clear");

	// INICIO CRIA SEMAFOROS ----------------------------------------------

	sem_init(&pegou_certificado,0,0);

	sem_init(&inseri_imigrantes_check_in,0,1);

	sem_init(&inseri_imigrantes_fila,0,1);

	sem_init(&inseri_imigrantes,0,1);

	sem_init(&sair_sala,0,0); 

	sem_init(&juiz_na_sala,0,0); // sinaliza quando o juiz está na sala.

	sem_init(&espectadores_fila,0,5); // limita a quantidade de espectadores dentro da sala em 5.

	sem_init(&imigrantes_fila,0,5); // limita a quantidade de espectadores na fila em 5.

	sem_init(&assentar,0,0);

	sem_init(&imigrantes_check_in,0,5); // limita a quantidade de imigrantes fazendo check_in em 5.

	sem_init(&inseri_espectador,0,1); // garante que somente um espectador seja inserido por vez.

	sem_init(&altera_tela,0,1); // limita a uma thread por vez a alteração da tela.

	sem_init(&pega_certificado,0,0);


	//FIM CRIA SEMAFOROS -------------------------------------------------- 	
	
	//INICIO CRIA ESTRUTURAS AUXILIARES -----------------------------------
	
	//Aloca tela[35][100]

	char** tela;
	tela = malloc(LINHAS*sizeof(char*));
	for (int i=0;i<LINHAS;i++) {
		tela[i] = malloc(COLUNAS*sizeof(char));
	}

	args_imigrante args_imigrantes[NUM_IMIGRANTES];

	args_espectador args_espectadores[NUM_ESPECTADORES];

	args_juiz arg_juiz;

	int indice_imigrantes = 0; // índice inicial das threads

	int indice_espectadores = 0; // índice inicial das threads

	int juiz_dentro; // 0 se o juiz está fora e 1 caso contrário.

	int num_espectadores; // número de espectadores

	int num_imigrantes_fila; // número de imigrantes na fila 

	int num_imigrantes_check_in; // número de imigrantes fazendo check-in

	int posicao_espectador_fila[5] = {0, 0, 0, 0, 0};

	int posicao_imigrante_fila[5] = {0, 0, 0, 0, 0};

	int posicao_imigrante_check_in[5] = {0, 0, 0, 0, 0};

			//titulo
	char* titulo[73]= {                                                                                           
	"  #####                                    #####                         ", 
	" #     #  #####   ######  ######  #    #  #     #    ##    #####   ##### ",
	" #        #    #  #       #       ##   #  #         #  #   #    #  #    #", 
	" #  ####  #    #  #####   #####   # #  #  #        #    #  #    #  #    #", 
	" #     #  #####   #       #       #  # #  #        ######  #####   #    #", 
	" #     #  #   #   #       #       #   ##  #     #  #    #  #   #   #    #", 
	"  #####   #    #  ######  ######  #    #   #####   #    #  #    #  ##### "
	};

	//fim
	/*char* fim[25] = {
		"#######  #     #  ###### ", 
		"#        ##    #  #     #",
		"#        # #   #  #     #",
		"#####    #  #  #  #     #", 
		"#        #   # #  #     #", 
		"#        #    ##  #     #", 
		"#######  #     #  ###### "
		};*/
		
		//imagem1
	char* imagem1[100] = { //tela vazia
	"____________________________________________________________________________________________________",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|__________________________________________________________________________________________________|",	
	};             

	/*
	//imagem2
	char* imagem2[100] = { //tela somente com mensagens
	"__________________________________________COURT OF JUSTICE__________________________________________",
	"|  SWEAR/GET CERTIFICATE:                                                                          |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                       SPECTORS:                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|   CHECKED IN:                                                                                    |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|   ENTRY:                                                                                         |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|__________________________________________________________________________________________________|",	
	};
	*/
	
	char* imagem2[100] = { //tela somente com mensagens
	"__________________________________________COURT OF JUSTICE__________________________________________",
	"|SWEAR/GET CERTIFICATE:                                                                            |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|SPECTORS:-----------------------------------------------------------------------------------------|",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|CHECKED IN:---------------------------------------------------------------------------------------|",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|ENTRY:--------------------------------------------------------------------------------------------|",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|__________________________________________________________________________________________________|",	
	};

	/*char* imagem3[100] = { //tela cheia
	"__________________________________________COURT OF JUSTICE__________________________________________",
	"|  SWEAR/GET CERTIFICATE:                      Judge                                               |",
	"|      Immigrant ?                            @@@_@@@                                              |",
	"|         (^^)                               @@@/ \\@@@                                             |",
	"|        / || \\                              @@\\O O/@@                                             |",
	"|       c  xx  c                             @@@\\-/@@@                                             |",
	"|          ||                                @@@/ \\@@@                                             |",
	"|          ||                                  /\\|/\\                                               |",
	"|          LL                                                                                      |",
	"|                                       SPECTORS:                                                  |",
	"|                                       Spectator ? Spectator ? Spectator ? Spectator ? Spectator ?|",
	"|                                          (00)        (00)        (00)        (00)        (00)    |",
	"|                                         / || \\      / || \\      / || \\      / || \\      / || \\   |",
	"|                                        c  xx  c    c  xx  c    c  xx  c    c  xx  c    c  xx  c  |",
	"|                                           ||          ||          ||          ||          ||     |",
	"|                                           ||          ||          ||          ||          ||     |",
	"|                                           LL          LL          LL          LL          LL     |",
	"|   CHECKED IN:                                                                                    |",
	"|Immigrant ? Immigrant ? Immigrant ? Immigrant ? Immigrant ?                                       |",
	"|   (^^)        (^^)        (^^)        (^^)        (^^)                                           |",
	"|  / || \\      / || \\      / || \\      / || \\      / || \\                                          |",
	"| c  xx  c    c  xx  c    c  xx  c    c  xx  c    c  xx  c                                         |",
	"|    ||          ||          ||          ||          ||                                            |",
	"|    ||          ||          ||          ||          ||                                            |",
	"|    LL          LL          LL          LL          LL                                            |",
	"|                                                                                                  |",
	"|   ENTRY:                                                                                         |",
	"|Immigrant ? Immigrant ? Immigrant ? Immigrant ? Immigrant ?                                       |",
	"|   (^^)        (^^)        (^^)        (^^)        (^^)                                           |",
	"|  / || \\      / || \\      / || \\      / || \\      / || \\                                          |",
	"| c  xx  c    c  xx  c    c  xx  c    c  xx  c    c  xx  c                                         |",
	"|    ||          ||          ||          ||          ||                                            |",
	"|    ||          ||          ||          ||          ||                                            |",
	"|    LL          LL          LL          LL          LL                                            |",
	"|__________________________________________________________________________________________________|",
	};*/             
		
	char* vazio[13] = {
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	};

	char *imagem_imigrante[13] = {	
	"Immigrant  ??",
	"   (^^)      ",
	"  / || \\     ",
	" c  xx  c    ",
	"    ||       ",
	"    ||       ", 		
	"    LL       ",
	};

	char* imagem_espectador[13] = {  
	"Spectator  ??",
	"   (00)      ",
	"  / || \\     ",
	" c  xx  c    ",
	"    ||       ",
	"    ||       ",
	"    LL       ",
	};
		
	char* imagem_juiz[13] = {  
	"   Judge     ",
	"  @@@_@@@    ",
	" @@@/ \\@@@   ",
	" @@\\O O/@@   ",
	" @@@\\-/@@@   ",
	" @@@/ \\@@@   ",
	"   /\\|/\\     ",
	}; 
		
	char mensagem[16] = "\"confirmed!\" <--";
	char apaga[16]    = "                ";

	// FIM CRIA ESTRUTURAS AUXILIARES --------------------------------------
	
	// INICIO CRIA THREADS ------------------------------------------------

	pthread_t imigrantes[NUM_IMIGRANTES]; //threads para os imigrantes
	pthread_t espectadores[NUM_ESPECTADORES]; //threads para os espectadores
	pthread_t juiz; //thread para o juiz
	
	while(1) {	
		juiz_dentro = 0;
		num_espectadores = 0;
		num_imigrantes_fila = 0;
		num_imigrantes_check_in = 0;

		//INICIO CRIA PARAMETROS THREADS --------------------------------------
	
		for (int i=0;i<NUM_IMIGRANTES;i++) {
			args_imigrantes[i].indice = indice_imigrantes;
			args_imigrantes[i].num_imigrantes_check_in = &num_imigrantes_check_in;
			args_imigrantes[i].num_imigrantes_fila = &num_imigrantes_fila;
			args_imigrantes[i].juiz_dentro = &juiz_dentro;
			args_imigrantes[i].imagem_imigrante = imagem_imigrante;
			args_imigrantes[i].vazio = vazio;
			args_imigrantes[i].tela = tela;
			args_imigrantes[i].posicao_imigrante_fila = posicao_imigrante_fila;
			args_imigrantes[i].posicao_imigrante_check_in = posicao_imigrante_check_in;
			args_imigrantes[i].sair_sala = &sair_sala;
			args_imigrantes[i].juiz_na_sala = &juiz_na_sala;
			args_imigrantes[i].imigrantes = &imigrantes_fila;
			args_imigrantes[i].inseri_imigrantes_fila = &inseri_imigrantes_fila;	
			args_imigrantes[i].inseri_imigrantes_check_in = &inseri_imigrantes_check_in;
			args_imigrantes[i].altera_tela = &altera_tela;	 
			args_imigrantes[i].check_in = &imigrantes_check_in;
			args_imigrantes[i].pega_certificado = &pega_certificado;
			args_imigrantes[i].pegou_certificado = &pegou_certificado;
			indice_imigrantes++;
			if (indice_imigrantes > 99)
				indice_imigrantes = 0;
		}
		for (int i=0; i<NUM_ESPECTADORES; i++) {
			args_espectadores[i].indice = indice_espectadores;
			args_espectadores[i].num_espectadores = &num_espectadores;
			args_espectadores[i].juiz_dentro = &juiz_dentro;
			args_espectadores[i].imagem_espectador = imagem_espectador;
			args_espectadores[i].vazio = vazio;
			args_espectadores[i].tela = tela;
			args_espectadores[i].posicao_espectador_fila = posicao_espectador_fila;
			args_espectadores[i].inseri_espectador = &inseri_espectador;
			args_espectadores[i].juiz_na_sala = &juiz_na_sala;
			args_espectadores[i].espectadores_fila = &espectadores_fila;
			args_espectadores[i].altera_tela = &altera_tela;
			indice_espectadores++;
			if (indice_espectadores > 99)
				indice_espectadores = 0;
		}
		arg_juiz.juiz_dentro = &juiz_dentro;
		arg_juiz.num_imigrantes_check_in = &num_imigrantes_check_in;
		arg_juiz.imagem_juiz = imagem_juiz;
		arg_juiz.mensagem_confirma = mensagem;
		arg_juiz.mensagem_apaga = apaga;
		arg_juiz.tela = tela;
		arg_juiz.vazio = vazio;
		arg_juiz.sair_sala = &sair_sala;
		arg_juiz.juiz_na_sala = &juiz_na_sala;
		arg_juiz.altera_tela = &altera_tela;
		arg_juiz.pega_certificado = &pega_certificado;
		arg_juiz.pegou_certificado = &pegou_certificado;

		// FIM CRIA PARAMETROS THREADS -----------------------------------------

		// INICIO IMPRIMIR IMAGENS DE INTRODUCAO -----------------------

		// Esvazia a tela
    	insere_texto(0, 0, LINHAS, COLUNAS, imagem1, tela);
   		// insere titulo
    	insere_texto(12, 15, 7, 73, titulo, tela);
        //imprime titulo
        imprime(tela, &altera_tela);
		sleep(1);		
    	// Esvazia a tela
    	insere_texto(0, 0, LINHAS, COLUNAS, imagem1, tela);
    	// insere immigrant
    	insere_texto(12, 42, 7, 11, imagem_imigrante, tela);        
    	// imprime immigrant
		imprime(tela, &altera_tela);
		sleep(1);
        // Esvazia a tela
    	insere_texto(0, 0, LINHAS, COLUNAS, imagem1, tela);
  		// insere spectator
    	insere_texto(12, 42, 7, 11, imagem_espectador, tela);        
    	// imprime spectator
        imprime(tela, &altera_tela);
		sleep(1);
		// Esvazia a tela
    	insere_texto(0, 0, LINHAS, COLUNAS, imagem1, tela);
    	// insere judge
    	insere_texto(12, 42, 7, 11, imagem_juiz, tela);        
    	// imprime judge
        imprime(tela, &altera_tela);
		sleep(1);
		// Esvazio a tela
		insere_texto(0, 0, LINHAS, COLUNAS, imagem2, tela);

		// FIM IMPRIMIR IMAGENS DE INTRODUCAO --------------------------

		// INICIO CRIA THREADS ---------------------------------------------------

		if (pthread_create(&juiz,NULL,rotina_juiz, &arg_juiz) != 0) { // cria a thread do juiz
			perror("Erro na criacao da thread do juiz.\n"); //testa se ocorreu um erro na criacao da thread do juiz
		}
		for (int i=0;i<NUM_IMIGRANTES;i++) {
			if (pthread_create(&imigrantes[i],NULL,rotina_imigrante, &args_imigrantes[i]) != 0) { // cria a thread do imigrante i
				perror("Erro na criacao da thread do imigrante.\n"); 
			}
			// sleep(2);
		}
		for (int i=0; i<NUM_ESPECTADORES;i++) {
			if (pthread_create(&espectadores[i],NULL,rotina_espectador, &args_espectadores[i]) != 0) { // cria a threads do espectador i
				perror("Erro na criacao da thread do espectador."); 
			}
		}
		for (int i=0; i < NUM_IMIGRANTES; i++) {
			if (pthread_join(imigrantes[i], NULL) != 0) {
				perror("Falha em join imigrantes.");
			}
		}
		for (int i=0; i < NUM_ESPECTADORES; i++) {
			if (pthread_join(espectadores[i], NULL) != 0) {
				perror("Falha em join espectadores.");
			}
		}
		if (pthread_join(juiz, NULL) != 0) {
			perror("Falha em join juiz.");
		}
	}

    // FIM CRIA THREADS ----------
	
	free (tela) ;

	return 0;
	
}