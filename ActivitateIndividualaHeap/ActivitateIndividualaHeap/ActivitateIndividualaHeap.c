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

struct Heap {
	Student* studenti;
	int lungime;
	int nrStudenti;
};
typedef struct Heap Heap;

Student citireStudentDinFisier(FILE* f) {
	Student s;
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	 fgets(buffer, 100, f);
	 aux = strtok(buffer, sep);
	s.id = atoi(aux);
	s.varsta = atoi(strtok(NULL, sep));
	s.medie = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	s.nume = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	s.facultate = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.facultate, strlen(aux) + 1, aux);
	s.grupa = *strtok(NULL, sep);
	return s;
}

void afisareStudet(Student s) {
	printf("Id: %d\n", s.id);
	printf("Varsta: %d\n", s.varsta);
	printf("Medie: %.2f\n", s.medie);
	printf("Nume: %s\n", s.nume);
	printf("Facultate: %s\n", s.facultate);
	printf("Grupa: %c\n", s.grupa);
}

Heap initializareHeap( int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrStudenti = 0;
	heap.studenti = (Student*)malloc(sizeof(Student) * lungime);
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	if (pozitieNod >=0 && pozitieNod < heap.nrStudenti) {
		int pozStg = 2 * pozitieNod + 1;
		int pozDr = 2 * pozitieNod + 2;
		int pozMax = pozitieNod;
		if (pozStg < heap.nrStudenti && heap.studenti[pozMax].id < heap.studenti[pozStg].id) {
			pozMax = pozStg;
		}
		if (pozDr < heap.nrStudenti && heap.studenti[pozMax].id < heap.studenti[pozDr].id) {
			pozMax = pozDr;
		}
		if (pozMax != pozitieNod) {
			Student aux = heap.studenti[pozMax];
			heap.studenti[pozMax] = heap.studenti[pozitieNod];
			heap.studenti[pozitieNod] = aux;
			if (pozMax < (heap.nrStudenti - 1) / 2) {
				filtreazaHeap(heap, pozMax);
			}
		}
	}
}

Heap citireHeapDinFisier(const char* numeFisier) {
	Heap heap = initializareHeap(10);
	FILE* f = fopen(numeFisier, "r");
	int index = 0;
	while (!feof(f)) {
		heap.studenti[index] = citireStudentDinFisier(f);
		index++;
	}
	heap.nrStudenti = index;
	fclose(f);
	for (int i = (heap.nrStudenti - 1) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afiseazaHeap(Heap heap) {
	for (int i = 0; i < heap.nrStudenti; i++) {
		afisareStudet(heap.studenti[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {
	for (int i = heap.nrStudenti; i < heap.lungime; i++) {
		afisareStudet(heap.studenti[i]);
	}
}

Student extrageStudenti(Heap* heap) {
	Student aux = heap->studenti[0];
	heap->studenti[0] = heap->studenti[heap->nrStudenti - 1];
	heap->studenti[heap->nrStudenti - 1] = aux;
	heap->nrStudenti--;
	for (int i = (heap->nrStudenti - 1) / 2; i >= 0; i--) {
		filtreazaHeap(*heap, i);
	}
	return aux;
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->nrStudenti; i++) {
		free(heap->studenti[i].nume);
		free(heap->studenti[i].facultate);
	}
	free(heap->studenti);
	heap->lungime = 0;
	heap->nrStudenti = 0;
	heap->studenti = NULL;
}

int main() {
	Heap heap = citireHeapDinFisier("studenti.txt");
	afiseazaHeap(heap);
	filtreazaHeap(heap, 0);
	printf("\n\nHeap dupa filtrare:\n");
	afiseazaHeap(heap);

	extrageStudenti(&heap);
	extrageStudenti(&heap);
	printf("\n\nHeap dupa extragere:\n");
	afiseazaHeap(heap);

	afiseazaHeapAscuns(heap);
	printf("\n\nHeap ascuns:\n");
	afiseazaHeap(heap);

	dezalocareHeap(&heap);
}