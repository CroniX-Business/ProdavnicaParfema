#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "datatype.h"

int main(void) {
	system("color B");

	int choice = 1;
	int confirmationExit = 1;
	char datoteka[20] = "vrsteParfema.bin";

	FILE* fp = NULL;
	fp = fopen(datoteka, "rb");
	if (fp == NULL) {
		fp = fopen(datoteka, "wb");
		int num = 0;
		fwrite(&num, sizeof(int), 1, fp);
		fprintf(stdout, "Datoteka %s stvorena je na disku.\n", datoteka);
		fclose(fp);
	}
	else {
		fprintf(stdout, "Datoteka %s spremna.\n", datoteka);
		fclose(fp);
	}

	while (choice) {
		choice = izbornik(datoteka);
	}

	printf("Zavrsetak programa!\n");

	return 0;
}
