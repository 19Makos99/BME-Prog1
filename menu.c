#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "debugmalloc.h"

static int szam_beker();

void kepernyo_torol() {
	system("cls||clear");
}

void fomenu_megjelenit() {
	printf(	"1: Uj szuletesnap megadasa\n"
			"2: Mentes\n"
			"3: Kereses nev alapjan\n"
			"9: Kilepes\n");
}

void kereses_menu_megjelenit() {
	printf(	"1: Vissza\n"
			"2: Modositas\n"
			"3: Torol\n"
			"4: Info\n");
}

bool benne_van_e(const int* elfogadhato, int hossz, int szam) {
	for (int i = 0; i < hossz; i++)
		if (elfogadhato[i] == szam)
			return true;
	return false;
}

int fomenu_szam_beker() {
	const int elfogadhato[4] = { 1, 2, 3, 9 };
	printf("Valaszd ki az egyik pontot: ");
	int szam = szam_beker();
	while (!benne_van_e(elfogadhato, 4, szam)) {
		kepernyo_torol();
		fomenu_megjelenit();
		printf("Valaszd ki az egyik pontot: ");
		szam = szam_beker();
	}
	return szam;
}

int kereses_menu_szam_beker() {
	const int elfogadhato[4] = { 1, 2, 3, 4 };
	printf("Valaszd ki az egyik pontot: ");
	int szam = szam_beker();
	while (!benne_van_e(elfogadhato, 4, szam)) {
		kepernyo_torol();
		kereses_menu_megjelenit();
		printf("Valaszd ki az egyik pontot: ");
		szam = szam_beker();
	}
	return szam;
}

bool nev_beker(char** nev) {
	*nev = (char*)malloc(sizeof(char) * (100 + 1));
	if (nev == NULL)
		return false;
	int i = 0;
	char chr;
	scanf(" %c", &chr);
	while (chr != '\n') {
		nev[0][i] = chr;
		i++;
		if (i % 100 == 0) {
			char* uj = (char*)realloc(nev, sizeof(char) * (i + 100 + 1));
			if (uj == NULL) {
				free(nev);
				varakozas_enterre();
				return false;
			}
			*nev = uj;
		}
		scanf("%c", &chr);
	}
	nev[0][i] = '\0';
	return true;
}

bool datum_beker(Idopont* datum) {
	Idopont temp;
	if (scanf(" %d-%d-%d", &temp.ev, &temp.ho, &temp.nap) != 3)
		return false;
	if (temp.ho > 12 || temp.ho < 1 || temp.nap < 1 || temp.nap > 31)
		return false;
	*datum = temp;
	return true;
}

static int szam_beker() {
	int szam;
	scanf(" %d", &szam);
	varakozas_enterre();
	return szam;
}

void varakozas_enterre() {
	char chr = '\0';
	while (chr != '\n') {
		scanf("%c", &chr);
	}
}

void fomenu_iranyit(HashTabla** tabla) {
    fomenu_megjelenit();
    int kivalasztott_menupont = fomenu_szam_beker();
    while (kivalasztott_menupont != 9) {
        double telitettseg = hash_tabla_telitettseg(*tabla);
        if (telitettseg > 50) {
            kepernyo_torol();
            printf("Adatok tarolasanak optimalizalasa.\nKerem varjon.");
            int szorzo = 2;
            while (telitettseg > 50) {
                szorzo *= 2;
                telitettseg /= 2;
            }
            hash_tabla_atmeretez(tabla, tabla[0]->meret * szorzo);
        }
        switch (kivalasztott_menupont) {
        case 1:
            uj_szuletesnap(*tabla);
            break;

        case 2:
            mentes(*tabla, "szuletesnapok.txt");
            break;

        case 3:
            kereses_nev_alapjan(*tabla);
            break;

        default:
            break;
        }
        kepernyo_torol();
        fomenu_megjelenit();
        kivalasztott_menupont = fomenu_szam_beker();
    }
}

void uj_szuletesnap(HashTabla* h) {
    kepernyo_torol();
    printf("Add meg az illeto nevet: ");
    char* nev = NULL;
    if (!nev_beker(&nev)) {
        printf("Sikertelen memoria foglalas.");
        varakozas_enterre();
        return;
    }
    if (hash_tabla_benne_van_e(h, nev)) {
        kepernyo_torol();
        printf("A nev mar szerepel a nyilvantartasban.");
        varakozas_enterre();
        free(nev);
        return;
    }
    Idopont datum;
    bool sikeres = false;
    while (!sikeres) {
        kepernyo_torol();
        printf("Add meg az illeto szuletesi datumat (ev-ho-nap): ");
        sikeres = datum_beker(&datum);
    }
    HashTabla_hibakod hiba = hash_tabla_lancszem_betesz(h, (LancSzem){ nev, datum, NULL });
    uj_szuletesnap_hiba_kiir(hiba);
    free(nev);
}

void uj_szuletesnap_hiba_kiir(HashTabla_hibakod hiba) {
    switch (hiba) {
        case nincs_hiba:
            kepernyo_torol();
            printf("Sikeresen elmentve.");
            varakozas_enterre();
            break;

        case sikertelen_memoria_foglalas:
            kepernyo_torol();
            printf("Sikertelen memoria foglalas.");
            varakozas_enterre();
            break;

        default:
            kepernyo_torol();
            printf("Ismeretlen hiba lepett fel.");
            varakozas_enterre();
            break;
    }
}

void mentes(const HashTabla* h, const char* fajl_nev) {
    HashTabla_hibakod hiba = hash_tabla_mentes(h, fajl_nev);
    kepernyo_torol();
    if (hiba == nincs_hiba)
        printf("Sikeresen el lettek mentve a szuletesnapok.\n");
    else
        printf("A szuletesnapok nem lettek elmentve. :(\n");
    varakozas_enterre();
}

void kereses_nev_alapjan(HashTabla* h) {
    kepernyo_torol();
    printf("Add meg az illeto nevet: ");
    char* nev = NULL;
    nev_beker(&nev);
    kepernyo_torol();
    if (!hash_tabla_benne_van_e(h, nev)) {
        printf("Nem szerepel ilyen nevu illeto!");
        varakozas_enterre();
        free(nev);
        return;
    }
    kivalasztott_nev_kezeles(h, nev);
    free(nev);
    return;
}

void kivalasztott_nev_kezeles(HashTabla* h, char* nev) {
    int valasztott = 0;
    while (valasztott != 1) {
        kepernyo_torol();
        kereses_menu_megjelenit();
        valasztott = kereses_menu_szam_beker();
        kepernyo_torol();
        switch (valasztott) {
            case 2:
                hash_tabla_lancszem_torol(h, nev);
                uj_szuletesnap(h);
                valasztott = 1;
                break;

            case 3:
                hash_tabla_lancszem_torol(h, nev);
                printf("Szuletesnap sikeresen eltavolitva.");
                varakozas_enterre();
                valasztott = 1;
                break;

            case 4:
                hash_tabla_lancszem_kiir(h, nev);
                varakozas_enterre();
                break;

            default:
                break;
        }
    }
}