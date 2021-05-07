#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
	 
//função espera e limpa tela
void wait_clear(){
	//Espera e Limpa
	sleep(2);  //system("sleep 1");
	system("clear");  // should simply write the path to current shell
	printf("\a");
	}

//função imprime tela
void imprime(int linha, int coluna, char** image, char** tela){
	for (int i=0;i<linha;i++) {
		for (int j=0;j<coluna;j++) {
			tela[i][j]=image[i][j];
			printf("%c",tela[i][j]);
		}
		printf("\n");
	}

}

//função insere boneco na tela
void insere_boneco(int L, int C, char** boneco, char** tela){
	// L linha origem
	// C coluna origem
	for (int i=0;i<7;i++) {
		for (int j=0;j<11;j++) {
			tela[L+i][C+j]=boneco[i][j];
		}
	}
}

//função que atualiza indice dos bonecos
void atualiza_indice(int L, int C, char indice, char** tela){
	int X = 0; //posiçoes fixa da linha do "?" no boneco
	int Y = 10; //posiçoes fixa da linha do "?" no boneco
	tela[L+X][C+Y] = indice;
}

int main(void){
	system("clear"); 
	
	//le
	/*
	FILE* arquivo_tela; 
        if ((arquivo_tela=fopen("tela.txt","r"))!=NULL) {
		for (int i=0;i<40;i++) {
			for (int j=0;j<100;j++) {
                		fscanf(arquivo_tela,"%c",&tela[i][j]);
                	}
		}
        }
	fclose(arquivo_tela);
	*/
	
	//Aloca tela[40][100]
	char** tela;
	tela = malloc(40*sizeof(char*));
	for (int i=0;i<40;i++) {
		tela[i] = malloc(100*sizeof(char));
	}
	
	//titulo
	char titulo[7][73]= {                                                                                           
	"  #####                                    #####                         ", 
	" #     #  #####   ######  ######  #    #  #     #    ##    #####   ##### ",
	" #        #    #  #       #       ##   #  #         #  #   #    #  #    #", 
	" #  ####  #    #  #####   #####   # #  #  #        #    #  #    #  #    #", 
	" #     #  #####   #       #       #  # #  #        ######  #####   #    #", 
	" #     #  #   #   #       #       #   ##  #     #  #    #  #   #   #    #", 
	"  #####   #    #  ######  ######  #    #   #####   #    #  #    #  ##### "
	};
	
	//fim
	char fim[7][25] = {
	 "#######  #     #  ###### ", 
	 "#        ##    #  #     #",
	 "#        # #   #  #     #",
	 "#####    #  #  #  #     #", 
	 "#        #   # #  #     #", 
	 "#        #    ##  #     #", 
	 "#######  #     #  ###### "
	 };
        
        //imagem1
	char imagem1[40][100] = {
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
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|                                                                                                  |",
	"|__________________________________________________________________________________________________|",	
	};             
             
        char imagem2[40][100] = {
        "__________________________________________COURT OF JUSTICE_________________________________________",
	"|  SWEAR/GET CERTIFICATE:                                                                          |",
	"|                                              Judge                                               |",
	"|      Immigrant ?                            @@@_@@@                                              |",
	"|         (^^)                               @@@/ \\@@@                                             |",
	"|        / || \\                              @@\\O O/@@                                             |",
	"|       c  xx  c                             @@@\\-/@@@                                             |",
	"|          ||                                @@@/ \\@@@                                             |",
	"|          ||                                  /\\|/\\                                               |",
	"|          LL                                                                                      |",
	"|                                       SPECTORS:                                                  |",
	"|                                                                                                  |",
	"|                                       Spectator ? Spectator ? Spectator ? Spectator ? Spectator ?|",
	"|                                          (00)        (00)        (00)        (00)        (00)    |",
	"|                                         / || \\      / || \\      / || \\      / || \\      / || \\   |",
	"|                                        c  xx  c    c  xx  c    c  xx  c    c  xx  c    c  xx  c  |",
	"|                                           ||          ||          ||          ||          ||     |",
	"|                                           ||          ||          ||          ||          ||     |",
	"|                                           LL          LL          LL          LL          LL     |",
	"|                                                                                                  |",
	"|   CHECKED IN:                                                                                    |",
	"|                                                                                                  |",
	"|Immigrant ? Immigrant ? Immigrant ? Immigrant ? Immigrant ?                                       |",
	"|   (^^)        (^^)        (^^)        (^^)        (^^)                                           |",
	"|  / || \\      / || \\      / || \\      / || \\      / || \\                                          |",
	"| c  xx  c    c  xx  c    c  xx  c    c  xx  c    c  xx  c                                         |",
	"|    ||          ||          ||          ||          ||                                            |",
	"|    ||          ||          ||          ||          ||                                            |",
	"|    LL          LL          LL          LL          LL                                            |",
	"|                                                                                                  |",
	"|   ENTRY:                                                                                         |",
	"|                                                                                                  |",
	"|Immigrant ? Immigrant ? Immigrant ? Immigrant ? Immigrant ?                                       |",
	"|   (^^)        (^^)        (^^)        (^^)        (^^)                                           |",
	"|  / || \\      / || \\      / || \\      / || \\      / || \\                                          |",
	"| c  xx  c    c  xx  c    c  xx  c    c  xx  c    c  xx  c                                         |",
	"|    ||          ||          ||          ||          ||                                            |",
	"|    ||          ||          ||          ||          ||                                            |",
	"|    LL          LL          LL          LL          LL                                            |",
	"|__________________________________________________________________________________________________|",
	};             
        
	char immigrant[7][11] = { 
	"Immigrant ?",
	"   (^^)    ",
	"  / || \\   ",
	" c  xx  c  ",
	"    ||     ",
	"    ||     ", 
	"    LL     ",
	};
	
	char spectator[7][11] = {  
	"Spectator ?",
        "   (00)    ",
        "  / || \\   ",
        " c  xx  c  ",
        "    ||     ",
        "    ||     ",
        "    LL     ",
        };
        
        char judge[7][11] = {  
        "   Judge   ",
        "  @@@_@@@  ",
        " @@@/ \\@@@ ",
        " @@\\O O/@@ ",
        " @@@\\-/@@@ ",
        " @@@/ \\@@@ ",
        "   /\\|/\\   ",
        }; 
            
	//imprime titulo
	for (int i=0;i<7;i++) {
		for (int j=0;j<73;j++) {
			printf("%c",titulo[i][j]);
		}
		printf("\n");
	}
	
        wait_clear();
                                                        	
	//Imprime imagem1
	for (int i=0;i<40;i++) {
		for (int j=0;j<100;j++) {
			//printf("x");
			tela[i][j]=imagem1[i][j];
			printf("%c",tela[i][j]);
		}
		printf("\n");
	}

	wait_clear();

	//Imprime immigrant        
        for (int i=0;i<7;i++) {
		for (int j=0;j<11;j++) {
			printf("%c",immigrant[i][j]);
		}
		printf("\n");
	}
	
	wait_clear();
	
	//Imprime spectator  
        for (int i=0;i<7;i++) {
		for (int j=0;j<11;j++) {
			printf("%c",spectator[i][j]);
		}
		printf("\n");
	}
	
	wait_clear();
	
	//Imprime judge  	
        for (int i=0;i<7;i++) {
		for (int j=0;j<11;j++) {
			printf("%c",judge[i][j]);
		}
		printf("\n");
	}
	
        wait_clear();

	//Imprime imagem2
	for (int i=0;i<40;i++) {
		for (int j=0;j<100;j++) {
			tela[i][j]=imagem2[i][j];
			printf("%c",tela[i][j]);
		}
		printf("\n");
	}
	
	wait_clear();
	
	int L; // linha origem
	int C; // colina origem
	
	/*
	//insere immigrant na tela
	L = 5; // linha origem
	C = 85; // colina origem
	for (int i=0;i<7;i++) {
		for (int j=0;j<11;j++) {
			tela[L+i][C+j]=immigrant[i][j];
		}
	}
	
	//insere spectator na tela 
	L = 22; // linha origem
	C = 10; // colina origem
	for (int i=0;i<7;i++) {
		for (int j=0;j<11;j++) {
			tela[L+i][C+j]=spectator[i][j];
		}
	}
		
	//insere judge na tela  
	L = 2; // linha origem
	C = 45; // colina origem
	for (int i=0;i<7;i++) {
		for (int j=0;j<11;j++) {
			tela[L+i][C+j]=judge[i][j];
		}
	}
	*/
	
	int X = 0; //posiçoes fixa da linha do "?" no boneco
	int Y = 10; //posiçoes fixa da coluna do "?" no boneco
	
	//atualiza indice
	L = 32;
	C = 1;
	tela[L+X][C+Y] = '1';
	L = 32;
	C = 13;
	tela[L+X][C+Y]= '2';
	
	
	//Imprime imagem modificada
	for (int i=0;i<40;i++) {
		for (int j=0;j<100;j++) {
			printf("%c",tela[i][j]);
		}
		printf("\n");
	}
			
	wait_clear();
	
	//imprime fim
	for (int i=0;i<7;i++) {
		for (int j=0;j<25;j++) {
			printf("%c",fim[i][j]);
		}
		printf("\n");
	}
	
	wait_clear();
	
	// libera a memória da matri  tela
	for (int i=0; i < 40; i++)
  		free (tela[i]) ;
	free (tela) ;
	
	return 0;
}
