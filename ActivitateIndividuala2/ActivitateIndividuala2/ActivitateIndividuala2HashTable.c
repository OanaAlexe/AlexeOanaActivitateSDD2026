#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student {
	int id;
	int varsta;
	float medie;
	char* nume;
	char* facultate;
	unsigned char grupa;
};

typedef struct Student Student;
typedef struct Nod Nod;

struct Nod {
	Student info;
	Nod* next;
};

typedef struct HashTable HashTable;

struct HashTable {
	Nod** vector;
	int nrNoduri;
};


Student citireStudentDinFisier(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	Student s;
	fgets(buffer, 100, f);
	aux = strtok(buffer, sep);
	s.id = atoi(aux);
	aux = strtok(NULL, sep);
	s.varsta = atoi(aux);
	aux = strtok(NULL, sep);
	s.medie = atof(aux);
	aux = strtok(NULL, sep);
	s.nume = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	s.facultate = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.facultate, strlen(aux) + 1, aux);
	s.grupa = *strtok(NULL, sep);
	return s;
}

void afisareStudent(Student s) {
	printf("Id: %d\nVarsta: %d\nMedia: %.2f\nNume: %s\nFacultate: %s\n Grupa: %c\n", s.id, s.varsta, s.medie, s.nume, s.facultate, s.grupa);
}

void afisareListaStudenti(Nod* cap) {
	Nod* p = cap;
	while (p) {
		afisareStudent(p->info);
		p = p->next;
	}
}

void adaugaStudentInLista(Nod* cap, Student studNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = studNou;
	nou->next = NULL;
	while (cap->next) {
		cap = cap->next;
	}
	cap->next = nou;
}

HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.nrNoduri = dimensiune;
	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

int calculeazaHash(Student s, int dimensiune) {
	return s.id % dimensiune;
}

void insereazaStudentInHashTable(HashTable* ht, Student s) {
	int pozitie = calculeazaHash(s, ht->nrNoduri);
	if (ht->vector[pozitie] == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = s;
		nou->next = NULL;
		ht->vector[pozitie] = nou;
	}
	else {
		adaugaStudentInLista(ht->vector[pozitie], s);
	}
}

HashTable citireHashTableDinFisier(const char* numeFisier, int dim) {
	FILE* file = fopen(numeFisier, "r");
	HashTable ht = initializareHashTable(dim);
	while (!feof(file)) {
		insereazaStudentInHashTable(&ht, citireStudentDinFisier(file));
	}
	fclose(file);
	return ht;
}

void afiseazaHashTable(HashTable ht) {
	for (int i = 0; i < ht.nrNoduri; i++) {
		printf("Clusterul: %d\n", i + 1);
		afisareListaStudenti(ht.vector[i]);
		printf("\n");
	}
}

int main() {
	HashTable ht = citireHashTableDinFisier("studenti.txt", 5);
	afiseazaHashTable(ht);
}