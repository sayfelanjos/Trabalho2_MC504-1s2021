void* rotina_imigrante (void* indice) {

	int ind = (int) indice;
	int cadeira;

	while (1) {
		sem_wait(&juiz_fora);
		sem_post(&juiz_fora);
		sem_wait(&vagas_imigrantes);
		//enter();
		sem_wait(&escolher_cadeira);
		for (int i=0;i<5;i++) {
			if (cadeiras[i]==1) {
				cadeiras[i] = 0;
				cadeira = i;
				sem_wait(&chekin[i]);
				sem_wait(&certificado[i]);
				break;
			}
		}
		sem_post(&escolher_cadeira);
		//checkin();
		sem_post(&checkin[cadeira]);
		sem_wait(&confirm);
		//swear();
		//getCertificate();
		sem_post(&certificado[cadeira]);
		sem_wait(&juiz_fora);
		sem_post(&juiz_fora);
		//leave();
		sem_post(&vagas_imigrantes);
	}
}

void* rotina_juiz (void* parametros) {

	while (1) {
		//enter();
		for (int i=0;i<5;i++) {
			sem_wait(&checkin[i]);
		}
		//confirm();
		for (int i=0;i<5;i++) {
			sem_post(&checkin[i]);
		}
		for (int i=0;i<5;i++) {
			sem_wait(&certificado[i]);
			sem_post(&certificado[i]);
		}
		//leave();
	}
}

void* rotina_espectador (void* indice) {

	int ind = (int) indice;
	while (1) {
		sem_wait(juiz_fora);
		sem_post(juiz_fora);
		//enter();
		//spectate();
		//leave();
	}
}
