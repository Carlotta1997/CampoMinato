#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Definizioni.h"


/* PER ESEGUIRE    -->  '  gcc -Wall -o CampoMinato CampoMinato.c Funzioni.c   '   */


int main() {
	/* dichiarazioni variabili */
	int n_mine=0, n_righe=0, n_colonne=0, x=0, y=0, n_vite=0, viteusate=0;
	int sceltaop=0, contaattive=0;
	int continua=1; /* per continuare la partita, continua=1 */
	int esci=0; /* per terminre il gioco, esci=1 */
	int menu=1; /* per caricare/generare una nuova parita, menu=1 */
	int attenzione=0; /* se viene cariato un file txt vuoto, attenzione=1 */
	int mina=0; /* se trovata una mina, mina=1 */
	int *righe, *colonne;
	int schema = 0;
	t_cella **campo = NULL;
	t_mossa listamosse = NULL;

	/* avvio del gioco */
	while (menu == 1 && esci == 0) {
		/* inizializzazioni variabili */
		sceltaop = 0;
		contaattive = 0;
		continua = 1;
		menu = 0;
		esci = 0;
		n_righe = 0;
		n_colonne = 0;
		n_mine = 0;
		viteusate = 0;
		listamosse = NULL;

		/* introduzione al gioco */	
		if (attenzione == 0) {
			/* stampa schermata principale */
			system("clear");
			printf("\033[31m"); /* testo rosso */
			printf("\n       ██████╗ █████╗ ███╗   ███╗██████╗  ██████╗\n");
			printf("      ██╔════╝██╔══██╗████╗ ████║██╔══██╗██╔═══██╗\n");
			printf("      ██║     ███████║██╔████╔██║██████╔╝██║   ██║\n");
			printf("      ██║     ██╔══██║██║╚██╔╝██║██╔═══╝ ██║   ██║\n");
			printf("      ╚██████╗██║  ██║██║ ╚═╝ ██║██║     ╚██████╔╝\n");
			printf("       ╚═════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝      ╚═════╝ \n");
			printf("              ███╗   ███╗██╗███╗   ██╗ █████╗ ████████╗ ██████╗\n");
			printf("              ████╗ ████║██║████╗  ██║██╔══██╗╚══██╔══╝██╔═══██╗\n");
			printf("              ██╔████╔██║██║██╔██╗ ██║███████║   ██║   ██║   ██║\n");		
			printf("              ██║╚██╔╝██║██║██║╚██╗██║██╔══██║   ██║   ██║   ██║\n");
			printf("              ██║ ╚═╝ ██║██║██║ ╚████║██║  ██║   ██║   ╚██████╔╝\n");
			printf("              ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ \n");
			printf("                                              By Carlotta & Fede\n\n\n");
			printf("\033[39m"); /* default */
			printf("   ┏╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┓\n");
			printf("   ╏    ");
			printf("\033[1;36m"); /* testo grassetto e ciano */
			printf("Vuoi generare un nuovo schema o caricarne uno vecchio?");
			printf("\033[0;39m"); /* default */
			printf("    ╏\n");
			printf("   ╏                                                              ╏\n");
			printf("   ╏      0 - generare                                            ╏\n");
			printf("   ╏      1 - caricare                                            ╏\n");
			printf("   ┗╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┛\n");
			do {
				printf("      ==>  La tua scelta: ");
				scanf("%d", &schema);
			} while (schema < 0 || schema > 1);
		} 
		righe = &n_righe;
		colonne = &n_colonne;

		/* generazione o carica di uno schema di gioco */
		if (schema == 0) {
			system("clear");
			if (attenzione == 1) {
				printf("Nessuno schema vecchio, generare un nuovo schema!\n");
				attenzione = 0;
			} else {
				printf("   ┏╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┓\n");
				printf("   ╏       ");
				printf("\033[1;36m"); /* testo grassetto e ciano */
				printf("Crea nuovo schema:");
				printf("\033[0;39m"); /* default */
				printf("        ╏\n");
				printf("   ┗╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┛\n");
			}
			do {
				printf("\n      ==>  Quante colonne vuoi? ");
				scanf("%d", &n_colonne);
				printf("      ==>  Quante righe vuoi? ");
				scanf("%d", &n_righe);
			} while ((n_colonne < 2 || n_righe < 1) && (n_colonne < 1 || n_righe < 2));
			do {
				printf("      ==>  Quante mine vuoi schivare? ");
				scanf("%d", &n_mine);
			} while (n_mine > (n_righe*n_colonne)-1);

			/* richiamo della funzione genera un nuovo campo */
			campo = genera(n_righe, n_colonne, n_mine);
			printf("\n   ┏╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┓\n");
			printf("   ╏    ");
			printf("\033[1;36m"); /* testo grassetto e ciano */
			printf("Quante vite vuoi avere?");
			printf("\033[0;39m"); /* default */
			printf("                                   ╏\n");
			printf("   ┗╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┛\n");
			printf("      ==>  La tua scelta: ");
			scanf("%d", &n_vite);
		} else {
			if (schema == 1) {
				/* caricare uno schema vecchio */
				FILE *fp;
				fp = fopen("Schema.txt", "r");
				if ((fp == NULL) || (feof(fp))) { 
					printf("Errore\n"); 
				} else {
					fscanf(fp, "%d, %d", &n_righe, &n_colonne);
				}
				if (fp == NULL || *righe == 0 || *colonne == 0) {
					menu = 1;
					attenzione = 1;
					printf("     !!!!  Nessuno schema vecchio, generare un nuovo schema  !!!!\n"); 
					schema = 0;
					continua = 0;
				} else {
					/* richiamo della funzione carica un nuovo campo */
					campo = carica(fp, righe, colonne, &n_mine);
					printf("\n   ┏╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┓\n");
					printf("   ╏    ");
					printf("\033[1;36m"); /* testo grassetto e ciano */
					printf("Quante vite vuoi avere?");
					printf("\033[0;39m"); /* default */
					printf("                                   ╏\n");
					printf("   ┗╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┛\n");
					printf("      ==>  La tua scelta: ");
					scanf("%d", &n_vite);
				}
			}
		}
		

		/* inizio gioco */
		system("clear");
		
		/* se uno schema è stato caricato correttamente viene stampato a video coperto */
		if (attenzione != 1) { stampa(n_colonne, n_righe, campo); }

		/* la partita prosegue finchè non viene trovata una mina o non vengono trovate tutte le caselle senza mina */
		while (continua == 1 && contaattive < ((n_righe*n_colonne)-n_mine)) {
			/* selezione del tipo di azione da eseguire */
			printf("   ┏╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┓\n");
			printf("   ╏    ");
			printf("\033[1;36m"); /* testo grassetto e ciano */
			printf("Operazioni disponibili:");
			printf("\033[0;39m"); /* default */
			printf("                                   ╏\n");
			printf("   ╏                                                              ╏\n");
			printf("   ╏      1 - Seleziona una cella                                 ╏\n");
			printf("   ╏      2 - Piazza/Rimuovi una bandiera                         ╏\n");
			printf("   ╏      3 - Torna al menù principale                            ╏\n");
			printf("   ╏      4 - Esci dal gioco                                      ╏\n");
			printf("   ┗╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┛\n");
			do {
				printf("\n      ==>  La tua scelta: ");
				scanf("%d", &sceltaop);
			} while (sceltaop < 1 || sceltaop > 5);

			if (sceltaop == 1) {
			/* continuare il gioco */
				system("clear");
				if (attenzione != 1) { stampa(n_colonne, n_righe, campo); }
				printf("   ┏╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┓\n");
				printf("   ╏    ");
				printf("\033[1;36m"); /* testo grassetto e ciano */
				printf("Inserisci le coordinate della cella da selezionare:");
				printf("\033[0;39m"); /* default */
				printf("       ╏\n");
				printf("   ┗╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┛\n");
				printf("\n      ==>  Riga: ");
				scanf("%d", &x);
				printf("      ==>  Colonna: ");
				scanf("%d", &y);
				while (x >= n_righe || y >= n_colonne || campo[x][y].bandiera == 1 || campo[x][y].attiva == 1) {
					if (x >= n_righe || y >= n_colonne) {
						printf("\033[1;31m"); /* testo grassetto e rosso */
						printf("     !!!!  Seleziona una cella valida  !!!!\n"); 
						printf("\033[0;39m"); /* default */
					} else {
					/* se viene selezionata una cella con una bandiera */
						if (campo[x][y].bandiera == 1) {
							printf("\033[1;31m"); /* testo grassetto e rosso */
							printf("     !!!!  Rimuovi la bandiera prima di procedere  !!!!\n");
							printf("\033[0;39m"); /* default */
						}
						if (campo[x][y].attiva == 1 && campo[x][y].bandiera == 0) {
							printf("\033[1;31m"); /* testo grassetto e rosso */
							printf("     !!!!  Hai già selezionato questa cella  !!!!\n"); 
							printf("\033[0;39m"); /* default */
						}
					}
					printf("      ==>  Riga: ");
					scanf("%d", &x);
					printf("      ==>  Colonna: ");
					scanf("%d", &y);
				}

				/* aggiunta in testa della lista della mossa */
				prepend(&listamosse, x, y);

				if (campo[x][y].valore != -1) {  /* non c'è la mina */
					continua = 1;
					if (campo[x][y].valore == 0) {
						/* se la cella ha valore 0 attivo anche le celle adiacenti */
						selezionaadiacenti(x, y, n_righe, n_colonne, &contaattive, campo);
					} else {
						campo[x][y].attiva = 1;
						contaattive += 1;
					}
				} else {  /* c'è la mina */
					campo[x][y].attiva = 1;
					contaattive += 1;
					continua = 0;
					mina = 1;
				}
			} else {
				if (sceltaop == 2) {
				/* piazzare/rimuovere una bandiera indicando le coordinate */
					system("clear");
					if (attenzione != 1) { stampa(n_colonne, n_righe, campo); }
					printf("   ┏╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┓\n");
					printf("   ╏    ");
					printf("\033[1;36m"); /* testo grassetto e ciano */
					printf("Inserisci le coordinate della cella in cui piazzare/rimuovere la bandiera:");
					printf("\033[0;39m"); /* default */
					printf("     ╏\n");
					printf("   ┗╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┛\n");
					printf("\n      ==>  Riga: ");
					scanf("%d", &x);
					printf("      ==>  Colonna: ");
					scanf("%d", &y);
					while (x >= n_righe || y >= n_colonne || (campo[x][y].attiva == 1 && campo[x][y].bandiera == 0)) {
						if (campo[x][y].attiva == 1 && campo[x][y].bandiera == 0) {
							printf("\033[1;31m"); /* testo grassetto e rosso */
							printf("     !!!!  Seleziona una cella non ancora selezionata  !!!!"); 
							printf("\033[0;39m"); /* default */
						} else {
							printf("\033[1;31m"); /* testo grassetto e rosso */
							printf("     !!!!  Seleziona una cella valida  !!!!"); 
							printf("\033[0;39m"); /* default */
						}
						printf("\n      ==>  Riga: ");
						scanf("%d", &x);
						printf("      ==>  Colonna: ");
						scanf("%d", &y);
					}
					if (campo[x][y].bandiera == 1) {
						campo[x][y].bandiera = 0; /* bandiera rimossa */
						campo[x][y].attiva = 0;
					} else {
						campo[x][y].bandiera = 1; /* bandiera piazzata */
						campo[x][y].attiva = 1;
					}
				} else {
					if (sceltaop == 3) {
					/* tornare al menu principale */
						continua = 0; /* per non entrare di nuovo nel while della partita */
						menu = 1; /* per rientrare nel while del gioco */
						liberamemoria(campo, listamosse, n_righe);
					} else {
						/* uscire dal gioco */
						if (sceltaop == 4) {
							continua = 0; /* per non entrare di nuovo nel while della partita */
							esci = 1; /* per uscire dal gioco */
							liberamemoria(campo, listamosse, n_righe);
						}
					}
				}
			}
			system("clear");
			if (esci != 1) { stampa(n_colonne, n_righe, campo); }

			if (contaattive >= ((n_righe*n_colonne)-n_mine) && continua == 1) {
				menu = 0;
			} else {
				menu = 1;
			}

			/* se hai beccato la mina */
			if (mina == 1 && continua == 0 && esci != 1 && menu == 1) {
				printf("\033[31m");
				printf("\n     ██▓███   █████  ██▀███    ██████  ▒█████  \n");
				printf("    ▓██░  ██▒▒█   ▀ ▒██ ▒ ██▒▒██    ▒ ▒██▒  ██▒\n");
				printf("    ▓██░ ██▓▒▒███   ▒██ ░▄█ ▒░ ▓██▄   ▒██░  ██▒\n");
				printf("    ▒██▄█▓▒ ▒▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒▒██   ██░\n");
				printf("    ▒██▒ ░  ░░█████░▒█▓ ▒██▒ ▒██████▒▒░ ████▓▒░\n");
				printf("    ▒█▒░ ░  ░░░ ▒░ ░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░░ ▒░▒░▒░\n");
				printf("    ░▒ ░      ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░  ░ ▒ ▒░\n");
				printf("    ░░          ░     ░░   ░ ░  ░  ░  ░ ░ ░ ▒\n");
				printf("                ░  ░   ░           ░      ░ ░\n");
				printf("\033[39m");
				printf("\033[1;31m"); /* testo grassetto e rosso */
				printf("\n     HAI BECCATO LA MINA!!!\n\n");
				printf("\033[0;39m"); /* default */
				printf("   ┏╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┓\n");
				printf("   ╏    ");
				printf("\033[1;36m"); /* testo grassetto e ciano */
				printf("Cosa vuoi fare?");
				printf("\033[0;39m"); /* default */
				printf("                                                             ╏\n");
				printf("   ╏                                                                                ╏\n");
				if (n_vite > viteusate) {
					printf("   ╏      0 - Torna indietro di %d mosse (hai ancora %d vite a diposizione)           ╏\n", viteusate+1, n_vite-viteusate);
				}
				printf("   ╏      1 - Torna al menù principale                                              ╏\n");
				printf("   ╏      2 - Esci dal gioco                                                        ╏\n");
				printf("   ┗╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┛\n\n");
				do {
					printf("      ==>  La tua scelta: ");
					scanf("%d", &sceltaop);
				} while (sceltaop < 0 || sceltaop > 2);

				if (sceltaop == 0) {
					/* tronare indietro delle mosse */
					int i=0;
					int eliminariga = 0;
					int eliminacolonna = 0;
					int controllelimina = 0;
					viteusate += 1; /* uso una vita */
					if (n_vite >= viteusate) {
						for (i=0; i<viteusate; i++) {
							controllelimina = elimina(&listamosse, &eliminariga, &eliminacolonna); /* prelevo le coord. dell'ultima mossa */
							if (controllelimina) {
								
								if (campo[eliminariga][eliminacolonna].attiva == 1 && campo[eliminariga][eliminacolonna].valore == 0) {
									eliminaadiacenti(listamosse, eliminariga, eliminacolonna, n_righe, n_colonne, &contaattive, campo);
								} else {
									campo[eliminariga][eliminacolonna].attiva = 0;
									contaattive -= 1;
								}
							}
						}
					}
					continua = 1;
					mina = 0;
					system("clear");
					stampa(n_colonne, n_righe, campo);
				} else {
					if (sceltaop == 1) {
						/* tonrare al menu prncipale */
						continua = 0; /* per non entrare di nuovo nel while della partita */
						menu = 1; /* per rientrare nel while del gioco */
						liberamemoria(campo, listamosse, n_righe);
					} else {
						if (sceltaop == 2) {
						/* uscire dal gioco */
							continua = 0; /* per non entrare di nuovo nel while della partita */
							esci = 1; /* per uscire dal gioco */
							liberamemoria(campo, listamosse, n_righe);
						}
					}
				}
			}
		}

		/* se hai vinto */
		if ((n_righe*n_colonne)-n_mine == contaattive && attenzione == 0 && menu == 0) {
			system("clear");
			printf("\033[34m");
			printf("\n    ██    ██ ██ ███    ██ ████████  ██████     ██  ██  ██\n");
			printf("    ██    ██ ██ ████   ██    ██    ██    ██    ██  ██  ██\n");
			printf("    ██    ██ ██ ██ ██  ██    ██    ██    ██    ██  ██  ██\n");
			printf("     ██  ██  ██ ██  ██ ██    ██    ██    ██\n");
			printf("      ████   ██ ██   ████    ██     ██████     ██  ██  ██\n\n");
			printf("\033[39m");
			printf("   ┏╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┓\n");
			printf("   ╏    ");
			printf("\033[1;36m"); /* testo grassetto e ciano */
			printf("Vuoi tornare al menù principale oppure uscire dal gioco?");
			printf("\033[0;39m"); /* default */
			printf("      ╏\n");
			printf("   ╏                                                                  ╏\n");			
			printf("   ╏      0 - Torna al menù principale                                ╏\n");
			printf("   ╏      1 - Esci dal gioco                                          ╏\n");
			printf("   ┗╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍┛\n");
			liberamemoria(campo, listamosse, n_righe);
			do {
				printf("      ==>  La tua scelta: ");
				scanf("%d", &sceltaop);
			} while (sceltaop < 0 || sceltaop > 1);
			if (sceltaop == 0) {
				/* tornare al menu principale */
				continua = 0; /* per non entrare di nuovo nel while della partita */
				menu = 1; /* per rientrare nel while del gioco */
			} else {
				/* uscire dal gioco */
				if (sceltaop == 1) {
					continua = 0; /* per non entrare di nuovo nel while della partita */
					esci = 1; /* per uscire dal gioco */
				}
			}
			
		}
	}
	return 0;
}