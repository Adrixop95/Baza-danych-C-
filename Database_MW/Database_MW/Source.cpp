/*
Kod zosta³ napisany w brzydki sposób, ka¿da zawartoœæ "if" z menu powinna byæ w osobnej funkcji. Wieczorem Ci to poprawiê.

W opicji wyszukiwania brakuje wypisywanie ca³ej linii.

Kod zadzia³a chyba popawnie tylko na Windowsie ze wzglêdu na local files i polskie znaki

Stara³em siê komentowaæ ka¿d¹ liniê, jeœli nie ma komentarza oznacza to, ¿e uzna³em coœ za truizm, jak czegoœ nie rozumiesz pytaj na fb.

Jak dasz kod z zajêæ to mogê go gdzieœ wcisn¹æ tutaj, przerobiæ ten program aby pasowa³. Teraz jest to prosta aplikacja terminalowa która spe³nia podstawowe rzeczy o jakich mi pisa³aœ
> plik tekstowy
> dodawanie do bazy danych
> szukanie w bazie danych
> wypisuje plik tekstowy
> ma jakieœ tam proste menu
> ma zapêtlone menu z opcj¹ wyjœcia
> po ka¿dej operacji zapisuje zmiany w pliku w celu nie utracenia czegoœ gdy zamiast wyboru kliknie ktoœ "x"
> nie zaimplementowa³em na razie usuwania wybranej linii
> dopisa³em wypisywanie informacji o wielkoœci pliku, dopiszê tam jeszcze iloœæ linii w pliku i inne pierdo³y jakie mi wpadn¹ do g³osy

Przepraszam, ¿e bez pytania Ciebie zrobi³em chyba czêœæ twojego projektu ale nudzi mi siê i nie mam co robiæ XD

Osobiœcie u¿ywam Visual Studio do programowania, jak masz jakieœ problemy z kompilowaniem/wyœwietlaniem/edytowaniem u siebie daj znaæ to naprawiê

Adrian~
*/

#include <iostream> // Standardowa biblioteka we/wy
#include <locale.h> // Potrzebna do polskich znaków
#include <fstream> // Potrzebna do operacji na plikach txt
#include <string> // Operacje na ci¹gach znaków

using namespace std;

int main() {
	setlocale(LC_CTYPE, "Polish"); // Dodanie polskich znaków, nie mam pewnoœci ale dzia³a chyba tylko na Windowsie

	int user_choice; // Tworzenie zmiennych: user_choice -> liczba pobrana od u¿ytkownika w celu wybrania opcji
	bool is_running = true; // Aplikacja zapêtla siê póki ktoœ nie wybierze opcji odpowiedzialnej za zmianê bool na false
	  
	// Powitanie
	cout << "Witaj! Wybierz jedn¹ z opcji!" << endl;

	// Proste menu wyboru
	while (is_running == true) { //Aplikcja dzia³a ci¹gle a¿ warunek jest spe³niony

		// Opcje wyboru
		cout << "\n1 - Dodaj do bazy danych" << endl;
		cout << "2 - Usuñ z bazy danych" << endl;
		cout << "3 - Wypisz bazê danych" << endl;
		cout << "4 - Wyszukaj w bazie danych" << endl;
		cout << "5 - Informacje o pliku bazy danych" << endl;
		cout << "0 - WyjdŸ z aplikacji\n" << endl;

		// Pobranie od u¿ytkownika zmiennej
		cin >> user_choice;
		cin.get();

		if (user_choice == 1) {

			// Otwarcie pliku tekstowego
			ofstream bazadanych;
			bazadanych.open("database.txt", ios::app); // W razie braku pliku, tworzy go w katalogu domowym programu

			// Ta baza danych zawiera informacjê o imieniu, nazwisku, roku urodzenia ludzi 
			// imiê, nazwisko to string, rok urodzenia to int,  
			string imie,
				nazwisko;
			int rok_urodzenia;

			// Pobieranie danych, przekazanie do zmiennych
			cout << "Dodaj dane" << endl;
			cout << "Podaj imiê: " << endl;
			cin >> imie;

			cout << "Podaj nazwisko: " << endl;
			//cin.getline(cin, nazwisko);
			cin >> nazwisko;

			cout << "Podaj rok urodzenia: " << endl;
			cin >> rok_urodzenia;
			cin.get();

			// Przekazanie zmiennych do pliku tekstowego
			bazadanych << imie << " " << nazwisko << " " << rok_urodzenia << "\n";

			cout << "Do bazy danych zosta³y dodane nastêpuj¹ce wartoœci: " << imie << " " << nazwisko << " " << rok_urodzenia << endl;
			bazadanych.close();
		}
		else if (user_choice == 2) {
			cout << "Usuñ dane" << endl;
		}
		else if (user_choice == 3) {
			cout << "Wypisujê bazê danych...\n" << endl;

			string line; // aktualnie iterowana linia

			// Otwarcie pliku tekstowego
			ifstream bazadanych("database.txt");

			if (bazadanych.is_open()) {  // jeœli plik jest otwarty...
				while (getline(bazadanych, line)) { // dopóki znajduj¹ siê linie w pliku bazadanych...
					cout << line << "\n"; // wypisz liniê
				}
			}

			bazadanych.close(); // zamknij plik
		}
		else if (user_choice == 4) {
			// Otwarcie pliku tekstowego
			ifstream bazadanych("database.txt");

			cout << "Wyszukaj w bazie danych" << endl;
			string szukane, linia; // inicjalizacja zmiennych, szukanie oraz linia w której pojawia siê wyra¿enie
			int currLine = 0; // Aktualnie analizowana linia

			cout << "Czego szukasz? " << endl;
			cin >> szukane;

			while (getline(bazadanych, linia)) { // dopóki znajduj¹ siê linie w pliku...
				currLine++; // zwiêksz aktualn¹ liniê o jeden
				if (linia.find(szukane, 0) != string::npos) { // jeœli iloœæ wyszukañ nie jest równa iloœci wartoœci maksymalnej mo¿liwej wartoœci dla rozmiaru linii 
					// aka w danej linii nie istnieje pasuj¹cy string do naszego szukanego wzorca
					// ad1: npos to sta³a wartoœæ elementu statycznego o najwiêkszej mo¿liwej wartoœci dla elementu typu size_t.
					cout << "Znalaz³em: " << szukane << ", w linii numer: " << currLine << endl; // wypisz co znalaz³eœ i w której linii
				}
			}

			bazadanych.close(); // zamknij plik
		}
		else if (user_choice == 5) {
			streampos begin, end;
			ifstream bazadanych("database.txt");

			begin = bazadanych.tellg();
			bazadanych.seekg(0, ios::end);
			end = bazadanych.tellg();

			bazadanych.close();

			cout << "Rozmiar pliku bazy danych: " << (end-begin) << " bajtów.\n" << endl;

		}
		else if (user_choice == 0) {
			is_running = false; // Zmiana wartoœci bool odpowiedzialnej za uruchomienie programu

			// Po¿egnanie z u¿ytkownikiem, zamkniêcie okna
			cout << "\nDo zobaczenia!" << endl;
			cout << "Naciœnij klawisz [Enter] aby zamkn¹æ okno...\n" << endl;

		}
	}

	//bazadanych.close(); //Zamkniêcie pliku tekstowego

	cin.get();
	return 0;
}