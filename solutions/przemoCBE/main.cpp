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
	cout << "------------------\n";
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

bool remove_student(bazaStudentow &baza,int indeks){
	if (indeks<0||indeks>=baza.rozmiar)
		return false;
	for (int i=indeks;i<baza.rozmiar;i++)
		baza.baza[i]=baza.baza[i+1];
	baza.rozmiar--;
	return true;
}

int main(){
	bazaStudentow test = {{{"abcd","def",mezczyzna,"00000000000","123456"},{"dcba","acd",kobieta,"11111111111","654321"},{"test","test",mezczyzna,"22222222222","246801"}},3};
	add_student(test);
	display_all_students(test.baza,test.rozmiar);
	cout << "indeks studenta z numerem indeksu 654321: " << find_student("654321",test) << endl;
	remove_student(test,1);
	display_all_students(test.baza,test.rozmiar);
	return 0;
}

