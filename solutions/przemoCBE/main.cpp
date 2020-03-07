#include <iostream>
#include <regex>
#include <fstream>

using namespace std;

enum ePlec              { mezczyzna , kobieta };
const string plecNazwa[]{"mężczyzna","kobieta"};


struct student{
	string imie;
	string nazwisko;
	ePlec plec;
	string pesel;
	string indeks;
};

struct bazaStudentow{
	student baza[100];
	int rozmiar;
};

void display_student(const student &doWyswietlenia){
	cout << "Imię: "       << doWyswietlenia.imie            << endl
	     << "Nazwisko: "   << doWyswietlenia.nazwisko        << endl
	     << "Płeć: "       << plecNazwa[doWyswietlenia.plec] << endl
	     << "PESEL: "      << doWyswietlenia.pesel           << endl
	     << "nr indeksu: " << doWyswietlenia.indeks          << endl;
}

void display_all_students(student tablica[],unsigned int rozmiar){
	cout << "------------------\n";
	for (unsigned int i=0;i<rozmiar;i++){
		display_student(tablica[i]);
		cout << "------------------\n";
	}
}

int find_student(string indeks, bazaStudentow baza){
	for (int i=0;i<baza.rozmiar;i++)
		if (baza.baza[i].indeks==indeks)
			return i;
	return -1;
}

inline ePlec wprowadz_plec(){
	powrot:
	cout << "płeć: ";
	string plec;
	cin >> plec;
	for (unsigned int i=0;i<2;i++)
		if (plec==plecNazwa[i]||plec==to_string(i))
			return static_cast<ePlec>(i);
	cout << "nieprawidłowa wartość!\n"
		 << "prawidłowe wartości (pełna nazwa lub liczba) to:\n";
	for (unsigned int i=0;i<2;i++)
		cout << i << " "
		     << plecNazwa[i] << endl;
	goto powrot;
}
//dla PESELu i nr indeksu
string wprowadz_regex(const regex &wzor,const string &nazwaWartosci,const string &opisWzoru){
	powrot:
	string wartosc;
	cout << nazwaWartosci << ": ";
	cin >> wartosc;
	if (regex_match(wartosc,wzor))
		return wartosc;
	cout << "Nieprawidłowa wartośc!\n"
	     << opisWzoru << endl;
	goto powrot;
}

bool add_student(bazaStudentow &baza){
	powrot:
	if (baza.rozmiar>=100){
		cout << "brak miejsca!\n";
		return false;
	}
	const regex rPesel("^[0-9]{11}$"),
	            rIndeks("^[0-9]{6}$");
	student bufor;
	cout << "Imię: ";
	cin  >> bufor.imie;
	cout << "Nazwisko: ";
	cin  >> bufor.nazwisko;
	bufor.plec = wprowadz_plec();
	bufor.pesel = wprowadz_regex(rPesel,"PESEL","PESEL musi mieć dokładnie 11 cyfr");
	bufor.indeks = wprowadz_regex(rIndeks,"nr indeksu","Nr indeksu musi mieć dokładnie 6 cyfr");
	cout << "------------------\n";
	display_student(bufor);
	cout << "------------------\n"
	     << "czy dane są prawidłowe?(t/N):";
	string odpowiedz;
	cin  >> odpowiedz;
	if (odpowiedz[0]=='t'){
		baza.baza[baza.rozmiar]=bufor;
		baza.rozmiar++;
		return true;
	}
	goto powrot;
}

bool remove_student(int indeks, bazaStudentow &baza){
	if (indeks<0||indeks>=baza.rozmiar)
		return false;
	for (int i=indeks;i<baza.rozmiar;i++)
		baza.baza[i]=baza.baza[i+1];
	baza.rozmiar--;
	return true;
}

string czytajCstring(ifstream &plik){
	char znak;
	string wartosc;
	while (true){
		plik.read(&znak,1);
		if (znak=='\0')
			return wartosc;
		wartosc += znak;
	}
}

void load_students (string sciezka,bazaStudentow &baza){
	student nowy;
	ifstream plik;
	plik.open(sciezka,fstream::binary);
	if (plik.good()){
		while (plik.peek()!=EOF){
			nowy.imie     = czytajCstring(plik);
			nowy.nazwisko = czytajCstring(plik);
			nowy.pesel    = czytajCstring(plik);
			nowy.indeks   = czytajCstring(plik);
			plik.read((char *)&(nowy.plec),sizeof(ePlec));
			baza.baza[baza.rozmiar]=nowy;
			baza.rozmiar++;
		}
	}
}

void piszCstring(ofstream &plik,string doPisania){
	plik << doPisania << '\0';
}

void save_students (string sciezka,const bazaStudentow &baza){
	ofstream plik;
	plik.open(sciezka,fstream::binary);
	if (plik.good()){
		for (int i = 0;i<baza.rozmiar;i++){
			piszCstring(plik,baza.baza[i].imie);
			piszCstring(plik,baza.baza[i].nazwisko);
			piszCstring(plik,baza.baza[i].pesel);
			piszCstring(plik,baza.baza[i].indeks);
			plik.write((char *)&(baza.baza[i].plec),sizeof(ePlec));
		}
	}
}

//funkcje testowe
/*
int main(){
	bazaStudentow test = {{{"abcd","def",mezczyzna,"00000000000","123456"},{"dcba","acd",kobieta,"11111111111","654321"},{"test","test",kobieta,"22222222222","246801"}},3};
	add_student(test);
	display_all_students(test.baza,test.rozmiar);
	cout << "indeks studenta z numerem indeksu 654321: " << find_student("654321",test) << endl;
	remove_student(1,test);
	display_all_students(test.baza,test.rozmiar);
	save_students("test",test);
	return 0;
}
*/
/*
int main(){
	bazaStudentow test{{},0};
	load_students("test",test);
	display_all_students(test.baza,test.rozmiar);
	return 0;
}
*/

int main(){
	bazaStudentow baza{{},0};
	cout << "czy wczytać dane z pliku?(t/N)";
	string odpowiedz;
	cin  >> odpowiedz;
	if (odpowiedz[0]=='t'){
		cout << "ścieżka: ";
		cin  >> odpowiedz;
		load_students(odpowiedz,baza);
	}
	while (true){
		string wybor;
		int intWybor;
		cout << "------------------\n"
		     << "1. wyświetl studentów\n"
		     << "2. znajdź studenta\n"
		     << "3. dodaj studenta\n"
		     << "4. usuń studenta\n"
		     << "5. zapisz\n"
		     << "6. wyjdź\n"
		     << "------------------\n"
		     << "wybór: ";
		cin >> odpowiedz;
		switch (odpowiedz[0]){
			case '1':
			display_all_students(baza.baza,baza.rozmiar);
			break;
			case '2':
			cout << "nr indeksu: ";
			cin  >> wybor;
			cout << "indeks:" << find_student(wybor,baza) << endl;
			break;
			case '3':
			add_student(baza);
			break;
			case '4':
			cout << "indeks: ";
			cin  >> intWybor;
			remove_student(intWybor,baza);
			break;
			case '5':
			cout << "ścieżka: ";
			cin  >> wybor;
			save_students(wybor,baza);
			break;
			case '6':
			return 0;
		}
	}
	return 0;
}
