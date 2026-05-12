//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
////creare structura pentru un nod dintr-o lista simplu inlantuita
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret= atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//typedef struct Nod Nod;
//
//struct Nod {
//	Masina info;
//	Nod* next; //pointer catre urmatorul nod din lista
//};
//
//void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
//	//adauga la final
//	//identificam o lista prin adresa primului nod
//	Nod* nou = malloc(sizeof(Nod)); //nu mai alocam spatiu si pt masina, pt ca nod contie masina
//	nou->info = masinaNoua; //shallow copy, dar e ok pentru ca nu modificam masinaNoua in nod
//	//nu facem de 2 ori dezalocarea pentru model si numeSofer, pentru ca nu modificam masinaNoua in nod
//	nou->next = NULL;
//	Nod* aux = *cap; 
//	if ((*cap) != NULL) { //daca avem cel putin un nod in lista
//		while (aux->next != NULL && aux->next != NULL) {
//			aux = aux->next;
//			//ma opresc pe ultimul nod, adica pe nodul care are next == NULL
//			//am nod in fata, ma mut pe el
//		}
//		aux->next = nou;
//	}
//	else (*cap) = nou; //daca lista era vida, nou devine primul nod
//}
//
//void afisareListaMasini(Nod* cap) {
//	while (cap) {
//		afisareMasina(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaLaInceputInLista(Nod**cap, Masina masinaNoua) {
//	//adauga la inceputul listei o noua masina pe care o primim ca parametru
//}
//
//void* citireListaMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* cap = NULL;
//	while(!feof(f)) {
//		Masina  m = citireMasinaDinFisier(f);
//		//void* este stramosul templateurilor, este pointer la orice
//		//void* returneaza un pointer
//		adaugaMasinaInLista(&cap, m); //shallow copy, trebuia sa dezaloc altfel
//	}
//	fclose(f);
//	return cap;
//}
//
//void dezalocareListaMasini(Nod** cap) {
//	Nod* aux = *cap;
//	Nod* urmator = NULL;
//	while (aux) {
//		urmator = aux->next;
//		free(aux->info.model);
//		free(aux->info.numeSofer);
//		free(aux);
//		aux = urmator;
//	}
//	*cap = NULL;
//}
//
//float calculeazaPretMediu(Nod* lista) {
//	float suma = 0;
//	int nrMasini = 0;
//	while (lista) {
//		suma += lista->info.pret;
//		nrMasini++;
//		lista = lista->next;
//	}
//	return suma > 0 ? suma / nrMasini : 0;
//}
//
//void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
//	//sterge toate masinile din lista care au seria primita ca parametru.
//	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//}
//
//float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//	return 0;
//}
//
//int main() {
//	Nod* lista = citireListaMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//	float pretMediu = calculeazaPretMediu(lista);
//	printf("\n==================================================================\n");
//	printf("Pretul mediu: %.2f\n", pretMediu);
//	dezalocareListaMasini(&lista);
//
//
//	printf("==================================================================\n");
//	afisareListaMasini(lista);
//	return 0;
//}