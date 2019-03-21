#ifndef DEFINICJE_H
#define DEFINICJE_H


#define LINE_SIZE 400
#define ZERO '0'
#define DZIEWIEC '9'
#define PIERWSZA_NIEWIADOMA 'A'
#define OSTATNIA_NIEWIADOMA 'Z'
#define MAX_WSPOLCZYNNIK 100.0
#define DLUGOSC_WSPOLCZYNNIKA 3
#define N 7



//zawiera rodzaje bledow; OK oznacza brak bledu
enum bledy {OK, NIEPOPRAWNA_LICZBA, ZA_DUZO_KROPEK, BRAK_NIEWIADOMEJ, BLEDNE_WYRAZENIE, BLAD_WCZYTYWANIA_LICZBY, NIEPOPRAWNA_NIEWIADOMA, BRAK_LICZBY, NIEPOPRAWNY_ZNAK, BRAK_WYRAZENIA, LICZBA_SPOZA_ZEKRESU, NADLICZBOWE_WYRAZENIE, NIEPOPRAWNA_KOLEJNOSC, ZA_DLUGA_LINIA};

//zawiera rodzaj elementu jaki powinien nastapic jako nastepny aby wyrazenie bylo poprawne
enum czekam_na {CYFRA, CYFRA_KROPKA_LITERA, DRUGA_LICZBA, CYFRA_LITERA, NIC};

//zawiera rodzaj elementu jaki powinien nastapic jako nastepny aby wyrazenie bylo poprawne w przypadku wyrazu wolnego
enum czekam_na_wyraz_wolny {CYFRA_WW, CYFRA_KROPKA_WW, DRUGA_LICZBA_WW, CYFRA_KONIEC_WW};

//struktura zawierajaca rodzaj bledu oraz to w ktorym wyrazeniu on wystepuje; w przypadku wyrazu wolnego gdzie = -1
struct blad
{
	enum bledy nr_bledu;
	int gdzie;
};

void czysc_bufor();

//wczytuje liczbe z pierwszej linii pliku bedaca liczba rownan i zwraca ja
int wczytaj_liczbe();

//wypisuje informacje o programie
void pisz_informacje(char* nazwa_pliku);

void pisz_opcje();

int czytaj_opcje();

void pisz_uklad(int liczba_rownan, double** macierz, double* wyrazy_wolne);

//wypisuje rodzaj oraz gdzie jest blad
void pisz_strukture(struct blad x, int nr_linii);

//wczytuje cala linie do elementu w; linia nie moze byc dluzsza niz LINE_SIZE
void wczytaj(char* w, FILE *f);

//usuwa spacje z lancucha znakow
void usun_spacje(char* lancuch);

//przesowa p tak zeby nie wskazywalo na + ani na - , zwraca -1 jesli jest nieparzysta liczba -, innaczej zwraca 1
int usun_plus_minus(char* linia, int* p);

//konwertuje czesc lini (elementy nr p, p+1, p+2, ..., k-1) na liczbe i ja zwraca
double liczba(char* linia, int p, int k, int kropka);

//sprawdza czy wyrazenie zlozone z jednego elementu jest poprawne (jest poprawne gdy skalada sie tylko z niewiadomej)
enum bledy sprawdz_wyrazenie_jednoelementowe(char* linia, int indeks, char poprzednia_niewiadoma, char ostatnia_niewiadoma);

//sprawdza czy element na miejscu nr indeks jest oczekiwanym elementem (rodzaj oczekiwanego elementu znajduje się w 'nastepny')
enum bledy sprawdz_znak(char* linia, int indeks, enum czekam_na* nastepny);

//sprawdza poprawnosc wyrazenia
struct blad sprawdz_wyrazenie(char* linia, int p, int k, int nr_wyrazenia, int nr_linii, double** macierz, char* poprzedni, char ostatni);

//sprawdza poprawnosc wyrazenia znajdujacego sie po znaku =
enum bledy sprawdz_wyraz_wolny(char* linia, int* indeks, int nr_linii, double* wyrazy_wolne);

//sprawdza poprawnosc calej linii (rownania)
struct blad sprawdz_linie(char* linia, int nr_linii, double** macierz, double* wyrazy_wolne, int liczba_rownan);

double licz_wyznacznik(int n, double** macierz);

void rozwiaz_uklad(int liczba_rownan, double** macierz, double* wyrazy_wolne, FILE* nazwa_pliku);

#endif
