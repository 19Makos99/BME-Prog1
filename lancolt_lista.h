#ifndef LANCOLT_LISTA_H
#define LANCOLT_LISTA_H

#include <stdio.h>
#include <stdbool.h>

#include "adat.h"

// A lancolt lista a kovetketo lancszemekbol epul fel.
// Erre az elemre azert van szukseg, hogy a hash tablaban azonos hash-el rendelkezo elemeket a hash tabla tombjeben azonos pozicióban el lehessen helyezni.
// A kulcs az illetok nevet tartalmazza, ami egyedi kulcskent szolgal a hash tablas tarolasnal.
// Az adat az illetok szuletesi datumat tarolja el.
// A kovetkezo a lancolt listaban kovetkezo elem cimet tarolja el.
typedef struct LancSzem {
    char* kulcs;
    Idopont adat;
    struct LancSzem* kovetkezo;
} LancSzem;

// Sorban kiirja a lancolt lista elemeit.
// Parametere: a kiirando lancolt lista elso elemere mutato pointer.
void lancolt_lista_kiir(const LancSzem* l);

// Kiirja a megadott kulcsu elemet a konzolba, ha letezik.
// Parameterei:
// l - a kiirando elemet tartalmazo lancolt lista elso elemere mutato pointer.
// kulcs - egy null karakterrel lezart karakter tomb, ami kiirando elem kulcsat tartalmazza.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool lancolt_lista_kiir_lancszem(const LancSzem* l, char* kulcs);

// Sorban kiirja a lancolt lista elemeit, a fajlpointer fajljaba.
// Parameterei:
// l - a kiirando lancolt lista elso elemere mutato pointer.
// fp - egy fajl pointer, amibe szeretnenk beleirni a lancolt listat.
void lancolt_lista_kiir_fajlba(const LancSzem* l, FILE* fp);

// Megvizsgalja, hogy az adott kulcs szerepel-e a listaban.
// Parameterei:
// l - a megvizsgalando lancolt lista elso elemere mutato pointer.
// kulcs - egy null karakterrel lezart karakter tomb, ami a keresett elem kulcsat tartalmazza.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool lancolt_lista_benne_van_e(const LancSzem* l, char* kulcs);

// A lancolt lista elejere berakja az elemet es ahhoz fuzi hozza a tobbit.
// Parameterei:
// l - a lancolt lista elso elemere mutato pointerre mutato pointer.
// x - a lancolt listaba betenni kivant lancszem.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool lancolt_lista_betesz(LancSzem** l, LancSzem x);

// Megkeresi, az adott elemet a lancolt listaban kulcs alapjan es eltavolitja.
// Parameterei:
// l - a lancolt lista elso elemere mutato pointerre mutato pointer.
// kulcs - egy null karakterrel lezart karakter tomb, ami az eltavolitando elem kulcsat tartalmazza.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool lancolt_lista_torol(LancSzem** l, char* kulcs);

// Megadja a lancolt lista hosszat.
// Parametere: egy lancolt lista elso elemere mutato pointer, amirol megszeretnenk tudni a hosszat.
// Visszateresi erteke, a lancolt lista hossza.
int lancolt_lista_hossz(const LancSzem* l);

// Dinamikusan foglalt lancolt listat felszabadit.
// Hasznalata utan a pointert nullara allitja, igy hasznalhato uj lancolt lista alapjakent.
// Parametere: egy lancolt lista elso elemere mutato pointerre mutato pointer, aminek a tartalmat fel szeretnenk szabaditani.
void lancolt_lista_felszabadit(LancSzem** l);

#endif