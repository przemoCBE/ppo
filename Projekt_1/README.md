*******************************************************************
Saper - etap 1
*******************************************************************

UWAGA: Obowiązuje zakaz wczytywania czegokolwiek z klawiatury. Jedyną funkcją (na tym etapie) której wolno cokolwiek wyświetlić na ekranie jest funkcja `debug_display()`.

Proszę opracować klasę reprezentującą planszę do gry Saper (Minesweeper). Klasa powinna posiadać informacje o:
* rozmiarze planszy (można przyjąć, że nie przekracza pewnego ustalonego maksimum, np. 100x100)
* stanie każdego z pól:
  * ukryte lub odkryte
  * bezpieczne lub z miną
  * ma "flagę" lub jej nie ma

Wskazówka: informacje o pojedynczym polu na planszy możemy przechowywać w strukturze:
```C++
  struct Field
  {
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
  };

  class MinesweeperBoard
  {
    Field board[100][100];
    int width;
    int height;
    public:
      MinesweeperBoard();
      void debug_display() const;
  };
```

Waszym pierwszym zadaniem jest napisanie konstruktora klasy Plansza oraz funkcji `debug_display()`.
Konstruktor ma:
* ustawić wysokosc i szerokosc planszy (na wartość nie większą niż 100x100 - bo taką sobie tablicę przygotowaliśmy). Proponuję coś "rozsądnego", np. 10x10
* ustawić stan początkowy wszystkich pól planszy na: "nie ma miny", "pole zakryte", "nie ma flagi"

Funkcja `debug_display()` ma wyświetlić planszę w celu weryfikacji poprawności przeprowadzanych operacji - każde pole ma być wyświetlone jako ciąg 3 znaków w nawiasach kwadratowych.
* Znak pierwszy informuje czy na polu jest mina - jeśli jest, to wyświetlamy literę 'M'
* Znak drugi - czy pole jest odkryte ('o')
* Znak trzeci - informuje czy na polu jest flaga - 'f'

Jeśli dany znacznik nie jest ustawiony - wyświetlamy kropkę, np:
```
[M..][...][...][M..][.o.]
[.o.][...][M..][...][.o.]
[M.f][...][...][..f][M..]
```
Następnie proszę zmodyfikować konstruktor i umieścić na planszy jakiś konkretny stan, np.:
* pole (0,0) - zawiera minę
* pole (1,1) - jest odkryte
* pole (2,0) - zawiera minę i flagę

Sprawdzić, czy funkcja `debug_display()` poprawnie wyświetli tą planszę, czyli czy zobaczymy:
```
[M..][...][M.f][...][...]
[...][.o.][...][...][...]
[...][...][...][...][...]
```

*******************************************************************
Kilka wskazówek dotyczących realizacji projektów na które będę zwracał uwagę:
*******************************************************************

- cały kod piszemy w języku angielskim,
- usuwamy zakomentowany kod,
- projekt dostarczamy razem z plikiem CMakeList.txt
- rozbijamy plik nagłówkowy od ciała funkcji (hpp, cpp),
- jeden nagłówek to jedna klasa/struktura -> `minesweeperboard.hpp`, `field.hpp`, itp.,
- komentarze w kodzie robimy w języku angielskim,
- nie zostawiamy kodu testowego (w przyszłości tego typu rzeczy mogą wpływać na bezpieczeństwo aplikacji) – do testowania kodu są testy jednostkowe o których będę mówił na zajęciach,
- korzystamy z ułatwień jakie daje nam język c++,
- w metodach klasy staramy się korzystać ze wskaźnika `this` – informujemy jednoznacznie czytającego skąd się bierze dana metoda lub pole:
```C++
void MinesweeperBoard::debugDisplay() const{
    for (unsigned int i = 0; i< this->height; i++) {
            …
    }
}
```
- do ustawiania pól wykorzystujemy tak zwane settery (enkapsulacja) np.:
```C++
void MinesweeperBoard::setField(int width, int height, const Field& field) {
    if (width < this->width && height < this->height) {
      this->board[height][width] = field;
    }
}
```
- nazwy zmiennych, które są przekazywane do metod powinny nazywać się tak samo, ułatwia to czytanie oraz debugowanie kodu:
```C++
MinesweeperBoard::minesweeperBoard(unsigned int width, unsigned int height): width(width), height(height) {}
```
- jeśli mamy klasę, to zawsze najpierw interesuje nas to jaki interfejs udostępnia, czyli w pierwszej kolejności wypisujemy konstruktory oraz metody publiczne:
```C++
class MinesweeperBoard {
  public:
    MinesweeperBoard()
    void debugDisplay() const;
  protected:
    …
  private:
    …
};
```
