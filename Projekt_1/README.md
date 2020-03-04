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
