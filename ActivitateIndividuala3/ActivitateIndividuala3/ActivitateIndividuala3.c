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

void pushStack(Nod** stiva, Student s) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = s;
	nou->next = stiva;
	*stiva = nou;
}

Student popStack(Nod** stiva) {
	if ((*stiva)) {
		Student nou = (*stiva)->info;
		Nod* prev = (*stiva);
	}
}

int main() {

}