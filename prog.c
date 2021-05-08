#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
	 
//função espera e limpa tela
void wait_clear(){
	sleep(2);  //system("sleep 1");
	system("clear");  // should simply write the path to current shell
	printf("\a");
}

//função imprime tela
void imprime(int linha, int coluna, char** tela){
	// linha é tamanho das linhas
	// coluna é tamanho das colunas
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


int main(void){
	system("clear"); 
		
	//Aloca tela[35][100]
	char** tela;
	tela = malloc(35*sizeof(char*));
	for (int i=0;i<35;i++) {
		tela[i] = malloc(100*sizeof(char));
	}
	
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
	char* fim[25] = {
	 "#######  #     #  ###### ", 
	 "#        ##    #  #     #",
	 "#        # #   #  #     #",
	 "#####    #  #  #  #     #", 
	 "#        #   # #  #     #", 
	 "#        #    ##  #     #", 
	 "#######  #     #  ###### "
	 };
        
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

        char* imagem3[100] = { //tela cheia
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
	};             
       
       char* vazio[11] = { 
	"           ",
	"           ",
	"           ",
	"           ",
	"           ",
	"           ", 
	"           ",
	};
       
	char* immigrant[11] = { 
	"Immigrant ?",
	"   (^^)    ",
	"  / || \\   ",
	" c  xx  c  ",
	"    ||     ",
	"    ||     ", 
	"    LL     ",
	};
	
	char* spectator[11] = {  
	"Spectator ?",
        "   (00)    ",
        "  / || \\   ",
        " c  xx  c  ",
        "    ||     ",
        "    ||     ",
        "    LL     ",
        };
        
        char* judge[11] = {  
        "   Judge   ",
        "  @@@_@@@  ",
        " @@@/ \\@@@ ",
        " @@\\O O/@@ ",
        " @@@\\-/@@@ ",
        " @@@/ \\@@@ ",
        "   /\\|/\\   ",
        }; 
        
        char mensagem[16] = "\"confirmed!\" <--";
        char apaga[16]    = "                ";
        
        //insere imagem1
        insere_texto(0, 0, 35, 100, imagem1, tela);
        //insere titulo
        insere_texto(12, 15, 7, 73, titulo, tela);
	//imprime titulo
	imprime(35, 100, tela);
	
        //insere imagem1
        insere_texto(0, 0, 35, 100, imagem1, tela);
        //insere immigrant
        insere_texto(12, 42, 7, 11, immigrant, tela);        
        //imprime immigrant                                                	
	imprime(35, 100, tela);
	
	 //insere imagem1
        insere_texto(0, 0, 35, 100, imagem1, tela);
        //insere spectator
        insere_texto(12, 42, 7, 11, spectator, tela);        
        //imprime spectator                                                	
	imprime(35, 100, tela);
	
	//insere imagem1
        insere_texto(0, 0, 35, 100, imagem1, tela);
        //insere judge
        insere_texto(12, 42, 7, 11, judge, tela);        
        //imprime judge                                                	
	imprime(35, 100, tela);
	
	//insere imagem2
	insere_texto(0, 0, 35, 100, imagem2, tela);        
        //imprime imagem2                                                	
	imprime(35, 100, tela);	
	
	//insere imagem3
	insere_texto(0, 0, 35, 100, imagem3, tela);        
        //imprime imagem3                                               	
	imprime(35, 100, tela);
		
	//atualiza indice
	atualiza_indice(27, 1, '1', tela); // ENTRY: 1
	atualiza_indice(27, 13, '2', tela); // ENTRY: 2
	atualiza_indice(27, 25, '3', tela); // ENTRY: 3
	atualiza_indice(27, 37, '4', tela); // ENTRY: 4
	atualiza_indice(27, 49, '5', tela); // ENTRY: 5
	atualiza_indice(18, 1, '1', tela); // CHECKED IN: 1
	atualiza_indice(18, 13, '2', tela); // CHECKED IN: 2
	atualiza_indice(18, 25, '3', tela); // CHECKED IN: 3
	atualiza_indice(18, 37, '4', tela); // CHECKED IN: 4
	atualiza_indice(18, 49, '5', tela); // CHECKED IN: 5
	atualiza_indice(10, 40, '1', tela); // SPECTORS: 1
	atualiza_indice(10, 52, '2', tela); // SPECTORS: 2
	atualiza_indice(10, 64, '3', tela); // SPECTORS: 3
	atualiza_indice(10, 76, '4', tela); // SPECTORS: 4
	atualiza_indice(10, 88, '5', tela); // SPECTORS: 5
	atualiza_indice(2, 7, 'X', tela); // SWEAR/GET CERTIFICATE: X
	//imprime indice   
	imprime(35, 100, tela);
	
	//insere mensagem de confirmação
	confirmed(mensagem, tela);
        //imprime mensagem de confirmação                                         	
	imprime(35, 100, tela);
	
        //insere vazio
        insere_texto(2, 7, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
	//insere mensagem apaga
	confirmed(apaga, tela);
        //imprime mensagem apaga                                        	
	imprime(35, 100, tela);
	
	//insere vazio
        insere_texto(10, 40, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
	 //insere vazio
        insere_texto(10, 52, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
        //insere vazio
        insere_texto(10, 64, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);

	 //insere vazio
        insere_texto(10, 76, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
	 //insere vazio
        insere_texto(10, 88, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
	//insere vazio
        insere_texto(18, 1, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
	 //insere vazio
        insere_texto(18, 13, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
        //insere vazio
        insere_texto(18, 25, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);

	 //insere vazio
        insere_texto(18, 37, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);

	 //insere vazio
        insere_texto(18, 49, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
		
        //insere vazio
        insere_texto(27, 1, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);

	 //insere vazio
        insere_texto(27, 13, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
	 //insere vazio
        insere_texto(27, 25, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
        //insere vazio
        insere_texto(27, 37, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);

	 //insere vazio
        insere_texto(27, 49, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
	//insere vazio - judge
        insere_texto(1, 45, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(35, 100, tela);
	
	//insere boneco
        insere_texto(10, 40, 7, 11, spectator, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
	
	 //insere boneco
        insere_texto(10, 52, 7, 11, spectator, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
	
        //insere boneco
        insere_texto(10, 64, 7, 11, spectator, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);

	 //insere boneco
        insere_texto(10, 76, 7, 11, spectator, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
	
	 //insere boneco
        insere_texto(10, 88, 7, 11, spectator, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
	
	//insere boneco
        insere_texto(18, 1, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
	
	 //insere boneco
        insere_texto(18, 13, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
	
        //insere boneco
        insere_texto(18, 25, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);

	 //insere boneco
        insere_texto(18, 37, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);

	 //insere boneco
        insere_texto(18, 49, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
		
        //insere boneco
        insere_texto(27, 1, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);

	 //insere boneco
        insere_texto(27, 13, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
	
	 //insere boneco
        insere_texto(27, 25, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
	
        //insere boneco
        insere_texto(27, 37, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);

	 //insere boneco
        insere_texto(27, 49, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
	
	//insere boneco - judge
        insere_texto(1, 45, 7, 11, judge, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
	
	//insere boneco
        insere_texto(2, 7, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(35, 100, tela);
			
        //insere imagem1
        insere_texto(0, 0, 35, 100, imagem1, tela);
        //insere fim
        insere_texto(12, 35, 7, 25, fim, tela);
	//imprime fim
	imprime(35, 100, tela);
	
	// libera a memória da matri  tela
	for (int i=0; i <35; i++)
  		free (tela[i]) ;
	free (tela) ;
	
	return 0;
}
