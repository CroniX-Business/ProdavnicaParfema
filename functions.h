#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "dataType.h"
	int izbornik(const char* const);
	int confirmExit(int, PARFEM*);
	void* admin();
	void* dodajParfem(const char* const);
	void* ucitavanjeParfema(const char* const);
	void* ispisParfema(const PARFEM* const);
	void* ispisPronadenogParfema(const PARFEM* const, int);
	void* pretrazivanjeParfema(PARFEM* const);
	void* brisanjeParfema(PARFEM** const, const PARFEM* const, const char* const);
	void* promijenaBaze(PARFEM* const, const char* const);
	void zamjena(PARFEM* veci, PARFEM* manji);
	void* sortiranjeUzlazno(PARFEM*, const char* const);
	void* sortiranjeSilazno(PARFEM*, const char* const);
#endif // FUNCTIONS_H
