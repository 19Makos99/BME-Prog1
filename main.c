#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lancolt_lista.h"
#include "hash.h"
#include "menu.h"
#include "debugmalloc.h"

// Megprobalja beolvasni a szuletesnapok.txt-t.
// Ha nem sikerult beolvasni, rossz formatum miatt, akkor kiirja azt es a program kilep.
// Ha nem letezik a fajl akkor letrehoz egy ures hash tablat.
// A fomenut iranyitja a felhasznalo altal kivalasztott menupontok alapjan a hash tabla segitsegevel.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
int main() {
    HashTabla* tabla = NULL;
    HashTabla_hibakod hiba = hash_tabla_beolvas(&tabla, "szuletesnapok.txt");
    if (hiba == sikertelen_fajl_megnyitas) {
        hash_tabla_init(&tabla, 100);
    } else if (hiba != nincs_hiba) {
        hash_tabla_hiba_kiir(hiba);
        return -1;
    }
    char nev[] = "Szabo Bence"; 
    hash_tabla_lancszem_betesz(tabla, (LancSzem){ nev, {1998, 7, 11}, NULL });
    fomenu_iranyit(&tabla);
    hash_tabla_felszabadit(&tabla);
    return 0;
}