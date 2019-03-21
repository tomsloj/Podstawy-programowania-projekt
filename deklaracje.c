#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deklaracje.h"



void czysc_bufor()
{
	char c;
	while((c = getchar()) != '\n' && c != EOF)
		;
}

// -1 jesli liczba jest niepoprawna
int wczytaj_liczbe(FILE* f)
{
	char tmp[LINE_SIZE];
	fgets(tmp, LINE_SIZE, f);
	
	// usuwamy spacje z przodu
	int p = 0;
	int size = strlen(tmp);
	
	while(p < size && (tmp[p] == ' ' || tmp[p] == '\t'))
		++p;
	//usuwamy spacje z konca
	while(size > 0 && (tmp[size - 1] == ' ' || tmp[size - 1] =='\n' || tmp[size - 1] == '\t'))
		--size;
	int v = 1;
	long long liczba = 0;
	for(int i = size - 1; i >= p; --i)
	{
		if(tmp[i] < '0' || tmp[i] > '9')
		{
			printf("blad wczytywania liczby rownan\n");
			return -1;
		}
		liczba += v * (tmp[i] - '0');
		v *= 10; 
	}
	if(size - p > 3)
		return -1;
	return liczba;
	
}


void pisz_informacje(char* nazwa_pliku)
{
	printf("Ten program rozwiazuje uklad N rownan z N niewiadomymi\n");
	printf("W pliku o nazwie %s umiesc w pierwszej linii liczbe N od 1 do %d\n", nazwa_pliku, N);
	printf("oznaczajaca liczbe rownan i niewiadomych\n");
	printf("nastepne N linii powinno zawierac po jednym rownaniu\n");
	printf("nazwy niewiadomych rownania powinny byc kolejnymi\n");
	printf("literami alfabetu lacinskiego zaczynajac od 'A'\n");
}

void pisz_opcje()
{
	printf("wpisz w konsole:\n");
	printf("1 aby wyznaczyc rozwiazania rownania\n");
	printf("0 aby zakonczyc dzialanie programu\n");
}

int czytaj_opcje()
{
	char c = ' ';
	while(c == ' ' || c == '\t')
	{
		scanf("%c", &c);
	}
	if(c != '0' && c != '1')
	{
		if(c != '\n')
			czysc_bufor();
		printf("nalezy wpisac 1 lub 0\npodaj nr opcji:\n");
		return czytaj_opcje();
	}
	else
	{
		char tmp = ' ';
		while(tmp == ' ' || tmp == '\t')
		{
			scanf("%c", &tmp);
		}
		if(tmp != '\n')
		{
			czysc_bufor();
			printf("nalezy wpisac 1 lub 0\npodaj nr opcji:\n");
			return czytaj_opcje();
		}
	}
	return c - ZERO;
}
void pisz_uklad(int liczba_rownan, double** macierz, double* wyrazy_wolne)
{
	printf("uklad ma postac:\n");
	for(int i = 0; i < liczba_rownan; ++i)
	{
		if(macierz[i][0] == 1)
			printf("%c", PIERWSZA_NIEWIADOMA);
		else
		if(((int) macierz[i][0]) == macierz[i][0])
			printf("%.0lf%c", macierz[i][0], PIERWSZA_NIEWIADOMA);
		else
			printf("%.3lf%c", macierz[i][0], PIERWSZA_NIEWIADOMA);
		
		for(int j = 1; j < liczba_rownan; ++j)
		{
			if(macierz[i][j] >= 0)
				printf("+");
			
			if(macierz[i][j] == 1)
				printf("%c", PIERWSZA_NIEWIADOMA + j);
			else
			if(((int) macierz[i][j]) == macierz[i][j])
				printf("%.0lf%c", macierz[i][j], PIERWSZA_NIEWIADOMA+j);
			else
				printf("%.3lf%c", macierz[i][j], PIERWSZA_NIEWIADOMA+j);
			
		}
		if(((int) wyrazy_wolne[i]) == wyrazy_wolne[i])
			printf("=%.0lf\n", wyrazy_wolne[i]);
		else
			printf("=%.3lf\n", wyrazy_wolne[i]);
		
	}
}

void pisz_strukture(struct blad x, int nr_linii)
{
	printf("linia %d:\n", nr_linii);
	if(x.nr_bledu == OK)
	{
		printf("rownanie jest poprawne\n");
	}
	else
	{
		switch(x.nr_bledu)
		{
			case NIEPOPRAWNA_LICZBA:
				printf("NIEPOPRAWNA_LICZBA ");
				break;
			case ZA_DUZO_KROPEK:
				printf("ZA_DUZO_KROPEK ");
				break;
			case BRAK_NIEWIADOMEJ:
				printf("BRAK_NIEWIADOMEJ ");
				break;
			case BLEDNE_WYRAZENIE:
				printf("BLEDNE_WYRAZENIE ");
				break;
			case BLAD_WCZYTYWANIA_LICZBY:
				printf("BLAD_WCZYTYWANIA_LICZBY ");
				break;
			case NIEPOPRAWNA_NIEWIADOMA:
				printf("NIEPOPRAWNA_NIEWIADOMA ");
				break;
			case BRAK_LICZBY:
				printf("BRAK_LICZBY ");
				break;
			case NIEPOPRAWNY_ZNAK:
				printf("NIEPOPRAWNY_ZNAK ");
				break;
			case BRAK_WYRAZENIA:
				printf("BRAK_WYRAZENIA ");
				break;
			case LICZBA_SPOZA_ZEKRESU:
				printf("LICZBA_SPOZA_ZEKRESU ");
				break;
			case NADLICZBOWE_WYRAZENIE:
				printf("NADLICZBOWE_WYRAZENIE ");
				break;
			case NIEPOPRAWNA_KOLEJNOSC:
				printf("NIEPOPRAWNA_KOLEJNOSC ");
				break;
			default:
				printf("inny blad ");
				break;
		}
		if(x.gdzie == -1)
		{
			printf("w wyrazie wolnym\n");
		}
		else
		{
			printf("w wyrazeniu nr %d\n", x.gdzie + 1);
		}
	}
}

void wczytaj(char* w, FILE* f)
{
	fgets(w, LINE_SIZE, f);
}

void usun_spacje(char* lancuch)
{
	char tmp[LINE_SIZE];
	int i = 0;//indeks w lancuchu
	int j = 0;//indeks w tmp
	while(lancuch[i] != '\0')
	{
		if(lancuch[i] != ' ' && lancuch[i] != '\n' && lancuch[i] != EOF && lancuch[i] != '\t')
		{
			tmp[j] = lancuch[i];
			++i;
			++j;	
		}
		else
			++i;
	}
	tmp[j] = '\0';
	
	strcpy(lancuch, tmp);
}

int usun_plus_minus(char* linia, int* p)
{
	int mnoznik = 1;
	while(linia[*p] == '+' || linia[*p] == '-')
	{
		if(linia[*p] == '-')
			mnoznik *= -1;
		++(*p);
	}
	return mnoznik;
}

double liczba(char* linia, int p, int k, int kropka)
{	
	if(p == k)
		return 0.0;
	int koniec_calkowitej;
	int poczatek_niecalkowitej;
	double wynik = 0.0;
	if(kropka == -1)
	{
		koniec_calkowitej = k;
		poczatek_niecalkowitej = k;
	}
	else
	{
		koniec_calkowitej = kropka;
		poczatek_niecalkowitej = kropka + 1;
	}
	while(linia[p] == '0')
		++p;
		
	if(koniec_calkowitej - p > DLUGOSC_WSPOLCZYNNIKA)
		return MAX_WSPOLCZYNNIK + 1.0;
	
	double mnoznik = 1.0;

	for(int i = koniec_calkowitej - 1; i >= p; --i)
	{
		wynik += (linia[i]- '0') * mnoznik;
		mnoznik *= 10.0;
	}
	mnoznik = 0.1;
	for(int i = poczatek_niecalkowitej; i < k; ++i)
	{
		wynik += (linia[i]- '0') * mnoznik;
		mnoznik /= 10.0;
	}
	return wynik;
}

enum bledy sprawdz_wyrazenie_jednoelementowe(char* linia, int indeks, char poprzednia_niewiadoma, char ostatnia_niewiadoma)
{
	if(linia[indeks] > poprzednia_niewiadoma && linia[indeks] <= ostatnia_niewiadoma)
		return OK;
	else
	{
		if(linia[indeks] <= poprzednia_niewiadoma && linia[indeks] >='A')
			return NIEPOPRAWNA_KOLEJNOSC;
		else
		if(linia[indeks] >= ZERO && linia[indeks] <= DZIEWIEC)
			return BRAK_NIEWIADOMEJ;
		else
		if(linia[indeks] <= 'Z' && linia[indeks] > ostatnia_niewiadoma)
			return NIEPOPRAWNA_NIEWIADOMA;
		else
			return BLEDNE_WYRAZENIE;
	}
}


enum bledy sprawdz_znak(char* linia, int indeks, enum czekam_na* nastepny)
{
	enum bledy error = OK;
	if(*nastepny == CYFRA)
	{
		if(linia[indeks] >= ZERO && linia[indeks] <= DZIEWIEC)
		{
			error = OK;
			*nastepny = CYFRA_KROPKA_LITERA;
		}
		else
		if(linia[indeks] >= PIERWSZA_NIEWIADOMA && linia[indeks] <= OSTATNIA_NIEWIADOMA)
			error = BRAK_LICZBY;
		else
			error = BLAD_WCZYTYWANIA_LICZBY;
	}
	else
	if(*nastepny == CYFRA_KROPKA_LITERA)
	{
		if(linia[indeks] >= ZERO && linia[indeks] <= DZIEWIEC)
			error = OK;
		else
		if(linia[indeks] == '.')
		{
			error = OK;
			*nastepny = DRUGA_LICZBA;
		}
		else
		if(linia[indeks] >= PIERWSZA_NIEWIADOMA && linia[indeks] <= OSTATNIA_NIEWIADOMA)
		{
			error = OK;
			*nastepny = NIC;
		}
		else
			error = NIEPOPRAWNA_NIEWIADOMA;
	}
	else
	if(*nastepny == DRUGA_LICZBA)
	{
		if(linia[indeks] >= ZERO && linia[indeks] <= DZIEWIEC)
		{
			error = OK;
			*nastepny = CYFRA_LITERA;
		}
		else
		if(linia[indeks] >= PIERWSZA_NIEWIADOMA && linia[indeks] <= OSTATNIA_NIEWIADOMA)
		{
			error = NIEPOPRAWNA_LICZBA;
		}
		else
		if(linia[indeks] == '.')
			error = ZA_DUZO_KROPEK;
		else
			error = NIEPOPRAWNY_ZNAK;
	}
	else
	if(*nastepny == CYFRA_LITERA)
	{
		if(linia[indeks] >= ZERO && linia[indeks] <= DZIEWIEC)
		{
			error = OK;
		}
		else
		if(linia[indeks] >= PIERWSZA_NIEWIADOMA && linia[indeks] <= OSTATNIA_NIEWIADOMA)
		{
			error = OK;
			*nastepny = NIC;
		}
		else
		if(linia[indeks] == '.')
			error = ZA_DUZO_KROPEK;
		else
			error = NIEPOPRAWNY_ZNAK;
	}
	else
	if(*nastepny == NIC)
	{
		error = NIEPOPRAWNA_NIEWIADOMA;
	}
	return error;
} 

struct blad sprawdz_wyrazenie(char* linia, int p, int k, int nr_wyrazenia, int nr_linii, double** macierz, char* poprzedni, char ostatni)
{
	struct blad aktualny_blad;
	aktualny_blad.gdzie = nr_wyrazenia;	
	double wspolczynnik = 0.0; 
	int koniec_liczby;
	int kropka = -1;
	int poczatek_liczby = p;
	
	//printf("%d, %d\n", p , k);
	
	if(p == k)
	{
		aktualny_blad.nr_bledu = BRAK_WYRAZENIA;
		aktualny_blad.gdzie = nr_wyrazenia;  
	}
	
	if(p == k - 1)
	{
		aktualny_blad.nr_bledu = sprawdz_wyrazenie_jednoelementowe(linia, p, *poprzedni, ostatni);
		wspolczynnik = 1.0;
		if(aktualny_blad.nr_bledu == OK)
		{
			macierz[nr_linii][linia[k-1] - 'A'] = wspolczynnik;
			*poprzedni = linia[k-1];
		}
		return aktualny_blad;
	}

	enum czekam_na nastepny = CYFRA;
	
	while(p < k)
	{
		//pisz_czekam_na(nastepny);
		aktualny_blad.nr_bledu = sprawdz_znak(linia, p, &nastepny);
		
		if(aktualny_blad.nr_bledu != OK)
			return aktualny_blad;
		
		if(linia[p] == '.')
			kropka = p;
		if(nastepny == NIC)
			koniec_liczby = p;
		++p;
	}
	if(nastepny != NIC)
	{
		aktualny_blad.nr_bledu = BRAK_NIEWIADOMEJ;
		return aktualny_blad;
	}	
	
	wspolczynnik = liczba(linia, poczatek_liczby , koniec_liczby, kropka);
	if(wspolczynnik > MAX_WSPOLCZYNNIK || wspolczynnik < -MAX_WSPOLCZYNNIK)
	{
		aktualny_blad.nr_bledu = LICZBA_SPOZA_ZEKRESU;
		aktualny_blad.gdzie = nr_wyrazenia;
		return aktualny_blad;
	}
	if(linia[k-1] <= *poprzedni)
	{
		aktualny_blad.nr_bledu = NIEPOPRAWNA_KOLEJNOSC;
		aktualny_blad.gdzie = nr_wyrazenia;
		return aktualny_blad;
	}
	if(linia[k-1] > ostatni)
	{
		aktualny_blad.nr_bledu = NIEPOPRAWNA_NIEWIADOMA;
		aktualny_blad.gdzie = nr_wyrazenia;
		return aktualny_blad;
	}
	*poprzedni = linia[k-1];
	macierz[nr_linii][linia[k - 1] - 'A'] = wspolczynnik;
	
	return aktualny_blad;
}

enum bledy sprawdz_wyraz_wolny(char* linia, int* indeks, int nr_linii, double* wyrazy_wolne)
{
	enum bledy error;
	enum czekam_na_wyraz_wolny nastepny = CYFRA_WW;
	double wyraz_wolny;
	int kropka = -1;
	int p = *indeks;
	
	while(linia[*indeks] != '\0')
	{
		if(linia[*indeks] == '.')
			kropka = *indeks;
		
		if(nastepny == CYFRA_WW)
		{
			if(linia[*indeks] >= ZERO && linia[*indeks] <= DZIEWIEC)
			{
				error = OK;
				nastepny = CYFRA_KROPKA_WW;
			}
			else
			{
				error = BLAD_WCZYTYWANIA_LICZBY;
				return error;
			}
		}
		else
		if(nastepny == CYFRA_KROPKA_WW)
		{
			if(linia[*indeks] >= ZERO && linia[*indeks] <= DZIEWIEC)
				error = OK;
			else
			if(linia[*indeks] == '.')
			{
				error = OK;
				nastepny = DRUGA_LICZBA_WW;
			}
			else
			{
				error = NIEPOPRAWNY_ZNAK;
				return error;
			}
		}
		else
		if(nastepny == DRUGA_LICZBA_WW)
		{
			if(linia[*indeks] >= ZERO && linia[*indeks] <= DZIEWIEC)
			{
				error = OK;
				nastepny = CYFRA_KONIEC_WW;
			}
			else
			if(linia[*indeks] == '.')
			{
				error = ZA_DUZO_KROPEK;
				return error;
			}
			else
			{
				error = NIEPOPRAWNY_ZNAK;
				return error;
			}
		}
		else
		if(nastepny == CYFRA_KONIEC_WW)
		{
			if(linia[*indeks] >= ZERO && linia[*indeks] <= DZIEWIEC)
				error = OK;
			else
			if(linia[*indeks] == '.')
			{
				error = ZA_DUZO_KROPEK;
				return error;
			}
			else
			{
				error = NIEPOPRAWNY_ZNAK;
				return error;
			}

		}
		
		++*indeks;
	}
	if(nastepny == DRUGA_LICZBA_WW)
	{
		error = NIEPOPRAWNA_LICZBA;
		return error;
	}
	wyraz_wolny = liczba(linia, p, *indeks, kropka);
	if(wyraz_wolny > MAX_WSPOLCZYNNIK || wyraz_wolny < -MAX_WSPOLCZYNNIK)
	{
		error = LICZBA_SPOZA_ZEKRESU;
		return error;
	}
	wyrazy_wolne[nr_linii] = wyraz_wolny;
	return error;
}

struct blad sprawdz_linie(char* linia, int nr_linii, double** macierz, double* wyrazy_wolne, int liczba_rownan)
{
	usun_spacje(linia);
	int p = 0; //indeks poczatkowy
	int k; //indeks koncowy
	int nr_wyrazenia = 0; //nr aktualnie sprawawdzanego wyrazenia
	char niewiadoma = 'A';
	char poprzednia_niewiadoma = 0;
	char ostatnia_niewiadoma = 'A' + liczba_rownan - 1;
	struct blad aktualny_blad;
	aktualny_blad.nr_bledu = OK;
	aktualny_blad.gdzie = 0;
	int znak;
	k = p;
	
	int dlugosc_linii = strlen(linia);
	while(k < dlugosc_linii && linia[k] != '\0' && linia[k] != EOF && linia[k] != '\n')
	{
		if(linia[k] != '=')
		{
			znak = usun_plus_minus(linia, &k);
			p = k;
			if(nr_wyrazenia >= liczba_rownan)
			{
				aktualny_blad.nr_bledu = NADLICZBOWE_WYRAZENIE;
				aktualny_blad.gdzie = nr_wyrazenia;
			}
			while(linia[k] != '+' && linia[k] != '-' && linia[k] != '=' && linia[k] != '\0' && linia[k] != EOF && linia[k] != '\n')
				++k;
			aktualny_blad = sprawdz_wyrazenie(linia, p, k, nr_wyrazenia, nr_linii, macierz, &poprzednia_niewiadoma, ostatnia_niewiadoma);
			
			if(aktualny_blad.nr_bledu != OK)
				return aktualny_blad;
			
			niewiadoma = poprzednia_niewiadoma;
			macierz[nr_linii][niewiadoma - 'A'] *= znak;
			++niewiadoma;
			p=k;
		}
		else
		{
			if(nr_wyrazenia == 0)
			{
				aktualny_blad.nr_bledu = BRAK_WYRAZENIA;
				aktualny_blad.gdzie = 0;
				return aktualny_blad;
			}
			enum bledy wyraz_wolny_blad;
			++k;
			znak = usun_plus_minus(linia, &k);
			if(linia[k] == '\0' || linia[k] == '\n')
			{
				aktualny_blad.nr_bledu = BRAK_LICZBY;
				aktualny_blad.gdzie = -1;
				return aktualny_blad;
			}
			wyraz_wolny_blad = sprawdz_wyraz_wolny(linia, &k, nr_linii, wyrazy_wolne);
			wyrazy_wolne[nr_linii] *= znak;
			aktualny_blad.nr_bledu = wyraz_wolny_blad;
			aktualny_blad.gdzie = -1;
			if(aktualny_blad.nr_bledu != OK)
			{
				k = dlugosc_linii;
			}
		}

		++nr_wyrazenia;
	}
	
	if(nr_wyrazenia == 0)
	{
		aktualny_blad.nr_bledu = BRAK_WYRAZENIA;
		aktualny_blad.gdzie = -1;
	}
	
	return aktualny_blad;
}


/*
struct blad sprawdz_linie(char* linia, int nr_linii, double** macierz, double* wyrazy_wolne, int liczba_rownan)
{
	usun_spacje(linia);
	int p = 0; //indeks poczatkowy
	int k; //indeks koncowy
	int nr_wyrazenia = 0; //nr aktualnie sprawawdzanego wyrazenia
	char niewiadoma = 'A';
	char poprzednia_niewiadoma = 0;
	char ostatnia_niewiadoma = 'A' + liczba_rownan - 1;
	struct blad aktualny_blad;
	aktualny_blad.nr_bledu = OK;
	aktualny_blad.gdzie = 0;
	int znak = usun_plus_minus(linia, &p);
	k = p;
	
	int dlugosc_linii = strlen(linia);
	while(k < dlugosc_linii && linia[k] != '\0' && linia[k] != EOF && linia[k] != '\n')
	{
		if(linia[k] == '+' || linia[k] == '-' || linia[k] == '=')
		{
			printf("%d, %d, %d\n", p, k, nr_linii);
			if(nr_wyrazenia >= liczba_rownan)
			{
				aktualny_blad.nr_bledu = NADLICZBOWE_WYRAZENIE;
				aktualny_blad.gdzie = nr_wyrazenia;
			}
			aktualny_blad = sprawdz_wyrazenie(linia, p, k, nr_wyrazenia, nr_linii, macierz, &poprzednia_niewiadoma, ostatnia_niewiadoma);
			
			if(p == k-1)
				++nr_wyrazenia;
			
			if(aktualny_blad.nr_bledu != OK)
				return aktualny_blad;
			
			niewiadoma = poprzednia_niewiadoma;
			macierz[nr_linii][niewiadoma - 'A'] *= znak;
			
			if(linia[k] == '+' || linia[k] == '-')
			{
				znak = usun_plus_minus(linia, &k);
			}
			else
			{
				if(nr_wyrazenia == 0)
				{
					aktualny_blad.nr_bledu = BRAK_WYRAZENIA;
					aktualny_blad.gdzie = 0;
					return aktualny_blad;
				}
				enum bledy wyraz_wolny_blad;
				++k;
				znak = usun_plus_minus(linia, &k);
				if(linia[k] == '\0')
				{
					aktualny_blad.nr_bledu = BRAK_LICZBY;
					aktualny_blad.gdzie = -1;
					return aktualny_blad;
				}
				wyraz_wolny_blad = sprawdz_wyraz_wolny(linia, &k, nr_linii, wyrazy_wolne);
				wyrazy_wolne[nr_linii] *= znak;
				aktualny_blad.nr_bledu = wyraz_wolny_blad;
				aktualny_blad.gdzie = -1;
			}
			if(p != k-1)
				++nr_wyrazenia;
			++niewiadoma;
			p=k;
		}
		++k;
	}
	if(nr_wyrazenia == 0)
	{
		aktualny_blad.nr_bledu = BRAK_WYRAZENIA;
		aktualny_blad.gdzie = -1;
	}
	
	return aktualny_blad;
}
*/

//oblicza wartosc wyznacznika metoda Laplace'a w sposob rekurencyjny
double licz_wyznacznik(int n, double** macierz)
{
    //jezeli n == 2 wtedy oblicz wyznacznik wzorem
    if(n == 2)
    {
        return macierz[0][0]*macierz[1][1]-macierz[0][1]*macierz[1][0];
    }

    //jezeli n == 1 wartosc wyznacznika jest rowna jedynemu elementowi macierzy
    if(n == 1)
        return macierz[0][0];

    //jezeli n == 0 zwraca 0
    if(n == 0)
        return 0;
	
    double** tmp_macierz = NULL; //wskaznik wskaznikow ktory przechowuje macierze do kolejnych wywolan rekurencji
	
    //alokujemy pamiec na macierz o wymiarze n-1 x n-1
    tmp_macierz = (double**) malloc((n - 1) * sizeof( double* ) );
    for(int i = 0; i < n-1; ++i)
        tmp_macierz[i]= (double*) calloc( (n - 1), sizeof(double) );
        
    double wynik = 0.0; //zmienna do zapisania wartosci wyznacznika
    
    double minus = 1.0; //zmienna przyjmujaca wartosc 1.0 gdy suma indeksow
    //usunietego wiersza i usunietej kolumny jest parzysta
    //innaczej przyjmuje wartosc -1.0

    //wypelnianie macierzy o wymiarach n-1 x n-1
    //usunieta kolumna jest pierwsza kolumna
    //usunietym wierszem jest wiersz o indeksie n-1
    for(int i = 0; i < n-1; ++i)
    {
        for(int j = 0; j < n-1; ++j)
        {
         	double t = macierz[i][j+1];
            tmp_macierz[i][j] = t;
        }
    }
    
    //wyliczanie wartości mniejszej macierzy i usunięcie kolejnej kolumny
    //wierszem usunietym jest zawsze wiersz ostatni czyli o indeksie n-1
	
    for(int i = 0; i < n; ++i)
    {
        //gdy suma indeksow usunietego wiersza i usunietej kolumny jest parzysta
        //wtedy zmienna minus przyjmuje wartosc 1.0
   	    if( ( n + i + 1 ) % 2 == 0)
            minus = 1.0;
        //innaczej przyjmuje wartosc -1.0
        else
            minus = -1.0;
        /*
        zwiekszamy wynik o iloczyn
        ->zmiennej minus czyli -1 podniesione do potegi bedacej suma usunietego wiersza i usunietej kolumny
        ->elementu wspolnego usunietego wiersza i usunietej kolumny
        ->wartosci macierzy z usunieta kolumna i usunietym wierszem
        */      
    	wynik += minus * macierz[n-1][i] * licz_wyznacznik(n-1, tmp_macierz);
      
      	if(i != n - 1)
      	{
		    //nadpisanie kolejnej kolumny
		    //i-ta kolumne macierzy pomocniczej zastepujemy usunieta kolumna
		    for(int j = 0; j < n-1; ++j)
		    {
		    	double t = macierz[j][i];
		        tmp_macierz[j][i] = t;
		    }
		}
    }
    for(int i = 0; i < n-1; ++i)
    {
        free( tmp_macierz[i] ); //zwolnienie pamieci
	} 
    free( tmp_macierz );
    
    return wynik;
 
}

void rozwiaz_uklad(int liczba_rownan, double** macierz, double* wyrazy_wolne, FILE* file)
{
	double wyznacznik_glowny = licz_wyznacznik(liczba_rownan, macierz);
	fprintf(file, "wyznacznik glowny: %lf\n", wyznacznik_glowny);
	fprintf(file, "kolejne wyznaczniki\n");
	double* tmp_kolumna = (double*) malloc(liczba_rownan * sizeof(double));
	double* wyznacznik = (double*) malloc(liczba_rownan * sizeof(double));
	int ile_wyznacznikow_zerowych;
	
	for(int i = 0; i < liczba_rownan; ++i)
	{
		//zapisujemy i-ta kolumne do tmp_kolumna i i-ta kolumne zastepujemy wyrazami wolnymi
		for(int j = 0; j < liczba_rownan; ++j)
		{
			tmp_kolumna[j] = macierz[j][i];
			macierz[j][i] = wyrazy_wolne[j];
		}
		
		wyznacznik[i] = licz_wyznacznik(liczba_rownan, macierz);
		if(wyznacznik[i] == 0)
			++ile_wyznacznikow_zerowych;
		fprintf(file, "wyznacznik z wyrazami wolnymi zamiast kolumny %c: %lf\n", 'A'+ i, wyznacznik[i]);
		
		//wstawiamy i-ta kolumne na swoje miejsce
		for(int j = 0; j < liczba_rownan; ++j)
		{
			macierz[j][i] = tmp_kolumna[j];
		}
	}
	
	//wypisanie rozwiazan ukladu rownan
	if(wyznacznik_glowny == 0)
	{
		if(ile_wyznacznikow_zerowych == liczba_rownan)
		{
			fprintf(file, "\nuklad jest nieoznaczony - ma nieskonczenie wiele rozwiazan\n");
		}
		else
		{
			fprintf(file, "\nuklad jest sprzeczny - nie ma rozwiazan\n");
		}
	}
	else
	{
		fprintf(file, "\nrozwiazaniami tego ukladu sa:\n");
		for(int i = 0; i < liczba_rownan; ++i)
		{
			fprintf(file, "%c = %lf\n", 'A' + i, wyznacznik[i] / wyznacznik_glowny);
		}
	}
	
	free(tmp_kolumna);
	free(wyznacznik);
	
}

