# Aplikacja do odchudzania plików .eps

## Autorzy
* Kacper Kozerski
* Mariusz Paluch 

## Opis
Celem działania aplikacji jest zmniejszanie rozmiaru plików .eps. 
Składają się one z instrukcji rysujących.

Pliki te są często wyjściem procesów symulacyjnych.
Zawierają dużo redundantnych danych - np. zaznaczone punkty znajdują się zbyt blisko siebie, aby
móc realnie dostrzec różnicę w założonej rozdzielczości.

Aplikacja ma wykrywać właśnie takie dane i dokonywać kompresji stratnej dla zadanie rozdzielczości
## Używane standardy, biblioteki i narzędzia
1. C++17
2. GTest - do testów jednostkowych, pobierane przez CMake
3. ghostscript
4. wx-widgets
5. CMake, make - narzędzia do zautomatyzowania budowania aplikacji
6. Clang-format - do dodawania białych znaków w odpowiedni sposób
## Instalacja, budowanie i uruchamianie
### Instalacja wx-widgets
1. `sh install_wx_widgets` 
### Budowanie aplikacji
1. Instalacja wx-widgets
1. `mkdir bin`
2. `cmake -B bin`
3. `cd bin`
4. `make`
### Demonstracja działania konsolowego
1. Budowanie aplikacji
2. `./zpr sciezka_do_pliku_eps sciezka_wyjsciowa_do_pliku`
### Demonstracja graficznego interfejsu
1. Budowanie aplikacji
2. `./zprGUI`

## Uruchomienie testów jednostkowych
1. Budowanie aplikacji
2. `make test`

## Instrukcja użytkowania GUI
Należy najpierw wybrać plik .eps, który będziemy obrabiać.
Następnie wybieramy opcje przetwarzania pliku
Potem wybieramy Potwierdz. Po chwili pojawi się obrazek poglądowy. Można
go zapisać klikając Zapisz
### Opis opcji kompresji:
* Pomniejszenie - ile razy zmniejszamy obraze. 1x - nie zmieniamy rozmiarów
* Min odleglosc miedzy punktami - oszacowanie, jaka najkrótsza odległość między punktami jest jeszcze dostrzegalna. 
Im więcej - tym kompresja jest mocniejsza. 0 - usuwamy tylko punkty bezpośrednio na sobie
* Zakres sortowania - heurystyka, ile następujących po sobie punktów będzie sortowane w porządku, takim, że każdy 
kolejny jest najbliżej poprzedniego z pozostałych w zakresie sortowania. Im więcej tym dłuższe procesowanie,
  ale lepsza kompresja
  
### Pliki testowe
Załączamy pliki .eps, które były dodane do treści zadania

## Środowisko pracy

W projekcie używamy gita, Gitlaba oraz  IDE - Cliona.
