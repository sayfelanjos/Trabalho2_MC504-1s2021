#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
	 
typedef struct {
	int x;
	int y;
} boneco;

//função espera e limpa tela
void wait_clear(){
	sleep(2);  //system("sleep 1");
	system("clear");  // should simply write the path to current shell
	printf("\a");
}

//função imprime tela
void imprime(char** tela){
	int linha = 35;// linha é tamanho das linhas
	int coluna = 100;// coluna é tamanho das colunas
	for (int i=0;i<linha;i++){
		for (int j=0;j<coluna;j++) {
			printf("%c",tela[i][j]);
		}
		printf("\n");
	}
	wait_clear();
}

//função insere texto na tela
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

//função insere boneco na tela
void insere_boneco(boneco boneco, char** texto, char** tela){
	insere_texto(boneco.x, boneco.y, 7, 11, texto, tela);
}

//função que atualiza indice dos bonecos
void atualiza_indice(boneco boneco, int indice, char** tela){
	char indice1 = '0' + (char) indice/10;
	char indice2 = '0' + (char) indice%10;
	int X = 0; //posiçoes fixa da linha desena "?_" no boneco
	int Y = 9; //posiçoes fixa da coluna desena "?_" no boneco
	tela[boneco.x+X][boneco.y+Y] = indice1;
	X = 0; //posiçoes fixa da linha unidade "_?" no boneco
	Y = 10; //posiçoes fixa da coluna unidade "_?" no boneco
	tela[boneco.x+X][boneco.y+Y] = indice2;
}

//funçao imprime mensagem de confirmação
void confirmed(char* mensagem, char** tela){
	int X = 5; // posiçao da linha
	int Y = 28; // posição da coluna
	int tam = 16; // tamanho da mensagem
	for (int j=0;j<tam;j++){
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
	
	//atribuindo posições para os bonecos
	boneco boneco1;// ENTRY: 1
	boneco1.x = 27;
	boneco1.y = 1; 
	boneco boneco2;// ENTRY: 2
	boneco2.x = 27;
	boneco2.y = 13; 
	boneco boneco3;// ENTRY: 3
	boneco3.x = 27;
	boneco3.y = 25; 
	boneco boneco4;// ENTRY: 4
	boneco4.x = 27;
	boneco4.y = 37; 
	boneco boneco5;// ENTRY: 5
	boneco5.x = 27;
	boneco5.y = 49; 
	boneco boneco6;// CHECKED IN: 6
	boneco6.x = 18;
	boneco6.y = 1;
	boneco boneco7;// CHECKED IN: 7
	boneco7.x = 18;
	boneco7.y = 13; 
	boneco boneco8;// CHECKED IN: 8
	boneco8.x = 18;
	boneco8.y = 25; 
	boneco boneco9;// CHECKED IN: 9
	boneco9.x = 18;
	boneco9.y = 37; 
	boneco boneco10;// CHECKED IN: 10
	boneco10.x = 18;
	boneco10.y = 49; 
	boneco boneco11;// SPECTORS: 11
	boneco11.x = 10;
	boneco11.y = 40; 
	boneco boneco12;// SPECTORS: 12
	boneco12.x = 10;
	boneco12.y = 52; 
	boneco boneco13;// SPECTORS: 13
	boneco13.x = 10;
	boneco13.y = 64; 
	boneco boneco14;// SPECTORS: 14
	boneco14.x = 10;
	boneco14.y = 76; 
	boneco boneco15;// SPECTORS: 15
	boneco15.x = 10;
	boneco15.y = 88; 
	boneco boneco16;//SWEAR/GET CERTIFICATE: 16
	boneco16.x = 2;
	boneco16.y = 7; 
	boneco boneco17;// JUDGE
	boneco17.x = 1;
	boneco17.y = 45; 
		
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
	
	 //imagem2
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

        char* imagem3[100] = { //tela cheia
	"__________________________________________COURT OF JUSTICE__________________________________________",
	"|  SWEAR/GET CERTIFICATE:                      Judge                                               |",
	"|      Immigrant??                            @@@_@@@                                              |",
	"|         (^^)                               @@@/ \\@@@                                             |",
	"|        / || \\                              @@\\O O/@@                                             |",
	"|       c  xx  c                             @@@\\-/@@@                                             |",
	"|          ||                                @@@/ \\@@@                                             |",
	"|          ||                                  /\\|/\\                                               |",
	"|          LL                                                                                      |",
	"|                                       SPECTORS:                                                  |",
	"|                                       Spectator?? Spectator?? Spectator?? Spectator?? Spectator??|",
	"|                                          (00)        (00)        (00)        (00)        (00)    |",
	"|                                         / || \\      / || \\      / || \\      / || \\      / || \\   |",
	"|                                        c  xx  c    c  xx  c    c  xx  c    c  xx  c    c  xx  c  |",
	"|                                           ||          ||          ||          ||          ||     |",
	"|                                           ||          ||          ||          ||          ||     |",
	"|                                           LL          LL          LL          LL          LL     |",
	"|   CHECKED IN:                                                                                    |",
	"|Immigrant?? Immigrant?? Immigrant?? Immigrant?? Immigrant??                                       |",
	"|   (^^)        (^^)        (^^)        (^^)        (^^)                                           |",
	"|  / || \\      / || \\      / || \\      / || \\      / || \\                                          |",
	"| c  xx  c    c  xx  c    c  xx  c    c  xx  c    c  xx  c                                         |",
	"|    ||          ||          ||          ||          ||                                            |",
	"|    ||          ||          ||          ||          ||                                            |",
	"|    LL          LL          LL          LL          LL                                            |",
	"|                                                                                                  |",
	"|   ENTRY:                                                                                         |",
	"|Immigrant?? Immigrant?? Immigrant?? Immigrant?? Immigrant??                                       |",
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
	"Immigrant??",
	"   (^^)    ",
	"  / || \\   ",
	" c  xx  c  ",
	"    ||     ",
	"    ||     ", 
	"    LL     ",
	};
	
	char* spectator[11] = {  
	"Spectator??",
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
	imprime(tela);
	
        //insere imagem1
        insere_texto(0, 0, 35, 100, imagem1, tela);
        //insere immigrant
        insere_texto(12, 42, 7, 11, immigrant, tela);        
        //imprime immigrant                                                	
	imprime(tela);
	
	 //insere imagem1
        insere_texto(0, 0, 35, 100, imagem1, tela);
        //insere spectator
        insere_texto(12, 42, 7, 11, spectator, tela);        
        //imprime spectator                                                	
	imprime(tela);
	
	//insere imagem1
        insere_texto(0, 0, 35, 100, imagem1, tela);
        //insere judge
        insere_texto(12, 42, 7, 11, judge, tela);        
        //imprime judge                                                	
	imprime(tela);
	
	//insere imagem2
	insere_texto(0, 0, 35, 100, imagem2, tela);        
        //imprime imagem2                                                	
	imprime(tela);	
	
	/*
	//insere imagem3
	insere_texto(0, 0, 35, 100, imagem3, tela);        
        //imprime imagem3                                               	
	imprime(tela);
	*/
	
	
	/*
        //insere vazio
        insere_boneco(boneco16, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	
	//insere mensagem apaga
	confirmed(apaga, tela);
        //imprime mensagem apaga                                        	
	imprime(tela);
	
	//insere vazio
        insere_texto(10, 40, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	
	 //insere vazio
        insere_texto(10, 52, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	
        //insere vazio
        insere_texto(10, 64, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);

	 //insere vazio
        insere_texto(10, 76, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	
	 //insere vazio
        insere_texto(10, 88, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	
	//insere vazio
        insere_texto(18, 1, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	
	 //insere vazio
        insere_texto(18, 13, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	
        //insere vazio
        insere_texto(18, 25, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);

	 //insere vazio
        insere_texto(18, 37, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);

	 //insere vazio
        insere_texto(18, 49, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
		
        //insere vazio
        insere_texto(27, 1, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);

	 //insere vazio
        insere_texto(27, 13, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	
	 //insere vazio
        insere_texto(27, 25, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	
        //insere vazio
        insere_texto(27, 37, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);

	 //insere vazio
        insere_texto(27, 49, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	
	//insere vazio - judge
        insere_texto(1, 45, 7, 11, vazio, tela);        
        //imprime vazio                                                	
	imprime(tela);
	*/
	
	//insere boneco
        insere_texto(10, 40, 7, 11, spectator, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
	 //insere boneco
        insere_texto(10, 52, 7, 11, spectator, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
        //insere boneco
        insere_texto(10, 64, 7, 11, spectator, tela);        
        //imprime boneco                                                	
	imprime(tela);

	 //insere boneco
        insere_texto(10, 76, 7, 11, spectator, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
	 //insere boneco
        insere_texto(10, 88, 7, 11, spectator, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
	//insere boneco
        insere_texto(18, 1, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
	 //insere boneco
        insere_texto(18, 13, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
        //insere boneco
        insere_texto(18, 25, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);

	 //insere boneco
        insere_texto(18, 37, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);

	 //insere boneco
        insere_texto(18, 49, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);
		
        //insere boneco
        insere_texto(27, 1, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);

	 //insere boneco
        insere_texto(27, 13, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
	 //insere boneco
        insere_texto(27, 25, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
        //insere boneco
        insere_texto(27, 37, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);

	 //insere boneco
        insere_texto(27, 49, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
	//insere boneco - judge
        insere_texto(1, 45, 7, 11, judge, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
	//insere boneco
        insere_texto(2, 7, 7, 11, immigrant, tela);        
        //imprime boneco                                                	
	imprime(tela);
	
	//atualiza indices		
	atualiza_indice(boneco1, 1, tela); // ENTRY: 1
	atualiza_indice(boneco2, 2, tela); // ENTRY: 2
	atualiza_indice(boneco3,3, tela); // ENTRY: 3
	atualiza_indice(boneco4,4, tela); // ENTRY: 4
	atualiza_indice(boneco5,5, tela); // ENTRY: 5
	atualiza_indice(boneco6,6, tela); // CHECKED IN: 6
	atualiza_indice(boneco7,7, tela); // CHECKED IN: 7
	atualiza_indice(boneco8,8, tela); // CHECKED IN: 8
	atualiza_indice(boneco9,9, tela); // CHECKED IN: 9
	atualiza_indice(boneco10,10, tela); // CHECKED IN: 10
	atualiza_indice(boneco11,11, tela); // SPECTORS: 11
	atualiza_indice(boneco12,12, tela); // SPECTORS: 12
	atualiza_indice(boneco13,13, tela); // SPECTORS: 13
	atualiza_indice(boneco14,14, tela); // SPECTORS: 14
	atualiza_indice(boneco15,15, tela); // SPECTORS: 15
	atualiza_indice(boneco16,16, tela); // SWEAR/GET CERTIFICATE: 16
	//imprime indice   
	imprime(tela);
		
	//insere mensagem de confirmação
	confirmed(mensagem, tela);
        //imprime mensagem de confirmação                                         	
	imprime(tela);
			
        //insere imagem1
        insere_texto(0, 0, 35, 100, imagem1, tela);
        //insere fim
        insere_texto(12, 35, 7, 25, fim, tela);
	//imprime fim
	imprime(tela);
	
	// libera a memória da matri  tela
	for (int i=0; i <35; i++)
  		free (tela[i]) ;
	free (tela) ;
	
	return 0;
}
