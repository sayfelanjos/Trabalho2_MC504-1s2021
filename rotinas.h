#define NUM_IMIGRANTES 10
#define NUM_ESPECTADORES 10
#define NUM_VAGAS_IMIGRANTES 5
#define NUM_VAGAS_ESPECTADORES 5
#define LINHAS 35
#define COLUNAS 100

typedef struct args_imigrante {
	int indice;
	int *num_imigrantes_check_in;
	int *num_imigrantes_fila;
	int *juiz_dentro;
	char **imagem_imigrante;
	char ** vazio;
	char ** tela;
	sem_t* confirm;
	sem_t* juiz_na_sala;
	sem_t* imigrantes;
	sem_t* inseri_imigrantes_fila;
	sem_t* inseri_imigrantes_check_in;
	sem_t* assentar;
	sem_t* check_in;
	sem_t* certificado;
} args_imigrante;

typedef struct args_espectador {
	int indice;
	int *num_espectadores;
	int *juiz_dentro;
	char** imagem_espectador;
	char** vazio;
	char** tela;
	char * posicao_espectador_fila;
	sem_t *inseri_espectador;
	sem_t* juiz_na_sala;
	sem_t* espectadores_fila;
} args_espectador;

typedef struct args_juiz {
	int* juiz_dentro;
	int* num_imigrantes_check_in;
	char ** imagem_juiz;
	char** mensagem_confirma;
	char** mensagem_apaga;
	char ** tela;
	sem_t* confirm;
	sem_t* juiz_na_sala;
	sem_t* assentar;
	sem_t* certificado;
} args_juiz;

void* rotina_imigrante (void* indice);

void* rotina_juiz (void* parametros);

void* rotina_espectador (void* indice);

void imprime(char** tela);

void insere_texto(int L, int C, int linha, int coluna, char** texto, char** tela);

void entra_imigrante(int pos_fila,char** immigrante, char** tela);

void sai_espectador(int pos, char** vazio, char** tela);

void entra_espectador(int pos, int id,char** espectador, char** tela);

void sai_imigrante(int pos_checkin, char** vazio, char** tela);

void pegar_certificado(int pos_checkin,char**imigrante,char** vazio, char** tela);

void checkin_imigrante(int pos_fila, int pos_chekin,char** imigrante, char** vazio, char** tela);

void sai_juiz(char** vazio, char** tela);

void juiz_confirma(char* mensagem, char* apaga, char** tela);

void entra_juiz(char** judge,char** tela);

int verifica_posicao(int * fila);