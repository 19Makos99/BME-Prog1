#ifndef HASH_H
#define HASH_H

#include <stdbool.h>

#include "lancolt_lista.h"

// A hash tabla felepitese a feladatbol kovetkezik.
// A meret megadja, hogy a tabla hany lancolt listat tartalmaz.
// A tabla az egy dinamikusan foglalt tomb, ami elemei lancolt listak elso elemeire mutató pointereket tarol, ebben tarolodnak el az adatok.
typedef struct HashTabla {
    int meret;
    LancSzem** tabla;
} HashTabla;

typedef enum HashTabla_hibakod {
    nincs_hiba,
    sikertelen_memoria_foglalas,
    nem_null_a_hivo_hash_tabla,
    sikertelen_fajl_megnyitas,
    sikertelen_beolvasas,
    nem_egyedi_a_kulcs,
    helytelen_formatum
} HashTabla_hibakod;

// Egy kulcs alapjan hash erteket keszit.
// Parametere: egy null karakterrel lezart karakter tomb, ami alapjan keszul a hash.
unsigned long hash(char* str);

// Letrehoz egy dinamikusan foglalt hash tablat.
// Hasznalat utan fel kell szabaditani, a hash_tabla_felszabadittal.
// Parameterei:
// h - egy NULL pointerre mutato pointer kell, hogy legyen, ebbe kerul bele a hash tabla.
// meret - a hash tabla vodreinek a szamat adja meg.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool hash_tabla_init(HashTabla** h, int meret);

// A hash tablat atmeretezi es annak megfeleloen ujrarendezi az elemeit.
// Sikertelen atmeretezes eseten a hash tabla valtozatlan marad.
// Parameterei:
// h - egy hash tabla pointerre mutató pointer kell, hogy legyen, ebbe kerul bele az uj hash tabla.
// meret - az uj hash tabla vodreinek a szamat adja meg.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool hash_tabla_atmeretez(HashTabla** h, int meret);

// Kiirja a hash tabla tartalmat.
// Parametere: A kiirando hash tablara mutato pointer.
void hash_tabla_kiir(const HashTabla* h);

// Kiirja az adott kulcsu elemet ha letezik.
// Parameterei:
// h - egy hash tablara mutato pointer, aminek az elemet szeretnenk kiiratni.
// kulcs - egy null karakterrel lezart karakter tomb, ami a kiirando elem kulcsat tartalmazza.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool hash_tabla_lancszem_kiir(const HashTabla* h, char* kulcs);

// Megvizsgalja, hogy az adott kulcs szerepel-e a hash tablaban.
// Parameterei:
// h - egy hash tablara mutato pointer, aminek az elemet szeretnenk megtalalni.
// kulcs - egy null karakterrel lezart karakter tomb, ami a keresett kulcsot tartalmazza.
// Visszateresi erteke, hogy szerepel-e az adott kulcs a hash tablaban.
bool hash_tabla_benne_van_e(const HashTabla* h, char* kulcs);

// A hash tablaban elhelyezi az adott lancszemet, ha a tabla nem tartalmazza az adott kulcsot.
// Parameterei:
// h - egy hash tablara mutato pointer, amiben a lancszemet szertnenk elhelyezni.
// x - a hash tablaban elhelyezendo lancszemet kell tartalmazza.
// Visszateresi erteke, egy hibakod, ami a hiba okat vagy annak hianyat tartalmazza.
HashTabla_hibakod hash_tabla_lancszem_betesz(HashTabla* h, LancSzem x);

// A hash tablabol eltavolitja azt az elemet, amelynek a kulcsa megegyezik a megadott kulcsal.
// Parameterei:
// h - egy hash tablara mutato pointer, aminek az elemet szeretnenk eltavolitani.
// kulcs - egy null karakterrel lezart karakter tomb, ami a torlendo elem kulcsat tartalmazza.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool hash_tabla_lancszem_torol(HashTabla* h, char *kulcs);

// Megadja a hash tabla telitettseget %-ban (5 jelent 500%-ot).
// A hash tabla vegtelen elemet tud tarolni, viszont magas telitettseg mellett lassubbak a muveletek.
// Parametere: egy hash tablara mutato pointer, amirol szeretnenk megtudni a telitettseget.
// Visszateresi erteke egy szam, ami a telitettseget jeloli.
double hash_tabla_telitettseg(const HashTabla* h);

// Dinamikusan foglalt hash tablat felszabadit.
// Hasznalata utan a pointert nullara allitja, igy hasznalhato uj hash tabla alapjakent.
// Parametere: a felszabaditando hash tablara mutato pointerre mutató pointer.
void hash_tabla_felszabadit(HashTabla** h);

// Beolvas egy fajlbol adatokat amit, egy dinamikusan foglalt hash tablaban eltarol.
// Null pointerrel kell meghivni.
// Hasznalat utan fel kell szabaditani, a hash_tabla_felszabadittal.
// Parameterei:
// h - egy NULL pointerre mutato pointer kell, hogy legyen, ebbe kerul bele a hash tabla.
// fajl_nev - egy null karakterrel lezart karakter tomb, ami a beolvasando fajl nevet tartalmazza.
// Visszateresi erteke egy hibakod, amibol kiderul, hogy sikeres volt-e a muvelet, vagy mi miatt nem sikerult vegrehajtani.
HashTabla_hibakod hash_tabla_beolvas(HashTabla** h, const char* fajl_nev);

// Kiir egy hash tablabol adatokat a megadott fajlba.
// Parameterei:
// h - az elmentendo hash tablara mutato pointer.
// fajl_nev - egy null karakterrel lezart karakter tomb, ami a mentendo fajl nevet tartalmazza.
// Visszateresi erteke egy hibakod, amibol kiderul, hogy sikeres volt-e a muvelet, vagy mi miatt nem sikerult vegrehajtani.
HashTabla_hibakod hash_tabla_mentes(const HashTabla* h, const char* fajl_nev);

// Kiirja szovegesen a konzolba a megadott hibakodot.
// Parametere: a kiirando hibakod.
void hash_tabla_hiba_kiir(HashTabla_hibakod hiba);

// Beolvas minden karaktert ';' vagy EOF-ig, amit egy dinamikusan foglalt tombkent ad vissza amit, hasznalat utan fel kell szabaditani.
// Parameteri:
// str - egy NULL pointerre mutato pointer kell, hogy legyen, ebbe kerul bele a kiolvasott nev.
// fp - egy file pointer, amibol a nevet szeretnenk kiolvasni.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool nev_beolvas_fajlbol(char** str, FILE* fp);
#endif