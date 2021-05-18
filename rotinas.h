#define NUM_IMIGRANTES 10
#define NUM_ESPECTADORES 10
#define NUM_VAGAS_IMIGRANTES 5
#define NUM_VAGAS_ESPECTADORES 5
#define LINHAS 35
#define COLUNAS 100

typedef struct args_imigrante {
	int indice;
	int *num_imigrantes_check_in;
	int *juiz_dentro;
	char **imagem_imigrante;
	char ** vazio;
	char ** tela;
	int* posicao_imigrante_fila;
	int* posicao_imigrante_check_in;
	sem_t* sair_sala;
	sem_t* juiz_na_sala;
	sem_t* imigrantes;
	sem_t* inseri_imigrantes_fila;
	sem_t* inseri_imigrantes_check_in;
	sem_t* altera_tela;
	sem_t* check_in;
	sem_t* pega_certificado;
	sem_t* pegou_certificado;
} args_imigrante;

typedef struct args_espectador {
	int indice;
	int *juiz_dentro;
	char** imagem_espectador;
	char** vazio;
	char** tela;
	int* posicao_espectador_fila;
	sem_t *inseri_espectador;
	sem_t* juiz_na_sala;
	sem_t* espectadores_fila;
	sem_t* altera_tela;
} args_espectador;

typedef struct args_juiz {
	int* juiz_dentro;
	int* num_imigrantes_check_in;
	char ** imagem_juiz;
	char* mensagem_confirma;
	char* mensagem_apaga;
	char ** tela;
	char** vazio;
	sem_t* sair_sala;
	sem_t* juiz_na_sala;
	sem_t* altera_tela;
	sem_t* pega_certificado;
	sem_t* pegou_certificado;
} args_juiz;

void* rotina_imigrante (void* args);

void* rotina_juiz (void* args);

void* rotina_espectador (void* args);

void imprime(char** tela, sem_t *altera_tela);

//funcao que toma como parametro uma imagem (imigrante/espectador/vazio) e insere na tela na posicao especificada
void insere_texto(int L, int C, int linha, int coluna, char** texto, char** tela);
// L é linha de origem
// C é coluna de origem
// linha é tamanho das linhas
// coluna é tamanho das colunas

//funcao que imprime o imigrante na respectiva posicao na entrada na tela
void entra_imigrante(int pos_fila,int id,char** imigrante, char** tela, sem_t * altera_tela); 

//funcao que apaga a imagem do espectador da tela
void sai_espectador(int pos, char** vazio, char** tela, sem_t * altera_tela);

// funcao que imprime o espectador na respectiva posicao na tela
void entra_espectador(int pos, int id,char** espectador, char** tela, sem_t * altera_tela);

//funcao que apaga o imigrante na posicao de checkin especificada
void sai_imigrante_check_in(int pos_fila, int id, int pos_check_in, char** imigrante, char** vazio, char** tela, sem_t *altera_tela);

//funcao que apaga o imigrante na posicao da fila especificada
void sai_imigrante_fila(int pos_fila, char** vazio, char** tela, sem_t * altera_tela);

//funcao que imprime o imigrante na posicao de pegar o certificado
void pegar_certificado(int pos_checkin,int id,char**imigrante,char** vazio, char** tela, sem_t * altera_tela);

//funcao que apaga o imigrante na posicao de checkin especificada
void checkin_imigrante(int pos_fila, int pos_chek_in,int id,char** imigrante, char** vazio, char** tela, sem_t * altera_tela);

//funcao que apaga a imagem do juiz da tela
void sai_juiz(char** vazio, char** tela, sem_t * altera_tela);

//funcao que imprime "->confirmed" na tela
void juiz_confirma(char* mensagem, char* apaga, char** tela, sem_t * altera_tela);

// funcao que coloca a imagem do juiz na tela
void entra_juiz(char** judge,char** tela, sem_t * altera_tela);

// funcao que escolhe uma posicao para inserir o imigrante/ espectador
int verifica_posicao(int * fila);

//funcao que remove o imigrante/ espectador da posicao especificada
void remove_posicao(int pos, int * fila);
