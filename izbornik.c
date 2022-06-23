#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"
#include "functions.h"

int izbornik(const char* const datoteka) {
	printf("\n\n			\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
	printf("	IZBORNIK TRGOVINE PARFEMA	");
	printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3\n\n");
	printf("\t\t\t	\xB3Opcija 1: Dodavanje novih parfema\n");
	printf("\t\t\t	\xB3Opcija 2: Ispis parfema\n");
	printf("\t\t\t	\xB3Opcija 3: Pretrazivanje parfema\n");
	printf("\t\t\t	\xB3Opcija 4: Uklanjanje parfema iz baze\n");
	printf("\t\t\t	\xB3Opcija 5: Promijeni podatke parfemu\n");
	printf("\t\t\t	\xB3Opcija 6: Admin\n");
	printf("\t\t\t	\xB3Opcija 7: Sortiranje parfema\n");
	printf("\t\t\t	\xB3Opcija 8: Izlazak iz programa\n");

	int choice = 0;
	int sortiranje = 0;
	int confirmationExit = 0;

	static PARFEM* poljeParfema = NULL;
	static PARFEM* pronadeniParfem = NULL;

	scanf("%d", &choice);
	switch (choice) {
	case 1:
		dodajParfem(datoteka);
		break;
	case 2:
		if (poljeParfema != NULL) {
			free(poljeParfema);
			poljeParfema = NULL;
		}
		poljeParfema = (PARFEM*)ucitavanjeParfema(datoteka);
		if (poljeParfema == NULL) {
			exit(EXIT_FAILURE);
		}
		ispisParfema(poljeParfema);
		break;
	case 3:
		pronadeniParfem = (PARFEM*)pretrazivanjeParfema(poljeParfema);
		break;
	case 4:
		brisanjeParfema(&pronadeniParfem, poljeParfema, datoteka);
		break;
	case 5:
		promijenaBaze(poljeParfema, datoteka);
		break;
	case 6:
		admin();
		break;
	case 7:
		printf("Izbornik sortiranja.\n");
		printf("\t\xB3Opcija 1: Sortiranje uzlazno\n");
		printf("\t\xB3Opcija 2: Sortiranje silazno\n");

		scanf("%d", &sortiranje);
		switch (sortiranje) {
		case 1:
			sortiranjeUzlazno(poljeParfema, datoteka);
			break;
		case 2:
			sortiranjeSilazno(poljeParfema, datoteka);
			break;
		}
		break;
	case 8:
		printf("	\xB3Program ce se ugasiti!\n		\xB3 0 za gasenje programa\n		\xB3 1 za nastavak\n");
		scanf("%d", &confirmationExit);
		choice = confirmExit(confirmationExit);
		break;
	default:
		printf("Upisali ste krivi broj za naredbu\nMolimo ponovo upisite broj");
	}

	return choice;
}
