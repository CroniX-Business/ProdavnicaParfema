#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"

static int brojParfema = 0;
static int adminPass = 0;

int confirmExit(int confirmationExit) {
	if (confirmationExit == 0) return 0;
}

void* admin() {
	system("cls");
	if (adminPass == 1) {
		printf("Vec ste prijavljeni");
		return NULL;
	}

	int i = 0, ch;
	const char adminIme[] = "Petar";
	const char adminLozinka[] = "Programiranje";
	char upisIme[20] = { '\0' };
	char upisLozinka[20] = { '\0' };

	printf("Upisite ime Admina: ");
	scanf("%s", upisIme);
	if (!strcmp(adminIme, upisIme)) {
		printf("Upisite lozinku Admina: ");

		while (i < 20) {
			ch = getch();
			if (ch == ' ' || ch == 27) {
				continue;
			}
			else if (ch == '\b') {
				if (i > 0) {
					printf("\b \b");
					--i;
				}
				else {
					continue;
				}
			}
			else if (ch == '\r' || ch == '\t') {
				break;
			}
			else if (ch == 0 || ch == 224) {
				ch = getch();
				continue;
			}
			else {
				upisLozinka[i++] = ch;
				printf("*");
			}
		}
		upisLozinka[i] = '\0';

		if (!strcmp(adminLozinka, upisLozinka)) {
			printf("\nDobar dan, Petar\nUspijesno ste se ulogirali");
			adminPass = 1;
		}
		else {
			printf("\nUpisali ste krivu lozinku");
		}
	}
	else {
		printf("Upisali ste krivo ime");
	}

	return NULL;
}

void* dodajParfem(const char* const datoteka) {
	if (adminPass == 0) {
		printf("Niste prijavljeni kao Admin");
		return NULL;
	}

	FILE* pF = fopen(datoteka, "rb+");

	if (pF == NULL) {
		perror("Dodavanje parfema u datoteku");
		exit(EXIT_FAILURE);
	}

	fread(&brojParfema, sizeof(int), 1, pF);
	printf("\xB3 Broj parfema: %d\n", brojParfema);

	PARFEM temp = { 0 };

	getchar();
	printf("Unesite ime parfema: ");
	scanf("%19[^\n]", temp.ime);

	getchar();
	printf("Unesite kategorije parfema muski/zenski: ");
	scanf("%19[^\n]", temp.kategorija);

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

	return NULL;
}

void* ucitavanjeParfema(const char* const datoteka) {
	FILE* fp = fopen(datoteka, "rb");

	if (fp == NULL) {
		perror("Ucitavanje korisnika iz datoteke");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojParfema, sizeof(int), 1, fp);
	//printf("\xB3 Broj parfema: %d\n", brojParfema);

	PARFEM* poljeParfema = (PARFEM*)calloc(brojParfema, sizeof(PARFEM));
	if (poljeParfema == NULL) {
		perror("Zauzimanje memorije za parfeme");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeParfema, sizeof(PARFEM), brojParfema, fp);

	return poljeParfema;
}

void* ispisParfema(const PARFEM* const poljeParfema) {
	if (poljeParfema == NULL || brojParfema == 0) {
		printf("Baza parfema je prazna!\n");
		return NULL;
	}

	int i;
	for (i = 0; i < brojParfema; i++)
	{
		printf("\n	Parfem: %s\t\n	Kategorija: %s\t\n	Cijena: %dkn\t\n	Mililitara: %d Ml\t\n	Kolicina: %d kom\n",
			(poljeParfema + i)->ime,
			(poljeParfema + i)->kategorija,
			(poljeParfema + i)->cijena,
			(poljeParfema + i)->mililitri,
			(poljeParfema + i)->kolicina);
	}

	return NULL;
}

void* ispisPronadenogParfema(const PARFEM* const poljeParfema, int i) {
	if (poljeParfema == NULL) {
		printf("Baza parfema je prazna!\n");
		return NULL;
	}

	printf("\n	Parfem: %s\t\n	Kategorija: %s\t\n	Cijena: %d\t\n	Mililitara: %d\t\n	Kolicina: %d\n",
		(poljeParfema + i)->ime,
		(poljeParfema + i)->kategorija,
		(poljeParfema + i)->cijena,
		(poljeParfema + i)->mililitri,
		(poljeParfema + i)->kolicina);

	return NULL;
}

void* pretrazivanjeParfema(PARFEM* const poljeParfema) {
	system("cls");
	if (poljeParfema == NULL || brojParfema == 0) {
		printf("Baza parfema je prazna!\n");
		return NULL;
	}

	int i, b, br = 0, brP[10];
	int trazeniKriterij = 0;
	int cijena;
	char trazenoIme[20] = { '\0' };

	printf("Unesite broj za trazeni kriterij za pronalazak parfema.\n");
	printf("\t\xB3Opcija 1: Ime\n");
	printf("\t\xB3Opcija 2: Cijena\n");
	printf("\t\xB3Opcija 3: Kategorija\n");
	printf("\t\xB3Opcija 4: Izlazak iz pretrazivanja\n");

	printf("\xB3Kriterij: ");
	scanf("%d", &trazeniKriterij);
	switch (trazeniKriterij) {
	case 1:
		printf("	\xB3Unesite Ime parfema: ");
		getchar();
		scanf("%19[^\n]", trazenoIme);
		for (i = 0; i < brojParfema; i++)
		{
			if (!strcmp(trazenoIme, (poljeParfema + i)->ime)) {
				br++;
				brP[br] = i;
				ispisPronadenogParfema(poljeParfema, i);
			}
		}
		if (br == 0) printf("Trazeni parfem ne postoji");

		if (br > 1) {
			printf("\n\xB3Unesite redni broj parfema za buduce brisanje: ");
			scanf("%d", &b);
			return (poljeParfema + brP[b]);
		}
		else {
			return (poljeParfema + i);
		}
		break;
	case 2:
		printf("	\xB3Unesite cijenu parfema: ");
		scanf("%d", &cijena);
		for (i = 0; i < brojParfema; i++)
		{
			if (cijena == (poljeParfema + i)->cijena) {
				br++;
				brP[br] = i;
				ispisPronadenogParfema(poljeParfema, i);
			}
		}

		if (br == 0) {
			printf("Trazeni parfem ne postoji");
			return NULL;
		}

		if (br > 1) {
			printf("\n\xB3Unesite redni broj parfema za buduce brisanje: ");
			scanf("%d", &b);
			return (poljeParfema + brP[b]);
		}
		else {
			return (poljeParfema + i);
		}
		break;
	case 3:
		printf("	\xB3Unesite kategoriju parfema muski ili zenski: ");
		getchar();
		scanf("%19[^\n]", trazenoIme);
		for (i = 0; i < brojParfema; i++)
		{
			if (!strcmp(trazenoIme, (poljeParfema + i)->kategorija)) {
				br++;
				brP[br] = i;
				ispisPronadenogParfema(poljeParfema, i);
			}
		}
		if (br == 0) printf("Trazeni parfem ne postoji");

		if (br > 1) {
			printf("\n\xB3Unesite redni broj parfema za buduce brisanje: ");
			scanf("%d", &b);
			return (poljeParfema + brP[b]);
		}
		else {
			return (poljeParfema + i);
		}
		break;
	case 4:
		return NULL;
		break;
	}

	return NULL;
}

void* brisanjeParfema(PARFEM** const trazeniParfem, const PARFEM* const poljeParfema, const char* const datoteka) {
	system("cls");

	if (adminPass == 0) {
		printf("Niste prijavljeni kao Admin");
		return NULL;
	}

	if (*trazeniParfem == NULL) {
		printf("Niste pretrazili parfem koji treba obrisati!\n");
		return NULL;
	}

	printf("Potvrdite brisanje pronadenog parfema");
	printf("\nUtipkajte \"da\" za brisanje parfema suprotno utipkajte\
\"ne\"!\n");

	char potvrda[3] = { '\0' };
	scanf("%2s", potvrda);
	if (strcmp("da", potvrda)) {
		printf("Vraceni ste na glavni izbornik, parfem nije izbrisan");
		return NULL;
	}

	FILE* pF = fopen(datoteka, "wb");
	if (pF == NULL) {
		perror("Brisanje parfema iz datoteke");
		exit(EXIT_FAILURE);
	}

	fseek(pF, sizeof(int), SEEK_SET);
	int noviBrojacParfema = 0;

	int i;
	for (i = 0; i < brojParfema; i++)
	{
		if (*trazeniParfem != (poljeParfema + i)) {
			fwrite((poljeParfema + i), sizeof(PARFEM), 1, pF);
			noviBrojacParfema++;
		}
	}

	rewind(pF);
	fwrite(&noviBrojacParfema, sizeof(int), 1, pF);
	fclose(pF);

	printf("Parfem je uspjesno obrisan!\n");
	*trazeniParfem = NULL;

	return NULL;
}

void* promijenaBaze(PARFEM* const poljeParfema, const char* const datoteka) {
	if (adminPass == 0) {
		printf("Niste prijavljeni kao Admin");
		return NULL;
	}

	if (poljeParfema == NULL || brojParfema == 0) {
		printf("Baza parfema je prazno!\n");
		return NULL;
	}

	char trazenoIme[20] = { '\0' };
	int trazeniKriterij;

	char ime[20] = { '\0' };
	char kategorija[20] = { '\0' };
	int cijena, mililitri, kolicina;

	printf("	\xB3Unesite Ime parfema: ");
	getchar();
	scanf("%19[^\n]", trazenoIme);

	int i;
	for (i = 0; i < brojParfema; i++)
	{
		if (!strcmp(trazenoIme, (poljeParfema + i)->ime)) {
			printf("\nUnesite broj za trazeni kriterij za promijenu parfema.\n");
			printf("\t\xB3Opcija 1: Ime\n");
			printf("\t\xB3Opcija 2: Kategorija\n");
			printf("\t\xB3Opcija 3: Cijena\n");
			printf("\t\xB3Opcija 4: Mililitri\n");
			printf("\t\xB3Opcija 5: Kolicina\n");
			printf("\t\xB3Opcija 6: Sve\n");
			printf("\t\xB3Opcija 7: Izlazak\n");


			printf("\n\xB3Kriterij: ");
			scanf("%d", &trazeniKriterij);
			switch (trazeniKriterij) {
			case 1:
				printf("	\xB3Unesite Ime parfema: ");
				getchar();
				scanf("%19[^\n]", trazenoIme);

				strcpy((poljeParfema + i)->ime, trazenoIme);

				break;
			case 2:
				printf("	\xB3Unesite Kategoriju parfema: ");
				getchar();
				scanf("%19[^\n]", kategorija);

				strcpy((poljeParfema + i)->kategorija, kategorija);

				break;
			case 3:
				printf("	\xB3Unesite cijenu parfema: ");
				scanf("%d", &cijena);

				(poljeParfema + i)->cijena = cijena;

				break;
			case 4:
				printf("	\xB3Unesite mililitre parfema: ");
				scanf("%d", &mililitri);

				(poljeParfema + i)->mililitri = mililitri;

				break;
			case 5:
				printf("	\xB3Unesite kolicinu parfema: ");
				scanf("%d", &kolicina);

				(poljeParfema + i)->kolicina = kolicina;

				break;
			case 6:
				printf("	\xB3Unesite Ime parfema: ");
				getchar();
				scanf("%19[^\n]", trazenoIme);

				printf("	\xB3Unesite cijenu parfema: ");
				scanf("%d", &cijena);

				printf("	\xB3Unesite mililitre parfema: ");
				scanf("%d", &mililitri);

				printf("	\xB3Unesite kolicinu parfema: ");
				scanf("%d", &kolicina);

				strcpy((poljeParfema + i)->ime, trazenoIme);
				(poljeParfema + i)->cijena = cijena;
				(poljeParfema + i)->mililitri = mililitri;
				(poljeParfema + i)->kolicina = kolicina;

				break;
			case 7:
				return NULL;
				break;
			}

			FILE* pF = fopen(datoteka, "rb+");
			if (pF == NULL) {
				perror("Promijena opisa u datoteki");
				exit(EXIT_FAILURE);
			}
			rewind(pF);
			fseek(pF, 4, SEEK_CUR);
			fseek(pF, sizeof(PARFEM) * i, SEEK_CUR);
			fwrite((poljeParfema + i), sizeof(PARFEM), 1, pF);
			fclose(pF);
		}
	}
	return NULL;
}

void zamjena(PARFEM* veci, PARFEM* manji) {
	PARFEM temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void* sortiranjeUzlazno(PARFEM* poljeParfema, const char* const datoteka) {
	int min = -1, kriterij = 0;
	int i, j;

	FILE* pF = fopen(datoteka, "rb");
	if (pF == NULL) {
		printf("Greska pri otvaranju datoteke\n");
		exit(EXIT_FAILURE);
	}
	if (poljeParfema == NULL) {
		printf("Polje proizvoda je prazno.\n");
		return NULL;
	}
	fread(&brojParfema, sizeof(int), 1, pF);

	printf("Izbornik sortiranja ulazno.\n");
	printf("\t\xB3Opcija 1: Sortiranje po cijeni\n");
	printf("\t\xB3Opcija 2: Sortiranje po mililitrima\n");

	scanf("%d", &kriterij);
	switch (kriterij) {
	case 1:
		for (i = 0; i < brojParfema; i++)
		{
			min = i;
			for (j = i + 1; j < brojParfema; j++)
			{
				if ((poljeParfema + j)->cijena > (poljeParfema + min)->cijena) {
					min = j;
				}
			}
			zamjena((poljeParfema + i), (poljeParfema + min));
			ispisPronadenogParfema(poljeParfema, i);
		}
		break;
	case 2:
		for (i = 0; i < brojParfema; i++)
		{
			min = i;
			for (j = i + 1; j < brojParfema; j++)
			{
				if ((poljeParfema + j)->mililitri > (poljeParfema + min)->mililitri) {
					min = j;
				}
			}
			zamjena((poljeParfema + i), (poljeParfema + min));
			ispisPronadenogParfema(poljeParfema, i);
		}
		break;
	}

	printf("\n");
	fclose(pF);
}

void* sortiranjeSilazno(PARFEM* poljeParfema, const char* const datoteka) {
	int max = -1, kriterij = 0;
	int i, j;

	FILE* pF = fopen(datoteka, "rb");
	if (pF == NULL) {
		printf("Greska pri otvaranju datoteke\n");
		exit(EXIT_FAILURE);
	}
	if (poljeParfema == NULL) {
		printf("Polje proizvoda je prazno.\n");
		return NULL;
	}
	fread(&brojParfema, sizeof(int), 1, pF);

	printf("Izbornik sortiranja silazno.\n");
	printf("\t\xB3Opcija 1: Sortiranje po cijeni\n");
	printf("\t\xB3Opcija 2: Sortiranje po mililitrima\n");

	scanf("%d", &kriterij);
	switch (kriterij) {
	case 1:
		for (i = 0; i < brojParfema; i++)
		{
			max = i;
			for (j = i + 1; j < brojParfema; j++)
			{
				if ((poljeParfema + j)->cijena < (poljeParfema + max)->cijena) {
					max = j;
				}
			}
			zamjena((poljeParfema + i), (poljeParfema + max));
			ispisPronadenogParfema(poljeParfema, i);
		}
		break;
	case 2:
		for (i = 0; i < brojParfema; i++)
		{
			max = i;
			for (j = i + 1; j < brojParfema; j++)
			{
				if ((poljeParfema + j)->mililitri < (poljeParfema + max)->mililitri) {
					max = j;
				}
			}
			zamjena((poljeParfema + i), (poljeParfema + max));
			ispisPronadenogParfema(poljeParfema, i);
		}
		break;
	}

	printf("\n");
	fclose(pF);
}
