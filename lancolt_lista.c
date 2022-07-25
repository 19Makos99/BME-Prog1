#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lancolt_lista.h"
#include "debugmalloc.h"

void lancolt_lista_init(LancSzem** l) {
    *l = NULL;
}

void lancolt_lista_kiir(const LancSzem* l) {
    if (l == NULL)
        return;
    printf("%s: %d-%d-%d\n", l->kulcs, l->adat.ev, l->adat.ho, l->adat.nap);
    lancolt_lista_kiir(l->kovetkezo);
}

bool lancolt_lista_kiir_lancszem(const LancSzem* l, char* kulcs) {
    if (l == NULL)
        return false;
    if (strcmp(l->kulcs, kulcs) == 0) {
        printf( "Nev: %s\n"
                "Szuletesnap: %d-%02d-%02d\n", l->kulcs, l->adat.ev, l->adat.ho, l->adat.nap);
        return true;
    }
    return lancolt_lista_kiir_lancszem(l->kovetkezo, kulcs);
    
}

void lancolt_lista_kiir_fajlba(const LancSzem* l, FILE* fp) {
    if (l == NULL)
        return;
    fprintf(fp, "%s;%d-%d-%d\n", l->kulcs, l->adat.ev, l->adat.ho, l->adat.nap);
    lancolt_lista_kiir_fajlba(l->kovetkezo, fp);
}

bool lancolt_lista_benne_van_e(const LancSzem* l, char* kulcs) {
    if (l == NULL)
        return false;
    if (strcmp(kulcs, l->kulcs) == 0)
        return true;
    return lancolt_lista_benne_van_e(l->kovetkezo, kulcs);
}

bool lancolt_lista_betesz(LancSzem** l, LancSzem x) {
    LancSzem * uj = (LancSzem*)malloc(sizeof(LancSzem));
    if (uj == NULL)
        return false;
    uj->kulcs = (char*)malloc(sizeof(char) * (strlen(x.kulcs) + 1));
    if (uj->kulcs == NULL) {
        free(uj);
        return false;
    }
    strcpy(uj->kulcs, x.kulcs);
    uj->adat = x.adat;
    uj->kovetkezo = *l;
    *l = uj;
    return true;
}

bool lancolt_lista_torol(LancSzem** l, char *kulcs) {
    if (*l == NULL)
        return false;
    if (strcmp((*l)->kulcs, kulcs) != 0)
        return lancolt_lista_torol(&(*l)->kovetkezo, kulcs);
    LancSzem* kovetkezo = (*l)->kovetkezo;
    free((*l)->kulcs);
    free(*l);
    *l = kovetkezo;
    return true;
}

int lancolt_lista_hossz(const LancSzem* l) {
    if (l == NULL)
        return 0;
    return 1 + lancolt_lista_hossz(l->kovetkezo);
}

void lancolt_lista_felszabadit(LancSzem** l) {
    if (*l == NULL)
        return;
    lancolt_lista_felszabadit(&(*l)->kovetkezo);
    free((*l)->kulcs);
    free(*l);
    *l = NULL;
}