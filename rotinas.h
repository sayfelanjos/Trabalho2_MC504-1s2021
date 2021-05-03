typedef struct  params_imigrante{

	int indice;
	sem_t* confirm;
	sem_t* juiz_fora;
	sem_t* vagas_imigrantes;
	sem_t* escolher_cadeira;
	sem_t* check_in[5];
	sem_t* certificado[5];
} params_imigrante;

typedef struct params_espectador{

	int indice;
	sem_t* juiz_fora;
	sem_t* vagas_espectadores;
} params_espectador;

typedef struct params_juiz{

	sem_t* confirm;
	sem_t* juiz_fora;
	sem_t* check_in[5];
	sem_t* certificado[5];
} params_juiz;

void* rotina_imigrante (void* indice);

void* rotina_juiz (void* parametros);

void* rotina_espectador (void* indice);
