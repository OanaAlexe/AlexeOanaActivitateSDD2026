#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
	int id;
	int varsta;
	float medie;
	char* nume;
	char* facultate;
	unsigned char grupa;
};

typedef struct	Student Student;
typedef struct Nod Nod;

struct Nod {
	Student info;
	Nod* dr;
	Nod* stg;
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
	printf("Id: %d\nVarsta: %d\nMedia: %.2f\nNume: %s\nFacultate: %s\nGrupa: %c", s.id, s.varsta, s.medie, s.nume, s.facultate, s.grupa);
}

int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina) {
		int inaltimeSTG = calculeazaInaltimeArbore(radacina->stg);
		int inaltimeDR = calculeazaInaltimeArbore(radacina->dr);
		return 1 + (inaltimeDR > inaltimeSTG ? inaltimeDR : inaltimeSTG);
	}
	else {
		return 0;
	}
}

void rotireStg(Nod** radacina) {
	Nod* nod;
	nod = (*radacina)->dr;
	(*radacina)->dr = nod->stg;
	nod->stg = *radacina;
	*radacina = nod;
}

void rotireDr(Nod** radacina) {
	Nod* nod;
	nod = (*radacina)->stg;
	(*radacina)->stg = nod->dr;
	nod->dr = (*radacina);
	(*radacina) = nod;
}

int gradEchilibru(Nod* radacina) {
	if (radacina) {
		return calculeazaInaltimeArbore(radacina->dr) - calculeazaInaltimeArbore(radacina->stg);
	}
	else {
		return 0;
	}
}

void adaugaStudentInArbore(Nod** radacina, Student studentNou){
	if (*radacina) {
		if (studentNou.id > (*radacina)->info.id) {
			adaugaStudentInArbore(&(*radacina)->dr, studentNou);
		}
		else if(studentNou.id < (*radacina)->info.id){
			adaugaStudentInArbore(&(*radacina)->stg, studentNou);
		}
		int gradEch = gradEchilibru(&radacina);
		if (gradEch == 2) { //dezechilibru dreapta
			if (gradEchilibru((*radacina)->dr == -1)){ //rotatie rl
				rotireDr(radacina);
			}
			rotireStg(radacina);
		}
		else if (gradEch == -2) { //dezechilibru stanga 
			if (gradEchilibru((*radacina)->stg) == 1) { //rotatie lr????
				rotireStg(radacina);
			}
			rotireDr(radacina);
		}
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = studentNou;
		nou->dr = NULL;
		nou->stg = NULL;
		nou = *radacina;
	}
}

Nod* citireArboreDeStudentiDinFisier(const char numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* arbore = NULL;
	while (!feof(f)) {
		Student s = citireStudentDinFisier(f);
		adaugaStudentInArbore(arbore, s);
	}
	fclose(f);
	return arbore;
}
//RSD
void afisarePreOrdine(Nod* arbore) {
	if (arbore) {
		afisareStudent(arbore->info);
		afisarePreOrdine(arbore->stg);
		afisarePreOrdine(arbore->dr);
	}
}

//SRD
void afisareInOrdine(Nod* arbore) {
	if (arbore) {
		afisareInOrdine(arbore->stg);
		afisareStudent(arbore->info);
		afisareInOrdine(arbore->dr);
	}
}

int main() {

}