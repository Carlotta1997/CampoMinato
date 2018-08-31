#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Definizioni.h"

/* funzione che incrementa il valore delle celle intorno alle bombe */
void incrementaval(int riga, int colonna, int n_righe, int n_colonne, t_cella **campo) {
	/* controllo se la riga è nei limiti */
	if(riga>0){ 
		if(campo[riga-1][colonna].valore!=-1) { 
			campo[riga-1][colonna].valore+=1; 
		}
		if(colonna>0){
			if(campo[riga-1][colonna-1].valore!=-1) { campo[riga-1][colonna-1].valore+=1; }
		}
		if(colonna<n_colonne-1){
			if(campo[riga-1][colonna+1].valore!=-1) { campo[riga-1][colonna+1].valore+=1; }
		}
	}
	/* controllo sempre se la riga è nei limiti */
	if(riga<n_righe-1){
		if(campo[riga+1][colonna].valore!=-1) {
			campo[riga+1][colonna].valore+=1;
		}
		if(colonna<n_colonne-1){
			if(campo[riga+1][colonna+1].valore!=-1) { campo[riga+1][colonna+1].valore+=1; }
		}
		if(colonna>0){
			if(campo[riga+1][colonna-1].valore!=-1) { campo[riga+1][colonna-1].valore+=1; }
		}
	}
	/* controllo se la colonna è nei limiti */
	if(colonna<n_colonne-1){
		if(campo[riga][colonna+1].valore!=-1) { campo[riga][colonna+1].valore+=1; }
	}
	/* controllo sempre se la colonna è nei limiti */
	if(colonna>0){
		if(campo[riga][colonna-1].valore!=-1) { campo[riga][colonna-1].valore+=1; }
	}
}


/* funzione che genera un nuovo schema */
t_cella **genera(int n_righe, int n_colonne, int n_mine) {
	int i, j, riga, colonna;
	srand(time(NULL));

	FILE *fp;
	fp = fopen("Schema.txt", "w");
	if (fp == NULL) { printf("Errore"); }
	fprintf(fp, "%d, %d\n", n_righe, n_colonne);
	fprintf(fp, "\n");

	/* alloco in head la matrice campo */
	t_cella **campo;
	campo = (t_cella**)malloc(sizeof(t_cella*)*n_righe);
	for (i=0; i<n_righe; i++) {
		campo[i] = (t_cella*)malloc(sizeof(t_cella)*n_colonne);
	}

	/* inizializzo a zero le celle */
	for (i=0; i<n_righe; i++) {
		for (j=0; j<n_colonne; j++) {
			campo[i][j].valore = 0;
			campo[i][j].bandiera = 0;
			campo[i][j].attiva = 0;
		}
	}

	i=0; j=0;
	/* metto le mine nel campo a random */
	for (i=0; i<n_mine; i++) {
		riga = rand() % n_righe;
		colonna = rand() % n_colonne;
		if (campo[riga][colonna].valore != -1) { /* controllo che non sia già presente una mina */
			campo[riga][colonna].valore = -1;
			/* scrivo nel file */
			fprintf(fp, "%d, %d\n", riga, colonna);
			incrementaval(riga, colonna, n_righe, n_colonne, campo);
		} else {
			i = i-1; /* se è già una mina prendo un'altra cella */ 
		}
	}
	
	fclose(fp);
	return campo;
}


/* funzione che carica uno schema da file */
t_cella **carica(FILE *fp, int *righe, int *colonne, int *mine) {
	int n_righe, n_colonne; 
	int riga=0, colonna=0, i, j;

	/* recupera da file le dimensioni */
	n_righe = *righe;
	n_colonne = *colonne;
	fscanf(fp, "\n");
	
	/* alloco in head la matrice campo */
	t_cella **campo;
	campo = (t_cella**)malloc(sizeof(t_cella*)*(n_righe));
	for (i=0; i<(n_righe); i++) {
		campo[i] = (t_cella*)malloc(sizeof(t_cella)*(n_colonne));
	}

	/* inizializzo a zero le celle */
	for (i=0; i<(n_righe); i++) {
		for (j=0; j<(n_colonne); j++) {
			campo[i][j].valore = 0;
			campo[i][j].bandiera = 0;
			campo[i][j].attiva = 0;
		}
	}

	/* carico le mine dalle posizioni nel file */
	while (fscanf(fp, "%d, %d", &riga, &colonna) && !feof(fp)) {
		campo[riga][colonna].valore = -1;
		*mine += 1;
		incrementaval(riga, colonna, *righe, *colonne, campo);
	}

	fclose(fp);
	return campo;
}


/* funzione che attiva le celle di valore 0 adiacenti a quella selezionata */
void selezionaadiacenti(int riga, int colonna, int n_righe, int n_colonne, int *contaattive, t_cella **campo) {
	/* controllo se sono all'interno dei limiti */
	if (riga >= 0 && riga < n_righe && colonna >= 0 && colonna < n_colonne) {
		/* controllo che il campo non sia attivo, sia valore zero e non abbia bandiere */
		if (campo[riga][colonna].attiva == 0 && campo[riga][colonna].valore == 0 && campo[riga][colonna].bandiera == 0) {
			campo[riga][colonna].attiva = 1;
			(*contaattive) += 1;
			selezionaadiacenti(riga, colonna+1, n_righe, n_colonne, contaattive, campo);
			selezionaadiacenti(riga, colonna-1, n_righe, n_colonne, contaattive, campo);
			selezionaadiacenti(riga+1, colonna, n_righe, n_colonne, contaattive, campo);
			selezionaadiacenti(riga-1, colonna, n_righe, n_colonne, contaattive, campo);
			selezionaadiacenti(riga+1, colonna+1, n_righe, n_colonne, contaattive, campo);
			selezionaadiacenti(riga-1, colonna-1, n_righe, n_colonne, contaattive, campo);
			selezionaadiacenti(riga+1, colonna-1, n_righe, n_colonne, contaattive, campo);
			selezionaadiacenti(riga-1, colonna+1, n_righe, n_colonne, contaattive, campo);
		} else {
			/* se ho valore > 0 termino la ricorsione */
			if (campo[riga][colonna].attiva == 0 && campo[riga][colonna].valore > 0 && campo[riga][colonna].bandiera == 0) {
				campo[riga][colonna].attiva = 1;
				(*contaattive) += 1;
			}
		}
	}
}

/* funzione che stampa il campodi gioco */
void stampa(int n_colonne, int n_righe, t_cella **campo) {
	int i=0, j=0, k=0, n=0;

	/* stampa prima riga */
	printf("\n     ╔═══");
	for (n=0; n<n_colonne-1; n++) {
		printf("╦═══");
	}
	printf("╗\n");
	i=0;
	j=0;
	n=0;

	/* stampa corpo centrale */
	for (i=0; i<n_righe-1; i++) {
		/* stampa indice di riga */
		if (i>9) {
			printf("   %d║", i);
		} else {
			printf("   %d ║", i);
		}
		for (j=0; j<n_colonne; j++) {
			if (campo[i][j].attiva == 0) {
				/* stampa celle di colore verde NON attive */
				printf(" ");
				printf("\033[32m");
				printf("█");
				printf("\033[39m");
				printf(" ║");
			} else {
				if (campo[i][j].attiva == 1 && campo[i][j].bandiera == 1) {
					/* stampa celle con bandierina attive */
					printf(" ");
					printf("\033[1;33m");
					printf("⚐");
					printf("\033[0m");
					printf(" ║");
				} else {
					if (campo[i][j].attiva == 1 && campo[i][j].valore == 0) {
						/* stampa celle attive di valore 0 */
						printf("   ║");
					} else {
						if (campo[i][j].attiva == 1 && campo[i][j].valore == -1) {
							/* stampa cella con mina */
							printf(" ✷ ║");
						} else { 
							/* stampa celle attive con valore */
							printf(" %d ║", campo[i][j].valore);
						}
					}
				}
			}
		}
		/* stampa margini delle celle */
		printf("\n");
		printf("     ╠═══");
		for (k=1; k<n_colonne; k++) {
			printf("╬═══");
		}
		printf("╣\n");
	}
	/* stampa ultima riga (stesso codice del for precedente) */
	if (i>9) {
		printf("   %d║", i);
	} else {
		printf("   %d ║", i);
	}
	j=0;
	i=n_righe-1;
	k=0;
	for (j=0; j<n_colonne; j++) {
		if (campo[i][j].attiva == 0) {
			printf(" ");
			printf("\033[32m");
			printf("█");
			printf("\033[39m");
			printf(" ║");
		} else {
			if (campo[i][j].attiva == 1 && campo[i][j].bandiera == 1) {
				printf(" ");
				printf("\033[33m");
				printf("⚐");
				printf("\033[0m");
				printf(" ║");
			} else {
				if (campo[i][j].attiva == 1 && campo[i][j].valore == 0) {
					printf("   ║");
				} else {
					if (campo[i][j].attiva == 1 && campo[i][j].valore == -1) {
						printf(" ✷ ║");
					} else { 
						printf(" %d ║", campo[i][j].valore);
					}
				}
			}				
		}
	}
	/* stampa margine inferiore */
	printf("\n");
	printf("     ╚═══");
	for (k=1; k<n_colonne; k++) {
		printf("╩═══");
	}
	printf("╝\n");
	printf("       ");
	for (k=0; k<n_colonne; k++) {
		if (k>9) {
			printf("%d  ", k);
		} else {
			printf("%d   ", k);
		}
	}
	printf("\n");
}

/* funzione che aggiunge in testa alla lista delle mosse precedenti */
int prepend(t_mossa *lista, int riga, int colonna) {
	t_mossa new;
	new = (t_mossa)malloc(sizeof(struct mossa));
	if (new) {
		new -> next = *lista;
		new -> riga = riga;
		new -> colonna = colonna;
		*lista = new;
		return 1; /* aggiunta in testa con successo */
	} else {
		return 0; /* fallimento */
	}
}

/* funzione che elimina l'ultima mossa fatta (prende le coordinate e le passa al main) */
int elimina(t_mossa *lista, int *riga, int *colonna) {
		if (*lista == NULL) {
			return 0;
		} else {
			/* elimino dlla lista di mosse l'ultima mossa */
			t_mossa appoggio;
			appoggio = *lista;
			(*riga) = appoggio -> riga;
			(*colonna) = appoggio -> colonna;
			(*lista) = appoggio -> next;
			free(appoggio);
			return 1;
		}
}

/* sorella di selezionaadiacenti, disattiva le celle adiacenti a quelle con valore 0 */
void eliminaadiacenti(t_mossa lista, int riga, int colonna, int n_righe, int n_colonne, int *contaattive, t_cella **campo) {
	/* controllo se sono all'interno dei margini */
	if (riga >= 0 && riga < n_righe && colonna >= 0 && colonna < n_colonne) {
		/* il controllo presenti serve per non disattivare celle già disattivate */
		if (!presenti(lista, riga, colonna, contaattive) && campo[riga][colonna].attiva == 1 && campo[riga][colonna].valore == 0 && campo[riga][colonna].bandiera == 0) {
			campo[riga][colonna].attiva = 0;
			(*contaattive) -= 1;
			eliminaadiacenti(lista, riga, colonna+1, n_righe, n_colonne, contaattive, campo);
			eliminaadiacenti(lista, riga, colonna-1, n_righe, n_colonne, contaattive, campo);
			eliminaadiacenti(lista, riga+1, colonna, n_righe, n_colonne, contaattive, campo);
			eliminaadiacenti(lista, riga-1, colonna, n_righe, n_colonne, contaattive, campo);
			eliminaadiacenti(lista, riga+1, colonna+1, n_righe, n_colonne, contaattive, campo);
			eliminaadiacenti(lista, riga-1, colonna-1, n_righe, n_colonne, contaattive, campo);
			eliminaadiacenti(lista, riga+1, colonna-1, n_righe, n_colonne, contaattive, campo);
			eliminaadiacenti(lista, riga-1, colonna+1, n_righe, n_colonne, contaattive, campo);
		} else {
			/* terminola ricorsione se trovo un valore > 0 */
			if (!presenti(lista, riga, colonna, contaattive) && campo[riga][colonna].attiva == 1 && campo[riga][colonna].valore > 0 && campo[riga][colonna].bandiera == 0) {
				campo[riga][colonna].attiva = 0;
				(*contaattive) -= 1;
			}
		}
	}
}

/* funzione che cerca se due coordinate sono già presenti nella lista */
int presenti(t_mossa lista, int riga, int colonna, int *contaattive) {
	int trovato=0;
	while (!trovato && lista) {
		if (riga == lista -> riga && colonna == lista -> colonna) {
			trovato = 1;
			(*contaattive) += 1;
		}
		lista = lista -> next;
	}
	return trovato;
}

/* funziona che si occupa di liberare la memoria del campo e della lista delle mosse */
void liberamemoria(t_cella **campo, t_mossa lista, int n_righe) {
	int i=0;
	t_mossa pc = lista;

	/* dealloco il campo */
	for (i=0; i<n_righe; i++) {
		free(campo[i]);
	}
	free(campo);

	/* dealloco la lista */
	while (pc) {
		lista = pc -> next;
		free(pc);
		pc = lista;
	}
}





