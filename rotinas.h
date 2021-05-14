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
	sem_t* confirm;
	sem_t* juiz_na_sala;
	sem_t* imigrantes_fila;
	sem_t* inseri_imigrante_fila;
	sem_t* inseri_imigrante_check_in;
	sem_t* assentar;
	sem_t* check_in;
	sem_t* certificado;
} args_imigrante;

typedef struct args_espectador {
	int indice;
	int *num_espectadores;
	int *juiz_dentro;
	sem_t *inseri_espectador;
	sem_t* juiz_na_sala;
	sem_t* espectadores_fila;
} args_espectador;

typedef struct args_juiz {
	int* juiz_dentro;
	int* num_imigrantes_check_in;
	sem_t* confirm;
	sem_t* juiz_na_sala;
	sem_t* assentar;
	sem_t* certificado;
} args_juiz;

void* rotina_imigrante (void* indice);

void* rotina_juiz (void* parametros);

void* rotina_espectador (void* indice);