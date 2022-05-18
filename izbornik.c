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
	printf("\t\t\t	\xB3Opcija 2: Ucitavanje parfema\n");
	printf("\t\t\t	\xB3Opcija 3: Ispis parfema\n");
	printf("\t\t\t	\xB3Opcija 6: Izlazak iz programa\n");

	int choice = 0;
	int confirmationExit = 0;

	static PARFEM* poljeParfema = NULL;

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
		ispisParfema(poljeParfema);
		break;
	case 6:
		printf("	\xB3Program ce se ugasiti!\n	\xB3Upisite nula ako zelite ugasiti program ili bilo koji broj kako bi nastavili\n");
		scanf("%d", &confirmationExit);
		choice = confirmExit(confirmationExit);
		break;
	default:
		choice = 0;
	}
	return choice;
}