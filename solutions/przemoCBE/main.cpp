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

inline ePlec input_gender(){
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

string input_regex(const regex &wzor,const string &nazwaWartosci,const string &opisWzoru){
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
	beginning:
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
	bufor.plec = input_gender();
	bufor.pesel = input_regex(rPesel,"PESEL","PESEL musi mieć dokładnie 11 cyfr");
	bufor.indeks = input_regex(rIndeks,"nr indeksu","Nr indeksu musi mieć dokładnie 6 cyfr");
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
	goto beginning;
}

bool remove_student(int indeks, bazaStudentow &baza){
	if (indeks<0||indeks>=baza.rozmiar)
		return false;
	for (int i=indeks;i<baza.rozmiar;i++)
		baza.baza[i]=baza.baza[i+1];
	baza.rozmiar--;
	return true;
}

string read_cstring(ifstream &file){
	char znak;
	string wartosc;
	while (true){
		file.read(&znak,1);
		if (znak=='\0')
			return wartosc;
		wartosc += znak;
	}
}

void load_students (string sciezka,bazaStudentow &baza){
	student nowy;
	ifstream file;
	file.open(sciezka,fstream::binary);
	if (file.good()){
		while (file.peek()!=EOF){
			nowy.imie     = read_cstring(file);
			nowy.nazwisko = read_cstring(file);
			nowy.pesel    = read_cstring(file);
			nowy.indeks   = read_cstring(file);
			file.read((char *)&(nowy.plec),sizeof(ePlec));
			baza.baza[baza.rozmiar]=nowy;
			baza.rozmiar++;
		}
	}
}

void write_cstring(ofstream &file,string doPisania){
	file << doPisania << '\0';
}

void save_students (string sciezka,const bazaStudentow &baza){
	ofstream file;
	file.open(sciezka,fstream::binary);
	if (file.good()){
		for (int i = 0;i<baza.rozmiar;i++){
			write_cstring(file,baza.baza[i].imie);
			write_cstring(file,baza.baza[i].nazwisko);
			write_cstring(file,baza.baza[i].pesel);
			write_cstring(file,baza.baza[i].indeks);
			file.write((char *)&(baza.baza[i].plec),sizeof(ePlec));
		}
	}
}

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
