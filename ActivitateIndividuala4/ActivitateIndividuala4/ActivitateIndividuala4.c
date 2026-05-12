#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct StructuraStudent {
	int id;
	int varsta;
	float medie;
	char* nume;
	char* facultate;
	unsigned char grupa;
};

typedef struct StructuraStudent Student;

struct Heap {
	int lungime; //cat poate efectiv sa stocheze
	Student* studenti;
	int nrStudenti; //nr real de studenti din heap
};

typedef struct Heap Heap;	

Student citireStudentDinFisier(FILE* fisier) {
	Student s;
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	aux = fgets(buffer, 100, fisier);
	aux = strtok(buffer, sep);
	s.id = atoi(aux);
	aux = strtok(NULL, sep);
	s.varsta = atoi(aux);
	aux = strtok(NULL, sep);
	s.medie = atof(aux);
	aux = strtok(NULL, sep);
	s.nume = (char*)maloc(strlen(aux) + 1);
	strcpy_s(s.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	s.facultate = (char*)maloc(strlen(aux) + 1);
	strcpy_s(s.facultate, strlen(aux) + 1, aux);
	s.grupa = *strtok(NULL, sep);
	return s;
}

void afisareStudent(Student s) {
	printf("Id: %d\n", s.id);
	printf("Varsta: %d\n", s.varsta);
	printf("Medie: %.2f\n", s.medie);
	printf("Nume: %s\n", s.nume);
	printf("Facultate: %s\n", s.facultate);
	printf("Grupa: %c\n", s.grupa);
}
Heap initializeazaHeap(int lungime) {
	Heap h;
	h.lungime = lungime; 
	h.studenti = (Student*)malloc(sizeof(Student) * lungime);
	h.nrStudenti = 0;
}

void filtreazaHeap(Heap h, int pozNod) {
	if (pozNod > 0 && pozNod < h.nrStudenti) {
		int stg = 2 * pozNod + 1;
		int dr = 2 * pozNod + 2;
		int pozMax = pozNod;
		if (stg < h.nrStudenti && h.studenti[pozMax].id < h.studenti[stg].id) {
			pozMax = stg;
		}
		if (dr < h.nrStudenti && h.studenti[pozMax].id < h.studenti[dr].id) {
			pozMax = dr;
		}
	}
}

int main() {

}