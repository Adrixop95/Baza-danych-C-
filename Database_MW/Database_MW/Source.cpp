/*

Dalej nie jest to najlepszy program. Nie posiada on ¿adnych wyj¹tków dla wpisania przez u¿ytkownika znaku innego ni¿ dany typ
Ca³oœæ powinna zostaæ rozbita na mniejsze pliki
Nie czyœci³em kodu, jeœli s¹ w nim jakieœ pozosta³oœci, niepotrzebne komentarze, niepotrzebne definicje to przepraszam.

W razie problemu ze zrozumieniem czegoœ pytaj œmia³o.

Funkcjonalnoœæ: 
> Odczyt/zapis do pliku tekstowego
> Pobieranie od u¿ytkownika danych
> Usunie danych u¿ytkownika
> Usunie bazy danych
> Wypisanie na ekranie bazy danych
> Wyœwietlenie informacji o pliku bazy danych
> Wyszukiwanie w bazie danych

Adrian~
*/

#include <iostream> // Standardowa biblioteka we/wy
#include <locale.h> // Potrzebna do polskich znaków
#include <fstream> // Potrzebna do operacji na plikach txt
#include <string> // Operacje na ci¹gach znaków

using namespace std;

void add_user(ofstream& bazadanych) { // Funkcja odpowiada za dodanie u¿ytkownika
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
	cin >> nazwisko;

	cout << "Podaj rok urodzenia: " << endl;
	cin >> rok_urodzenia;
	cin.get();

	// Przekazanie zmiennych do pliku tekstowego
	bazadanych << imie << " " << nazwisko << " " << rok_urodzenia << "\n";

	cout << "Do bazy danych zosta³y dodane nastêpuj¹ce wartoœci: " << imie << " " << nazwisko << " " << rok_urodzenia << endl;
}

void delete_line(ifstream& bazadanych) {
	string line; //Musimy iterowaæ po danej linii
	int index = 1, //indeksujê od 1 bazê danych od pocz¹tku
		line_to_delete = 0; // muszê zainicjalizowaæ zmienn¹, 

	// w C++ najprostszym sposobem usuniêcia wybranej linii jest przepisanie ca³ego pliku jeszcze raz z zast¹pieniem wybranej linii pust¹
	// moim zdaniem najprostszym sposodem jest iterowanie po wszystkich liniach ze stworzeniem specjalnego indexu/countera który bêdzie wskazywa³ na dan¹ liniê
	// w starszych wersjach jêzyka mo¿na by³o to za³atwiæ za pomoc¹ jednej funkcji podana_linia.replace(pocz¹tek_linii, koniec_lini, "") lecz w nowszych to nie dzia³a
	// poniewa¿ zosta³y zmienione typy danych w funkcji replace (a przynajmniej u mnie nie dzia³a albo ja nie umiem tego napisaæ proœciej)

	// na pocz¹tku tworzê tymczasowu plik temp.txt
	ofstream temp; //stwórz plik temp
	temp.open("temp.txt"); //otwórz go

	// pobieram od u¿ytkownika któr¹ liniê chce usun¹æ
	cout << "Któr¹ liniê chcesz usun¹æ?" << endl;
	cin >> line_to_delete;
	
	if (bazadanych.is_open()) {  // jeœli plik jest otwarty...
		while (getline(bazadanych, line)) { // dopóki znajduj¹ siê linie w pliku bazadanych...
			if (line_to_delete == index) { //jeœli linia któr¹ u¿ytkownik chce usun¹æ jest zgodna z naszym indeksowaniem linii 
				line.erase(line.begin(), line.end()); // wyma¿ liniê w sensie usuniêcia ca³oœci zawartoœci ci¹gu znaków,
													  // efekt uboczny to pozostawienie pustego ci¹gu znaków, ni¿ej jest na to rozwi¹zanie
			}

			index++; //zwiêksz indeks co iteracjê

			if (!line.empty()) { // tu rozwi¹zanie na pusty ci¹g znaków; jeœli linia nie jest pusta czyli nie znajduje siê w niej ¿aden znak
				temp << line << endl; //przepisz od nowa plik do tymczasowego pliku z pominiêciem tej linii
			}
		}
	}

	temp.close(); //zamknij tymczasowy plik
	bazadanych.close(); //zamknij bazê danych

	remove("database.txt"); //usuñ bazê danych 
	rename("temp.txt","database.txt"); // zmieñ nazwê pliku tymczasowego na bazê danych
}

void print_database(ifstream& bazadanych) { // funkcja odpowiedzialna za wypisywanie ca³ej bazy danych z indeksami 
	string line; // aktualnie iterowana linia
	int index = 1; // index linii

	cout << "\nIndex:" << " Imiê:" << " Nazwisko:" << " Rok urodzenia:" << endl; //header, bez dopasowania
	if (bazadanych.is_open()) {  // jeœli plik jest otwarty...
		while (getline(bazadanych, line)) { // dopóki znajduj¹ siê linie w pliku bazadanych...
			cout << index << " " << line << "\n"; // wypisz liniê
			index++;
		}
	}
}

void find_in_database(ifstream& bazadanych) { //funkcja odpowiedzialna za wyszukiwanie w bazie danych
	string szukane, 
		linia; // inicjalizacja zmiennych, szukanie oraz linia w której pojawia siê wyra¿enie
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
}

void information_about_database(ifstream& bazadanych) {
	streampos begin, //streampos to zmianna odpowiedzialna za reprezentacjê pozycji w strumieniach danych
		end; 
	string line;
	int index = 1;

	begin = bazadanych.tellg(); //tellg zwraca pozycjê obecnej pozycji w strumieniu wejœcia
	bazadanych.seekg(0, ios::end); //seekg ustawia pozycjê nastêpnego znaku
	end = bazadanych.tellg();

	while (!bazadanych.eof()) { // Dopóki to nie jest koniec pliku
								// End of File - plik zosta³ przeczytany do koñca, b¹dŸ wyst¹pi³ b³¹d podczas próby odczytu danych.
		getline(bazadanych, line); // Pobieraj linie z pliku tekstowego
		index++; // Zwiêkszaj licznik
	}

	cout << "\nLiczba wpisów w bazie danych: " << index << endl;
	cout << "Rozmiar pliku bazy danych: " << (end - begin) << " bajtów.\n" << endl;
}

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
		cout << "6 - Usuñ bazê danych " << endl;
		cout << "0 - WyjdŸ z aplikacji\n" << endl;

		// Pobranie od u¿ytkownika zmiennej
		cin >> user_choice;
		cin.get();

		if (user_choice == 1) {

			// Otwarcie pliku tekstowego
			ofstream bazadanych;
			bazadanych.open("database.txt", ios::app); // W razie braku pliku, tworzy go w katalogu domowym programu, 
													   // ios::app potrzebne aby w razie istnienia pliku wykorzystywa³ go zamiast tworzyæ nowy

			add_user(bazadanych); // Wywo³anie funkcji 

			bazadanych.close(); // Zamknij plik
		}
		else if (user_choice == 2) {
			cout << "Usuñ dane" << endl;

			ifstream bazadanych("database.txt"); // Otwórz plik tekstowy

			delete_line(bazadanych); // Wywo³anie funkcji
		}
		else if (user_choice == 3) {
			cout << "Wypisujê bazê danych...\n" << endl;

			// Otwarcie pliku tekstowego
			ifstream bazadanych("database.txt");
			 
			print_database(bazadanych); // Wywo³anie funkcji

			bazadanych.close(); // zamknij plik
		}
		else if (user_choice == 4) {
			cout << "Wyszukaj w bazie danych" << endl;
			// Otwarcie pliku tekstowego
			ifstream bazadanych("database.txt"); 

			find_in_database(bazadanych); // Wywo³anie funkcji

			bazadanych.close(); // zamknij plik
		}
		else if (user_choice == 5) {
			ifstream bazadanych("database.txt");

			information_about_database(bazadanych); // Wywo³anie funkcji

			bazadanych.close();
		}
		else if (user_choice == 6) {
			string user_decission;

			cout << "Czy na pewno chcesz usun¹æ bazê danych (Y/N)?" << endl;
			cin >> user_decission;

			if (user_decission == "Y") {
				remove("database.txt");
			}
		}
		else if (user_choice == 0) {
			is_running = false; // Zmiana wartoœci bool odpowiedzialnej za uruchomienie programu

			// Po¿egnanie z u¿ytkownikiem, zamkniêcie okna
			cout << "\nDo zobaczenia!" << endl;
			cout << "Naciœnij klawisz [Enter] aby zamkn¹æ okno...\n" << endl;
		}
	}

	cin.get();
	return 0;
}