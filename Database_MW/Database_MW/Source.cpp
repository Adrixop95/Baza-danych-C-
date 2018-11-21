#include <iostream> // Standardowa biblioteka we/wy
#include <locale.h> // Potrzebna do polskich znaków
#include <fstream> // Potrzebna do operacji na plikach txt
#include <string> // Operacje na ci¹gach znaków

using namespace std;

int main() {
	setlocale(LC_CTYPE, "Polish"); // Dodanie polskich znaków, nie mam pewnoœci ale dzia³a chyba tylko na Windowsie

	int user_choice; // Tworzenie zmiennych: user_choice -> liczba pobrana od u¿ytkownika w celu wybrania opcji
	bool is_running = true; // Aplikacja zapêtla siê póki ktoœ nie wybierze opcji odpowiedzialnej za zmianê bool na false

	// Otwarcie pliku tekstowego
	ofstream bazadanych;
	bazadanych.open("database.txt", ios::app); // W razie braku pliku, tworzy go w katalogu domowym programu
	   
	// Proste menu wyboru
	while (is_running == true) { //Aplikcja dzia³a ci¹gle a¿ warunek jest spe³niony

		// Powitanie oraz opcje wyboru
		cout << "Witaj! Wybierz jedn¹ z opcji!\n" << endl;
		cout << "1 - Dodaj do bazy danych" << endl;
		cout << "2 - Usuñ z bazy danych" << endl;
		cout << "3 - Wypisz bazê danych" << endl;
		cout << "4 - Wyszukaj w bazie danych" << endl;
		cout << "5 - Informacje o pliku bazy danych" << endl;
		cout << "0 - WyjdŸ z aplikacji\n" << endl;

		// Pobranie od u¿ytkownika zmiennej
		cin >> user_choice;
		cin.get();

		if (user_choice == 1) {
			// Ta baza danych zawiera informacjê o imieniu, nazwisku, roku urodzenia ludzi 
			// imiê, nazwisko to string, rok urodzenia to int,  
			string imie,
				nazwisko;
			int rok_urodzenia;

			// Pobieranie danych, przekazanie do zmiennych
			cout << "Dodaj dane" << endl;
			cout << "Podaj imiê: " << endl;
			getline(cin, imie);

			cout << "Podaj nazwisko: " << endl;
			getline(cin, nazwisko);

			cout << "Podaj rok urodzenia: " << endl;
			cin >> rok_urodzenia;
			cin.get();

			// Przekazanie zmiennych do pliku tekstowego
			bazadanych << imie << " " << nazwisko << " " << rok_urodzenia << "\n";

			cout << "Do bazy danych zosta³y dodane nastêpuj¹ce wartoœci: " << imie << " " << nazwisko << " " << rok_urodzenia << endl;
		}
		else if (user_choice == 2) {
			cout << "Usuñ dane" << endl;
		}
		else if (user_choice == 3) {
			cout << "Wypisujê bazê danych...\n" << endl;
		}
		else if (user_choice == 4) {
			cout << "Wyszukaj w bazie danych" << endl;
		}
		else if (user_choice == 5) {
			cout << "Rozmiar pliku bazy danych: " << endl;
		}
		else if (user_choice == 0) {
			is_running = false; // Zmiana wartoœci bool odpowiedzialnej za uruchomienie programu

			// Po¿egnanie z u¿ytkownikiem, zamkniêcie okna
			cout << "\nDo zobaczenia!" << endl;
			cout << "Naciœnij klawisz [Enter] aby zamkn¹æ okno...\n" << endl;

		}
	}

	bazadanych.close(); //Zamkniêcie pliku tekstowego

	cin.get();
	return 0;
}