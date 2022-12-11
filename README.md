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
3. (w następnej wersji) używany będzie pakiet graficzny (prawdopodobnie R Graphics)
4. (w następnej wersji) używana będzie biblioteka do GUI (np. Qt)
5. CMake, make - narzędzia do zautomatyzowania budowania aplikacji
6. Clang-format - do dodawania białych znaków w odpowiedni sposób
## Instrukcja użytkowania
Obecnie dostępny jest szkielet aplikacji, z testami jednostkowymi dla 
dostępny funkcjonalności i aplikacją demonstracyjną

Budowanie aplikacji
1. `mkdir bin`
2. `cmake -B bin`
3. `cd bin`
4. `make`

Demonstracja działania
1. Budowanie aplikacji
2. `./zpr sciezka_do_pliku_eps sciezka_wyjsciowa_do_pliku`

Odpalenie testów jednostkowych
1. Budowanie aplikacji
2. `make test`

## Uwagi
Nie ma testów jednostkowych dla funkcji, które nie mają jeszcze implementacji.

Z poziomu CMake'a tworzone są biblioteki podzielone, tak jak w dokumentacji wstępnej.

W projekcie używamy gita, Gitlaba oraz  IDE - Cliona.
## Napotkane problemy
* W projekcie staraliśmy się unikać jak najmocniej dynamicznej alokacji pamięci. Uzyskaliśmy to dzięki std::variant,
    może to jednak zmniejszyć skalowalność aplikacji - będzie to przedmiotem dalszych konsultacji
* Przewidujemy, że zmienimy hierarchię klas w Scalar2DRepresentation - np. Resolution nie jest idealną klasą potomną po
    jej klasie bazowej, bo operuje tylko na liczbach całkowitych. Hierachia zostanie zmieniona w kolejnym etapie
## Planowany rozwój
* Zamierzamy "nastroić" algorytm 
    * dodając prawdziwą implementację dla MidpointVisitor, która będzię tworzyła punkt pośredni między komendami
    * umożliwić zrzutowanie komend z obrazka na komendy z obrazka innego rozmiaru
* Zamierzamy dodać graficzny interfejs użytkownika
    * będzie umożliwiał wybieranie plików eps oraz wprowadzanie ich docelowych rozmiarów
    * będzie rysował obrazki przy pomocy pakietu graficznego
* Użyty zostanie C++20 z jego funkcjonalnościami    