#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "debugmalloc.h"

unsigned long hash(char* str) {
    unsigned long hash = 1 << (sizeof(unsigned long) * 8 - 2);

    for (int i = 0; str[i] != '\0'; i++)
        hash += str[i];

    return hash;
}

bool hash_tabla_init(HashTabla** h, int meret) {
    if (*h != NULL)
        return false;

    HashTabla* uj = (HashTabla*)malloc(sizeof(HashTabla));
    if (uj == NULL)
        return false;

    uj->meret = 0;
    uj->tabla = (LancSzem**)malloc(sizeof(LancSzem*) * meret);
    if (uj->tabla == NULL)
        return false;

    for (int i = 0; i < meret; i++)
        uj->tabla[i] = NULL;

    uj->meret = meret;
    *h = uj;
    return true;
}

bool hash_tabla_atmeretez(HashTabla** h, int meret) {
    if (meret < 1)
        return false;
    HashTabla* eredeti = *h;
    HashTabla* uj = NULL;
    if (!hash_tabla_init(&uj, meret))
        return false;

    bool hibatlan = true;
    for (int i = 0; i < eredeti->meret && hibatlan; i++) {
        LancSzem* vizsgalt = eredeti->tabla[i];

        while (vizsgalt != NULL && hibatlan) {
            hibatlan = nincs_hiba == hash_tabla_lancszem_betesz(uj, (LancSzem){ vizsgalt->kulcs, vizsgalt->adat, NULL });
            vizsgalt = vizsgalt->kovetkezo;
        }
    }

    if (hibatlan) {
        hash_tabla_felszabadit(h);
        *h = uj;
        return true;
    }

    hash_tabla_felszabadit(&uj);
    return false;
}

void hash_tabla_kiir(const HashTabla* h) {
    for (int i = 0; i < h->meret; i++)
        lancolt_lista_kiir(h->tabla[i]);
}

bool hash_tabla_lancszem_kiir(const HashTabla* h, char* kulcs) {
    int index = hash(kulcs) % h->meret;
    return lancolt_lista_kiir_lancszem(h->tabla[index], kulcs);
}

bool hash_tabla_benne_van_e(const HashTabla* h, char* kulcs) {
    int index = hash(kulcs) % h->meret;
    if (h->tabla[index] == NULL)
        return false;
    return lancolt_lista_benne_van_e(h->tabla[index], kulcs);
}

HashTabla_hibakod hash_tabla_lancszem_betesz(HashTabla* h, LancSzem x) {
    int index = hash(x.kulcs) % h->meret;
    if (lancolt_lista_benne_van_e(h->tabla[index], x.kulcs))
        return nem_egyedi_a_kulcs;
    return lancolt_lista_betesz(h->tabla + index, x) ? nincs_hiba : sikertelen_memoria_foglalas;
}

bool hash_tabla_lancszem_torol(HashTabla* h, char* kulcs) {
    int index = hash(kulcs) % h->meret;
    if (h->tabla[index] == NULL)
        return false;
    return lancolt_lista_torol(h->tabla + index, kulcs);
}

double hash_tabla_telitettseg(const HashTabla* h) {
    if (h->meret == 0)
        return 0;
    double db = 0;

    for (int i = 0; i < h->meret; i++)
        db += lancolt_lista_hossz(h->tabla[i]);

    return db / h->meret;
}

void hash_tabla_felszabadit(HashTabla** h) {
    HashTabla* x = *h;
    for (int i = 0; i < x->meret; i++)
        lancolt_lista_felszabadit(&x->tabla[i]);
    free(x->tabla);
    free(x);
    *h = NULL;
}

HashTabla_hibakod hash_tabla_beolvas(HashTabla** h, const char* fajl_nev) {
    if (*h != NULL)
        return nem_null_a_hivo_hash_tabla;

    FILE* fp = fopen(fajl_nev, "rt");
    if (fp == NULL)
        return sikertelen_fajl_megnyitas;

    int meret;
    if (fscanf(fp, "%d\n", &meret) != 1) {
        fclose(fp);
        return sikertelen_beolvasas;
    }

    HashTabla* uj = NULL;
    if (!hash_tabla_init(&uj, meret)) {
        fclose(fp);
        return sikertelen_memoria_foglalas;
    }

    char* str = NULL;
    Idopont adat;
    int sikeres;
    if (!nev_beolvas_fajlbol(&str, fp)) {
        fclose(fp);
        hash_tabla_felszabadit(&uj);
        return sikertelen_beolvasas;
    }
    sikeres = fscanf(fp, "%d-%d-%d", &adat.ev, &adat.ho, &adat.nap);
    while (sikeres == 3) {
        HashTabla_hibakod hiba = hash_tabla_lancszem_betesz(uj, (LancSzem){ str, adat, NULL });
        if (hiba != nincs_hiba) {
            fclose(fp);
            hash_tabla_felszabadit(&uj);
            return hiba;
        }
        free(str);
        str = NULL;
        if (!nev_beolvas_fajlbol(&str, fp)) {
            fclose(fp);
            hash_tabla_felszabadit(&uj);
            return sikertelen_beolvasas;
        }
        sikeres = 0;
        sikeres = fscanf(fp, "%d-%d-%d", &adat.ev, &adat.ho, &adat.nap);
    }
    free(str);
    fclose(fp);
    if (sikeres != EOF) {
        hash_tabla_felszabadit(&uj);
        return sikertelen_beolvasas;
    }
    *h = uj;
    return nincs_hiba;
}

bool nev_beolvas_fajlbol(char** str, FILE* fp) {
    if (*str != NULL)
        return false;
    *str = (char*)malloc(sizeof(char) * (100 + 1));
    if (*str == NULL)
        return false;
    char chr;
    int i = 0;
    fscanf(fp, " %c", &chr);
    while (chr != ';') {
        str[0][i] = chr;
        i++;
        if (i % 100 == 0) {
            char* uj = (char*)realloc(*str, sizeof(char) * (i + 100 + 1));
            if (uj == NULL) {
                free(*str);
                return false;
            }
            *str = uj;
        }
        if (fscanf(fp, "%c", &chr) == EOF)
            break;
    }
    str[0][i] = '\0';
    return true;
}

HashTabla_hibakod hash_tabla_mentes(const HashTabla* h, const char* fajl_nev) {
    FILE* fp = fopen(fajl_nev, "wt");
    if (fp == NULL)
        return sikertelen_fajl_megnyitas;

    fprintf(fp, "%d\n", h->meret);

    for (int i = 0; i < h->meret; i++) {
        lancolt_lista_kiir_fajlba(h->tabla[i], fp);
    }
    fclose(fp);
    return nincs_hiba;
}

void hash_tabla_hiba_kiir(HashTabla_hibakod hiba) {
    switch (hiba) {
        case nincs_hiba:
            printf("Nincs hiba.\n");
            break;
        case sikertelen_memoria_foglalas:
            printf("Sikertelen memoria foglalas.\n");
            break;
        case nem_null_a_hivo_hash_tabla:
            printf("A fuggveny parameterenek NULL pointernek kell, hogy legyen.\n");
            break;
        case sikertelen_beolvasas:
            printf("Rossz formatumu a fajl.\n");
            break;
        case nem_egyedi_a_kulcs:
            printf("Nem egyedi a kulcs.\n");
            break;
        default:
            printf("Ismeretlen hiba, hibakod: %d", hiba);
            break;
    }
}