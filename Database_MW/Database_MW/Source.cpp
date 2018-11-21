#include <iostream> // Standardowa biblioteka we/wy
#include <locale.h> // Potrzebna do polskich znak�w
#include <fstream> // Potrzebna do operacji na plikach txt
#include <string> // Operacje na ci�gach znak�w

using namespace std;

int main() {
	setlocale(LC_CTYPE, "Polish"); // Dodanie polskich znak�w, nie mam pewno�ci ale dzia�a chyba tylko na Windowsie

	int user_choice; // Tworzenie zmiennych: user_choice -> liczba pobrana od u�ytkownika w celu wybrania opcji
	bool is_running = true; // Aplikacja zap�tla si� p�ki kto� nie wybierze opcji odpowiedzialnej za zmian� bool na false

	// Otwarcie pliku tekstowego
	ofstream bazadanych;
	bazadanych.open("database.txt", ios::app); // W razie braku pliku, tworzy go w katalogu domowym programu
	   
	// Proste menu wyboru
	while (is_running == true) { //Aplikcja dzia�a ci�gle a� warunek jest spe�niony

		// Powitanie oraz opcje wyboru
		cout << "Witaj! Wybierz jedn� z opcji!\n" << endl;
		cout << "1 - Dodaj do bazy danych" << endl;
		cout << "2 - Usu� z bazy danych" << endl;
		cout << "3 - Wypisz baz� danych" << endl;
		cout << "4 - Wyszukaj w bazie danych" << endl;
		cout << "5 - Informacje o pliku bazy danych" << endl;
		cout << "0 - Wyjd� z aplikacji\n" << endl;

		// Pobranie od u�ytkownika zmiennej
		cin >> user_choice;
		cin.get();

		if (user_choice == 1) {
			// Ta baza danych zawiera informacj� o imieniu, nazwisku, roku urodzenia ludzi 
			// imi�, nazwisko to string, rok urodzenia to int,  
			string imie,
				nazwisko;
			int rok_urodzenia;

			// Pobieranie danych, przekazanie do zmiennych
			cout << "Dodaj dane" << endl;
			cout << "Podaj imi�: " << endl;
			getline(cin, imie);

			cout << "Podaj nazwisko: " << endl;
			getline(cin, nazwisko);

			cout << "Podaj rok urodzenia: " << endl;
			cin >> rok_urodzenia;
			cin.get();

			// Przekazanie zmiennych do pliku tekstowego
			bazadanych << imie << " " << nazwisko << " " << rok_urodzenia << "\n";

			cout << "Do bazy danych zosta�y dodane nast�puj�ce warto�ci: " << imie << " " << nazwisko << " " << rok_urodzenia << endl;
		}
		else if (user_choice == 2) {
			cout << "Usu� dane" << endl;
		}
		else if (user_choice == 3) {
			cout << "Wypisuj� baz� danych...\n" << endl;
		}
		else if (user_choice == 4) {
			cout << "Wyszukaj w bazie danych" << endl;
		}
		else if (user_choice == 5) {
			cout << "Rozmiar pliku bazy danych: " << endl;
		}
		else if (user_choice == 0) {
			is_running = false; // Zmiana warto�ci bool odpowiedzialnej za uruchomienie programu

			// Po�egnanie z u�ytkownikiem, zamkni�cie okna
			cout << "\nDo zobaczenia!" << endl;
			cout << "Naci�nij klawisz [Enter] aby zamkn�� okno...\n" << endl;

		}
	}

	bazadanych.close(); //Zamkni�cie pliku tekstowego

	cin.get();
	return 0;
}