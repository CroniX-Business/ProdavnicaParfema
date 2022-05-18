#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"

static int brojParfema = 0;

int confirmExit(int confirmationExit) {
	if (confirmationExit == 0) {
		return 0;
	}
}

void dodajParfem(const char* const datoteka) {
	FILE* pF = fopen(datoteka, "rb+");

	if (pF == NULL) {
		perror("Dodavanje parfema u datoteke %s", datoteka);
		exit(EXIT_FAILURE);
	}

	fread(&brojParfema, sizeof(int), 1, pF);
	printf("\xB3 Broj parfema: %d\n", brojParfema);

	PARFEM temp = { 0 };

	getchar();
	printf("Unesite ime parfema: ");
	scanf("%19[^\n]", temp.ime);

	printf("Unesite cijenu parfema: ");
	scanf("%d", &temp.cijena);

	printf("Unesite mililitre parfema: ");
	scanf("%d", &temp.mililitri);

	printf("Unesite kolicinu parfema: ");
	scanf("%d", &temp.kolicina);

	fseek(pF, sizeof(PARFEM) * brojParfema, SEEK_CUR);
	fwrite(&temp, sizeof(PARFEM), 1, pF);

	rewind(pF);
	brojParfema++;

	fwrite(&brojParfema, sizeof(int), 1, pF);
	fclose(pF);
	system("cls");
}

void* ucitavanjeParfema(const char* const datoteka) {

	FILE* fp = fopen(datoteka, "rb");

	if (fp == NULL) {
		perror("Ucitavanje korisnika iz datoteke %s", datoteka);
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojParfema, sizeof(int), 1, fp);
	printf("\xB3 Broj parfema: %d\n", brojParfema);

	PARFEM* poljeParfema = (PARFEM*)calloc(brojParfema, sizeof(PARFEM));
	if (poljeParfema == NULL) {
		perror("Zauzimanje memorije za parfeme");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeParfema, sizeof(PARFEM), brojParfema, fp);
	printf("\xB3 Svi clanovi uspjesno ucitani.\n\n");

	return poljeParfema;
}


void ispisParfema(const PARFEM* const poljeParfema) {
	if (poljeParfema == NULL) {
		printf("Polje filmova je prazno!\n");
		return;
	}

	int i;
	for (i = 0; i < brojParfema; i++)
	{
		printf("\nParfem: %s\t\nCijena: %d\t\nMililitara: %d\t\nKolicina: %d\n",
			(poljeParfema + i)->ime,
			(poljeParfema + i)->cijena,
			(poljeParfema + i)->mililitri,
			(poljeParfema + i)->kolicina);
	}
}