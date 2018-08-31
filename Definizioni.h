#ifndef definizioni
#define definizioni
#include <stdio.h>
#include <math.h>
#include <time.h>

/* Questo file .h incude tutte le funzioni che vengono utilizzate nel programma */

/* tipo cella continene il valore della cella, se c'è una bandiera e se è attiva */
struct cella {
	int valore; /* -1 bomba, 0 vuota, 1 e così via */
	int bandiera;
	int attiva;
};
typedef struct cella t_cella;

/* tipo mossa contiene le coordinate di una mossa e il puntatore alla mossa successiva (lista) */
struct mossa {
	int riga;
	int colonna;
	struct mossa *next;
};
typedef struct mossa *t_mossa;

/* funzione che genera un nuovo schema */
t_cella **genera(int n_righe, int n_colonne, int n_mine);

/* funzione che carica uno schema da file */
t_cella **carica(FILE *schema, int *righe, int *colonne, int *mine);

/* funzione che incrementa il valore delle celle intorno alle bombe */
void incrementaval(int riga, int colonna, int n_righe, int n_colonne, t_cella **campo);

/* funzione che attiva le celle di valore 0 adiacenti a quella selezionata */
void selezionaadiacenti(int riga, int colonna, int n_righe, int n_colonne, int *contaattive, t_cella **campo);

/* sorella di selezionaadiacenti, disattiva le celle adiacenti a quelle con valore 0 */
void eliminaadiacenti(t_mossa lista, int riga, int colonna, int n_righe, int n_colonne, int *contaattive, t_cella **campo);

/* funzione che elimina l'ultima mossa fatta (prende le coordinate e le passa al main) */
int elimina(t_mossa *lista, int *riga, int *colonna);

/* funzione che aggiunge in testa alla lista delle mosse precedenti */
int prepend(t_mossa *lista, int riga, int colonna);

/* funzione che cerca se due coordinate sono già presenti nella lista */
int presenti(t_mossa lista, int riga, int colonna, int *contaattive);

/* funzione che stampa il campodi gioco */
void stampa(int n_colonne, int n_righe, t_cella **campo);

/* funziona che si occupa di liberare la memoria del campo e della lista delle mosse */
void liberamemoria(t_cella **campo, t_mossa lista, int n_righe);

#endif