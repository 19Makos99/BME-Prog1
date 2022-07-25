#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

#include "adat.h"
#include "hash.h"

// Letorli a kepernyot.
void kepernyo_torol();

// Megjeleniti a fomenut.
void fomenu_megjelenit();

// Megjeleniti a kereses menut.
void kereses_menu_megjelenit();

// Addig ker be szamokat amig, a felhasznalo helyes szamot nem ad a fomenu opcioibol.
// Csak helyes erteket ad vissza.
// Visszateresi erteke a fomenu opcioi kozul az egyik.
int fomenu_szam_beker();

// Addig ker be szamokat amig, a felhasznalo helyes szamot nem ad a kereses menu opcioibol.
// Csak helyes erteket ad vissza.
// Visszateresi erteke a kereses menu opcioi kozul az egyik.
int kereses_menu_szam_beker();

// Megvizsgalja, hogy a tomben szerepel-e a keresett szam.
// Parameterei:
// elfogadhato – egy tomb, ami az elfogadhato szamokat tartalmazza.
// hossz – az elso parameternek a hosszát kell tartalmazza!
// szam – a keresett szám.
// Visszateresi erteke, hogy szerepel-e a tombben a megadott szam.
bool benne_van_e(const int* elfogadhato, int hossz, int szam);

// Beolvas a konzolbol egy sort, amit dinamikusan foglalt stringkent adja vissza, amit fell kell majd szabaditani.
// Parametere: egy char pointerre mutato pointer, ebbe kerul bele a beolvasott nev.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool nev_beker(char** nev);

// Beolvas egy datumot a konzolbol ev-honap-nap formatumban.
// Parametere: egy Idopont pointer, amibe belekerul a megadott adat.
// Visszateresi erteke, hogy sikerrel jart-e a muvelet.
bool datum_beker(Idopont* datum);

// Minden karaktert elnyel, amit a felhasznalo ir uj sor karakterig.
void varakozas_enterre();

// A fomenut iranyitja a felhasznalo altal kivalasztott menupontok alapjan hivja meg a kello fuggvenyeket.
// Parametere: a menukon belul hasznalni kivant hash tablara mutato pointerre mutato.
void fomenu_iranyit(HashTabla** h);

// Beker egy nevet, egy szuletesi datumot, amit megprobal elmenteni a hash tablaban.
// A nevet csak egyszer probalja meg bekerni.
// A datumot addig keri be amig, a felhasznalo helyes formatumban meg nem adja, a datumot.
// Ha a nev szerepel mar a hash tablaban, vagy sikertelen valamelyik memoria foglalas, akkor a program kiirja a hiba okat es return-ol.
// Parametere: az uj adat ebben a hash tablaban kerul elmentesre.
void uj_szuletesnap(HashTabla* h);

// Az uj_szuletesnap fuggveny meghivasakor fellepo, hibakat vagy azok hianyat kiirja a kepernyore.
// Parametere: ennek a hibakodnak a jelenteset irja ki a konzolra.
void uj_szuletesnap_hiba_kiir(HashTabla_hibakod hiba);

// Elmenti a hash tablat a megadott fajlneven.
// A muvelet sikeresseget kiirja.
// Parameterei:
// h - az elmentendo hash tablara mutato pointer.
// fajl_nev - egy null karakterrel lezart karakter tomb, ami a mentendo fajl nevet tartalmazza.
void mentes(const HashTabla* h, const char* fajl_nev);

// Beker egy nevet beture pontosan.
// Ha szerepel a nev a hash tablaban, akkor felajanlja a modositasat, torleset vagy informaciokat rola.
// A modositasnal bekeri az uj adatokat, elmenti a hash tablaban es return-ol.
// A torlesnel torli a hash tablabol es return-ol.
// Az informacional kiirja az illeto adatait.
// Hiba eseten kiirja a hiba okat es return-ol.
// Parametere: ebben a hash tablaban keresi a nevet.
void kereses_nev_alapjan(HashTabla* h);

// A megadott nevu illeto adatainak megtekintesere, modositasara, torlesere jelenit meg egy menut.
// A modositasnal bekeri az uj adatokat, elmenti a hash tablaban es return-ol.
// A torlesnel torli a hash tablabol es return-ol.
// Az informacional kiirja az illeto adatait.
// Hiba eseten kiirja a hiba okat es return-ol
// Parameterei:
// h - ezen a hash tablan vegezi el a felhasznalo altal megadott feladatot.
// nev - egy null karakterrel lezart karakter tomb, ami a kezelendo illeto nevet tartalmazza.
void kivalasztott_nev_kezeles(HashTabla* h, char* nev);
#endif