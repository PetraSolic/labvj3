#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktura za definiranje osobe
typedef struct Osoba {
    char ime[50];
    char prezime[50];
    int godina_rodenja;
    struct Osoba* sljedeca;
} Osoba;

// Funkcija za stvaranje nove osobe
Osoba* stvori_osobu(const char* ime, const char* prezime, int godina_rodenja) {
    Osoba* nova_osoba = (Osoba*)malloc(sizeof(Osoba));
    if (nova_osoba == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        exit(1);
    }
    strcpy(nova_osoba->ime, ime);
    strcpy(nova_osoba->prezime, prezime);
    nova_osoba->godina_rodenja = godina_rodenja;
    nova_osoba->sljedeca = NULL;
    return nova_osoba;
}

// A. Dodavanje osobe na početak liste
void dodaj_na_pocetak(Osoba** glava, Osoba* nova_osoba) {
    nova_osoba->sljedeca = *glava;
    *glava = nova_osoba;
}

// B. Ispisivanje liste
void ispis_liste(Osoba* glava) {
    Osoba* trenutna = glava;
    while (trenutna != NULL) {
        printf("%s %s, %d\n", trenutna->ime, trenutna->prezime, trenutna->godina_rodenja);
        trenutna = trenutna->sljedeca;
    }
}

// C. Dodavanje osobe na kraj liste
void dodaj_na_kraj(Osoba** glava, Osoba* nova_osoba) {
    if (*glava == NULL) {
        *glava = nova_osoba;
    }
    else {
        Osoba* trenutna = *glava;
        while (trenutna->sljedeca != NULL) {
            trenutna = trenutna->sljedeca;
        }
        trenutna->sljedeca = nova_osoba;
    }
}

// D. Pronalaženje osobe po prezimenu
Osoba* pronadi_po_prezimenu(Osoba* glava, const char* prezime) {
    Osoba* trenutna = glava;
    while (trenutna != NULL) {
        if (strcmp(trenutna->prezime, prezime) == 0) {
            return trenutna;
        }
        trenutna = trenutna->sljedeca;
    }
    return NULL;
}

// E. Brisanje osobe po prezimenu
int brisi_po_prezimenu(Osoba** glava, const char* prezime) {
    Osoba* trenutna = *glava;
    Osoba* prethodna = NULL;

    while (trenutna != NULL) {
        if (strcmp(trenutna->prezime, prezime) == 0) {
            if (prethodna == NULL) {
                *glava = trenutna->sljedeca;
            }
            else {
                prethodna->sljedeca = trenutna->sljedeca;
            }
            free(trenutna);
            return 1;
        }
        prethodna = trenutna;
        trenutna = trenutna->sljedeca;
    }
    return 0;
}

// Glavna funkcija za demonstraciju rada
int main() {
    Osoba* glava = NULL;

    // Dodavanje novih osoba na početak i kraj liste
    dodaj_na_pocetak(&glava, stvori_osobu("Ivan", "Ivic", 1990));
    dodaj_na_kraj(&glava, stvori_osobu("Ana", "Anic", 1985));

    // Ispis liste
    printf("Ispis liste:\n");
    ispis_liste(glava);

    // Pronalaženje osobe po prezimenu
    printf("\nPronalaženje osobe s prezimenom 'Anic':\n");
    Osoba* pronadena_osoba = pronadi_po_prezimenu(glava, "Anic");
    if (pronadena_osoba) {
        printf("Pronađena osoba: %s %s, %d\n", pronadena_osoba->ime, pronadena_osoba->prezime, pronadena_osoba->godina_rodenja);
    }
    else {
        printf("Osoba s tim prezimenom nije pronađena.\n");
    }

    // Brisanje osobe po prezimenu
    printf("\nBrisanje osobe s prezimenom 'Ivic':\n");
    if (brisi_po_prezimenu(&glava, "Ivic")) {
        printf("Osoba uspješno obrisana.\n");
    }
    else {
        printf("Osoba nije pronađena za brisanje.\n");
    }

    // Ispis liste nakon brisanja
    printf("\nIspis liste nakon brisanja:\n");
    ispis_liste(glava);

    // Oslobađanje memorije
    while (glava != NULL) {
        Osoba* za_brisanje = glava;
        glava = glava->sljedeca;
        free(za_brisanje);
    }

    return 0;
}
