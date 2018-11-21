/*
Kod zosta� napisany w brzydki spos�b, ka�da zawarto�� "if" z menu powinna by� w osobnej funkcji. Wieczorem Ci to poprawi�.

W opicji wyszukiwania brakuje wypisywanie ca�ej linii.

Kod zadzia�a chyba popawnie tylko na Windowsie ze wzgl�du na local files i polskie znaki

Stara�em si� komentowa� ka�d� lini�, je�li nie ma komentarza oznacza to, �e uzna�em co� za truizm, jak czego� nie rozumiesz pytaj na fb.

Jak dasz kod z zaj�� to mog� go gdzie� wcisn�� tutaj, przerobi� ten program aby pasowa�. Teraz jest to prosta aplikacja terminalowa kt�ra spe�nia podstawowe rzeczy o jakich mi pisa�a�
> plik tekstowy
> dodawanie do bazy danych
> szukanie w bazie danych
> wypisuje plik tekstowy
> ma jakie� tam proste menu
> ma zap�tlone menu z opcj� wyj�cia
> po ka�dej operacji zapisuje zmiany w pliku w celu nie utracenia czego� gdy zamiast wyboru kliknie kto� "x"
> nie zaimplementowa�em na razie usuwania wybranej linii
> dopisa�em wypisywanie informacji o wielko�ci pliku, dopisz� tam jeszcze ilo�� linii w pliku i inne pierdo�y jakie mi wpadn� do g�osy

Przepraszam, �e bez pytania Ciebie zrobi�em chyba cz�� twojego projektu ale nudzi mi si� i nie mam co robi� XD

Osobi�cie u�ywam Visual Studio do programowania, jak masz jakie� problemy z kompilowaniem/wy�wietlaniem/edytowaniem u siebie daj zna� to naprawi�

Adrian~
*/

#include <iostream> // Standardowa biblioteka we/wy
#include <locale.h> // Potrzebna do polskich znak�w
#include <fstream> // Potrzebna do operacji na plikach txt
#include <string> // Operacje na ci�gach znak�w

using namespace std;

int main() {
	setlocale(LC_CTYPE, "Polish"); // Dodanie polskich znak�w, nie mam pewno�ci ale dzia�a chyba tylko na Windowsie

	int user_choice; // Tworzenie zmiennych: user_choice -> liczba pobrana od u�ytkownika w celu wybrania opcji
	bool is_running = true; // Aplikacja zap�tla si� p�ki kto� nie wybierze opcji odpowiedzialnej za zmian� bool na false
	  
	// Powitanie
	cout << "Witaj! Wybierz jedn� z opcji!" << endl;

	// Proste menu wyboru
	while (is_running == true) { //Aplikcja dzia�a ci�gle a� warunek jest spe�niony

		// Opcje wyboru
		cout << "\n1 - Dodaj do bazy danych" << endl;
		cout << "2 - Usu� z bazy danych" << endl;
		cout << "3 - Wypisz baz� danych" << endl;
		cout << "4 - Wyszukaj w bazie danych" << endl;
		cout << "5 - Informacje o pliku bazy danych" << endl;
		cout << "0 - Wyjd� z aplikacji\n" << endl;

		// Pobranie od u�ytkownika zmiennej
		cin >> user_choice;
		cin.get();

		if (user_choice == 1) {

			// Otwarcie pliku tekstowego
			ofstream bazadanych;
			bazadanych.open("database.txt", ios::app); // W razie braku pliku, tworzy go w katalogu domowym programu

			// Ta baza danych zawiera informacj� o imieniu, nazwisku, roku urodzenia ludzi 
			// imi�, nazwisko to string, rok urodzenia to int,  
			string imie,
				nazwisko;
			int rok_urodzenia;

			// Pobieranie danych, przekazanie do zmiennych
			cout << "Dodaj dane" << endl;
			cout << "Podaj imi�: " << endl;
			cin >> imie;

			cout << "Podaj nazwisko: " << endl;
			//cin.getline(cin, nazwisko);
			cin >> nazwisko;

			cout << "Podaj rok urodzenia: " << endl;
			cin >> rok_urodzenia;
			cin.get();

			// Przekazanie zmiennych do pliku tekstowego
			bazadanych << imie << " " << nazwisko << " " << rok_urodzenia << "\n";

			cout << "Do bazy danych zosta�y dodane nast�puj�ce warto�ci: " << imie << " " << nazwisko << " " << rok_urodzenia << endl;
			bazadanych.close();
		}
		else if (user_choice == 2) {
			cout << "Usu� dane" << endl;
		}
		else if (user_choice == 3) {
			cout << "Wypisuj� baz� danych...\n" << endl;

			string line; // aktualnie iterowana linia

			// Otwarcie pliku tekstowego
			ifstream bazadanych("database.txt");

			if (bazadanych.is_open()) {  // je�li plik jest otwarty...
				while (getline(bazadanych, line)) { // dop�ki znajduj� si� linie w pliku bazadanych...
					cout << line << "\n"; // wypisz lini�
				}
			}

			bazadanych.close(); // zamknij plik
		}
		else if (user_choice == 4) {
			// Otwarcie pliku tekstowego
			ifstream bazadanych("database.txt");

			cout << "Wyszukaj w bazie danych" << endl;
			string szukane, linia; // inicjalizacja zmiennych, szukanie oraz linia w kt�rej pojawia si� wyra�enie
			int currLine = 0; // Aktualnie analizowana linia

			cout << "Czego szukasz? " << endl;
			cin >> szukane;

			while (getline(bazadanych, linia)) { // dop�ki znajduj� si� linie w pliku...
				currLine++; // zwi�ksz aktualn� lini� o jeden
				if (linia.find(szukane, 0) != string::npos) { // je�li ilo�� wyszuka� nie jest r�wna ilo�ci warto�ci maksymalnej mo�liwej warto�ci dla rozmiaru linii 
					// aka w danej linii nie istnieje pasuj�cy string do naszego szukanego wzorca
					// ad1: npos to sta�a warto�� elementu statycznego o najwi�kszej mo�liwej warto�ci dla elementu typu size_t.
					cout << "Znalaz�em: " << szukane << ", w linii numer: " << currLine << endl; // wypisz co znalaz�e� i w kt�rej linii
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

			cout << "Rozmiar pliku bazy danych: " << (end-begin) << " bajt�w.\n" << endl;

		}
		else if (user_choice == 0) {
			is_running = false; // Zmiana warto�ci bool odpowiedzialnej za uruchomienie programu

			// Po�egnanie z u�ytkownikiem, zamkni�cie okna
			cout << "\nDo zobaczenia!" << endl;
			cout << "Naci�nij klawisz [Enter] aby zamkn�� okno...\n" << endl;

		}
	}

	//bazadanych.close(); //Zamkni�cie pliku tekstowego

	cin.get();
	return 0;
}