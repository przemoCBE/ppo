#include <iostream>

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

void display_student(const student &doWyswietlenia){
	cout << "Imię:"       << doWyswietlenia.imie            << endl
	     << "Nazwisko:"   << doWyswietlenia.nazwisko        << endl
	     << "Płeć:"       << plecNazwa[doWyswietlenia.plec] << endl
	     << "PESEL:"      << doWyswietlenia.pesel           << endl
	     << "nr indeksu:" << doWyswietlenia.indeks          << endl;
}

void display_all_students(student tablica[],unsigned int rozmiar){
	for (unsigned int i=0;i<rozmiar;i++){
		display_student(tablica[i]);
		cout << "------------------\n";
	}
}

int main(){
	student test[] = {{"abcd","def",mezczyzna,"00000000000","123456"},{"dcba","acd",kobieta,"11111111111","654321"},{"test","test",mezczyzna,"22222222222","246801"}};
	display_all_students(test,3);
	return 0;
}

