/*

Dalej nie jest to najlepszy program. Nie posiada on �adnych wyj�tk�w dla wpisania przez u�ytkownika znaku innego ni� dany typ
Ca�o�� powinna zosta� rozbita na mniejsze pliki
Nie czy�ci�em kodu, je�li s� w nim jakie� pozosta�o�ci, niepotrzebne komentarze, niepotrzebne definicje to przepraszam.

W razie problemu ze zrozumieniem czego� pytaj �mia�o.

Funkcjonalno��: 
> Odczyt/zapis do pliku tekstowego
> Pobieranie od u�ytkownika danych
> Usunie danych u�ytkownika
> Usunie bazy danych
> Wypisanie na ekranie bazy danych
> Wy�wietlenie informacji o pliku bazy danych
> Wyszukiwanie w bazie danych

Adrian~
*/

#include <iostream> // Standardowa biblioteka we/wy
#include <locale.h> // Potrzebna do polskich znak�w
#include <fstream> // Potrzebna do operacji na plikach txt
#include <string> // Operacje na ci�gach znak�w

using namespace std;

void add_user(ofstream& bazadanych) { // Funkcja odpowiada za dodanie u�ytkownika
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
	cin >> nazwisko;

	cout << "Podaj rok urodzenia: " << endl;
	cin >> rok_urodzenia;
	cin.get();

	// Przekazanie zmiennych do pliku tekstowego
	bazadanych << imie << " " << nazwisko << " " << rok_urodzenia << "\n";

	cout << "Do bazy danych zosta�y dodane nast�puj�ce warto�ci: " << imie << " " << nazwisko << " " << rok_urodzenia << endl;
}

void delete_line(ifstream& bazadanych) {
	string line; //Musimy iterowa� po danej linii
	int index = 1, //indeksuj� od 1 baz� danych od pocz�tku
		line_to_delete = 0; // musz� zainicjalizowa� zmienn�, 

	// w C++ najprostszym sposobem usuni�cia wybranej linii jest przepisanie ca�ego pliku jeszcze raz z zast�pieniem wybranej linii pust�
	// moim zdaniem najprostszym sposodem jest iterowanie po wszystkich liniach ze stworzeniem specjalnego indexu/countera kt�ry b�dzie wskazywa� na dan� lini�
	// w starszych wersjach j�zyka mo�na by�o to za�atwi� za pomoc� jednej funkcji podana_linia.replace(pocz�tek_linii, koniec_lini, "") lecz w nowszych to nie dzia�a
	// poniewa� zosta�y zmienione typy danych w funkcji replace (a przynajmniej u mnie nie dzia�a albo ja nie umiem tego napisa� pro�ciej)

	// na pocz�tku tworz� tymczasowu plik temp.txt
	ofstream temp; //stw�rz plik temp
	temp.open("temp.txt"); //otw�rz go

	// pobieram od u�ytkownika kt�r� lini� chce usun��
	cout << "Kt�r� lini� chcesz usun��?" << endl;
	cin >> line_to_delete;
	
	if (bazadanych.is_open()) {  // je�li plik jest otwarty...
		while (getline(bazadanych, line)) { // dop�ki znajduj� si� linie w pliku bazadanych...
			if (line_to_delete == index) { //je�li linia kt�r� u�ytkownik chce usun�� jest zgodna z naszym indeksowaniem linii 
				line.erase(line.begin(), line.end()); // wyma� lini� w sensie usuni�cia ca�o�ci zawarto�ci ci�gu znak�w,
													  // efekt uboczny to pozostawienie pustego ci�gu znak�w, ni�ej jest na to rozwi�zanie
			}

			index++; //zwi�ksz indeks co iteracj�

			if (!line.empty()) { // tu rozwi�zanie na pusty ci�g znak�w; je�li linia nie jest pusta czyli nie znajduje si� w niej �aden znak
				temp << line << endl; //przepisz od nowa plik do tymczasowego pliku z pomini�ciem tej linii
			}
		}
	}

	temp.close(); //zamknij tymczasowy plik
	bazadanych.close(); //zamknij baz� danych

	remove("database.txt"); //usu� baz� danych 
	rename("temp.txt","database.txt"); // zmie� nazw� pliku tymczasowego na baz� danych
}

void print_database(ifstream& bazadanych) { // funkcja odpowiedzialna za wypisywanie ca�ej bazy danych z indeksami 
	string line; // aktualnie iterowana linia
	int index = 1; // index linii

	cout << "\nIndex:" << " Imi�:" << " Nazwisko:" << " Rok urodzenia:" << endl; //header, bez dopasowania
	if (bazadanych.is_open()) {  // je�li plik jest otwarty...
		while (getline(bazadanych, line)) { // dop�ki znajduj� si� linie w pliku bazadanych...
			cout << index << " " << line << "\n"; // wypisz lini�
			index++;
		}
	}
}

void find_in_database(ifstream& bazadanych) { //funkcja odpowiedzialna za wyszukiwanie w bazie danych
	string szukane, 
		linia; // inicjalizacja zmiennych, szukanie oraz linia w kt�rej pojawia si� wyra�enie
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
}

void information_about_database(ifstream& bazadanych) {
	streampos begin, //streampos to zmianna odpowiedzialna za reprezentacj� pozycji w strumieniach danych
		end; 
	string line;
	int index = 1;

	begin = bazadanych.tellg(); //tellg zwraca pozycj� obecnej pozycji w strumieniu wej�cia
	bazadanych.seekg(0, ios::end); //seekg ustawia pozycj� nast�pnego znaku
	end = bazadanych.tellg();

	while (!bazadanych.eof()) { // Dop�ki to nie jest koniec pliku
								// End of File - plik zosta� przeczytany do ko�ca, b�d� wyst�pi� b��d podczas pr�by odczytu danych.
		getline(bazadanych, line); // Pobieraj linie z pliku tekstowego
		index++; // Zwi�kszaj licznik
	}

	cout << "\nLiczba wpis�w w bazie danych: " << index << endl;
	cout << "Rozmiar pliku bazy danych: " << (end - begin) << " bajt�w.\n" << endl;
}

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
		cout << "6 - Usu� baz� danych " << endl;
		cout << "0 - Wyjd� z aplikacji\n" << endl;

		// Pobranie od u�ytkownika zmiennej
		cin >> user_choice;
		cin.get();

		if (user_choice == 1) {

			// Otwarcie pliku tekstowego
			ofstream bazadanych;
			bazadanych.open("database.txt", ios::app); // W razie braku pliku, tworzy go w katalogu domowym programu, 
													   // ios::app potrzebne aby w razie istnienia pliku wykorzystywa� go zamiast tworzy� nowy

			add_user(bazadanych); // Wywo�anie funkcji 

			bazadanych.close(); // Zamknij plik
		}
		else if (user_choice == 2) {
			cout << "Usu� dane" << endl;

			ifstream bazadanych("database.txt"); // Otw�rz plik tekstowy

			delete_line(bazadanych); // Wywo�anie funkcji
		}
		else if (user_choice == 3) {
			cout << "Wypisuj� baz� danych...\n" << endl;

			// Otwarcie pliku tekstowego
			ifstream bazadanych("database.txt");
			 
			print_database(bazadanych); // Wywo�anie funkcji

			bazadanych.close(); // zamknij plik
		}
		else if (user_choice == 4) {
			cout << "Wyszukaj w bazie danych" << endl;
			// Otwarcie pliku tekstowego
			ifstream bazadanych("database.txt"); 

			find_in_database(bazadanych); // Wywo�anie funkcji

			bazadanych.close(); // zamknij plik
		}
		else if (user_choice == 5) {
			ifstream bazadanych("database.txt");

			information_about_database(bazadanych); // Wywo�anie funkcji

			bazadanych.close();
		}
		else if (user_choice == 6) {
			string user_decission;

			cout << "Czy na pewno chcesz usun�� baz� danych (Y/N)?" << endl;
			cin >> user_decission;

			if (user_decission == "Y") {
				remove("database.txt");
			}
		}
		else if (user_choice == 0) {
			is_running = false; // Zmiana warto�ci bool odpowiedzialnej za uruchomienie programu

			// Po�egnanie z u�ytkownikiem, zamkni�cie okna
			cout << "\nDo zobaczenia!" << endl;
			cout << "Naci�nij klawisz [Enter] aby zamkn�� okno...\n" << endl;
		}
	}

	cin.get();
	return 0;
}