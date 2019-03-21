#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deklaracje.h"

int main( int argc, char **argv )
{
	//czy dołączono 1 plik
	if(argc != 2)
	{
		printf("niepoprawna liczba argumentow wywolania programu;\nnalezy podac 1 argument\n");
		return 0;
	}
	pisz_informacje(argv[1]);
	
	int opcja = 1;
	char nazwa_pliku[LINE_SIZE];
	pisz_opcje();
	opcja = czytaj_opcje();
	
	//dopóki nie wybierzemy opcji 0
	while(opcja != 0)
	{
		FILE *file = fopen(argv[1], "r");
		if(file == NULL)
		{
			printf("nie udalo sie otworzyc pliku %s", argv[1]);
			return 0;
		}
		int liczba_rownan = wczytaj_liczbe(file);
		//czy wczytano liczbę od 1 do N
		if(liczba_rownan > N || liczba_rownan < 1)
		{
			printf("w pierwszej linii pliku musi znajdowac sie\n");
			printf("liczba calkowita z zakresu od 1 do %d\n", N);
			fclose(file);
			pisz_opcje();
			opcja = czytaj_opcje();
			continue;
		}
		
		//alokacja pamięci
		double** macierz;
		macierz = (double**) malloc(liczba_rownan * sizeof( double* ) );
		for(int i = 0; i < liczba_rownan; ++i)
		    macierz[i]= (double*) calloc(liczba_rownan, sizeof(double) );
		double* wyrazy_wolne;
		wyrazy_wolne = (double*) calloc(liczba_rownan, sizeof (double));
		
		
		
		struct blad czy_blad;
		char linia[LINE_SIZE];
		
		//wczytanie z pliku ukladu rownan i sprawdzenie jego poprawnosci
		for(int i = 0; i < liczba_rownan; ++i)
		{
			wczytaj(linia, file);
			czy_blad = sprawdz_linie(linia, i, macierz, wyrazy_wolne, liczba_rownan);
			if(czy_blad.nr_bledu != OK)
			{
				pisz_strukture(czy_blad, i+1);
				break;
			}
			//pisz_uklad(liczba_rownan, macierz, wyrazy_wolne);
		}
		
		//jesli nie wykryto bledu
		if(czy_blad.nr_bledu == OK)
		{
			pisz_uklad(liczba_rownan, macierz, wyrazy_wolne);
			printf("podaj nazwe pliku w którym ma byc zapisane rozwiazanie\n");
			printf("ukladu rownan(plik nie moze zawierac spacji - jesli pojawi sie\nwiecej niz jedna nazwa uzyta zostanie tylko pierwsza):\n");
			//wczytujemy plik w ktorym ma byc zapisane rozwiazanie
			scanf("%s", nazwa_pliku);
			czysc_bufor();
			FILE * plik_z_rozwiazaniem = fopen(nazwa_pliku, "w");
			if(plik_z_rozwiazaniem == NULL)
			{
				printf("nie udalo sie utworzyc pliku %s i zapiac rozwiazania\n", nazwa_pliku);
			}
			else
			{
				//rozwiazujemy uklad rownan
				rozwiaz_uklad(liczba_rownan, macierz, wyrazy_wolne, plik_z_rozwiazaniem);
				printf("rozwiazanie ukladu rownan znajduje sie w pliku %s\n", nazwa_pliku);
				fclose(plik_z_rozwiazaniem);
			}
		}
		//zwalnianie pamici i zamykanie pliku
		for(int i = 0; i < liczba_rownan; ++i)
		{
        	free(macierz[i]);
        }
    	free(macierz);
    	free(wyrazy_wolne);
		fclose(file);
		pisz_opcje();
		opcja = czytaj_opcje();
	}

}
