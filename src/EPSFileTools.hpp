//
// Created by mariusz on 08.11.22.
//
//
//    Plik EPSFileTools.h zawiera definicje klas reprezentujących nagłówek pliku
//    (Header), i klasy reprezentujące pliki wejściowe i wyjściowe. Są używane do
//    czytania danych z pliku wejściowego, przekazywania ich do algorytmu
//    i zapisywania wyniku działania algorytmu do pliku wyjściowego.
//
#ifndef ZPR_EPSFILETOOLS_HPP
#define ZPR_EPSFILETOOLS_HPP
#include <fstream>
#include <memory>
#include <variant>

#include "Algorithm.hpp"
#include "EPSCommandRepresentation.h"
#include "GraphicCommands.h"
#include "Scalar2DRepresentation.h"

/**
 * Klasa reprezentująca nagłówek pliku.
 */
class Header {
  Resolution resolution_;
  std::string header_;
  static Resolution findResolution(const std::string &header);
  std::string setResolutionInHeader() const;

public:
  explicit Header(const std::string &header)
      : resolution_(findResolution(header)), header_(header) {}
  /**
   * Funkcja modyfikująca pole rozdzielczość w headerze.
   */
  void setResolution(const Resolution &resolution);
  /**
   * Funkcja nagłówek w postaci stringa.
   */
  std::string getHeaderString() const { return header_; }
  /**
   * Funkcja zwracająca objekt resolution.
   */
  Resolution getResolution() const { return resolution_; }
};

/**
    Klasa reprezentuje plik wejściowy. Jako argumenty w kostruktorze klasa wymagają
    referencji do obiektu pliku. Przed czytaniem komend, objekt klasy powinien przeczytać
    nagłówek poprzez wywołanie metody 'getHeader', w przeciwnym wypadku metoda getCommand rzuci wyjątek.
    Objekt klasy nie zamyka wejściowego pliku.
*/
class EPSInFile {
  std::istream &file_;
  bool was_header_read = false;

  std::string readHeader();
  static CoordinateValue readPoint(const std::string &commandLine);
  static std::string stripCommandSignature(const std::string &commandLine);
  std::string getCommandLine();

public:
  explicit EPSInFile(std::istream &f) : file_(f) {}
  EPSInFile(const EPSInFile &) = delete;
  EPSInFile &operator=(const EPSInFile &) = delete;
  /**
   * Funkcja do zwracania obiektu Header.
   */
  Header getHeader();
  /**
   * Funkcja sprawdza czy plik został już przeczytany.
   */
  bool isFinished() { return file_.peek() == EOF; }
  /**
   * Funkcja sprawdza czy następna komenda jest względna.
   */
  bool isNextRelative();
  /**
   * Funkcja sprawdza czy następna komenda jest absolutna.
   */
  bool isNextAbsolute();
  /**
   * Funkcja sprawdza czy następna komenda jest użytkowa.
   */
  bool isNextUnprocessable();
  /**
   * Funkcja czyta z pliku i zwraca obiekt RelativeCommandVar.
   * Jeśli kolejna komenda nie jest odpowiedniego typu, metoda
   * rzuca wyjątek.
   */
  RelativeCommandVar getRelativeCommandVar();
  /**
   * Funkcja czyta z pliku i zwraca obiekt AbsoluteCommandVar.
   * Jeśli kolejna komenda nie jest odpowiedniego typu, metoda
   * rzuca wyjątek.
   */
  AbsoluteCommandVar getAbsoluteCommandVar();
  /**
   * Funkcja czyta z pliku i zwraca obiekt NonProcessableCommand.
   * Jeśli kolejna komenda nie jest odpowiedniego typu, metoda
   * rzuca wyjątek.
   */
  NonProcessableCommand getNonProcessableCommand();
};

/**
    Klasa reprezentująca plik wyjściowy. Jako argumenty w konstruktorze klasa wymaga
    referencji do obiektu pliku. Przed pisaniem komend, objekt klasy powinien
    zapisać nagłówek poprzez wywołanie metody 'putHeader', w przeciwnym wypadku 'putCommand' rzuci
    wyjątkiem. Obiekt klasy nie zamyka pliku wyjściowego .
*/
class EPSOutFile {
  std::ostream &file_;
  bool was_header_write = false;

public:
  explicit EPSOutFile(std::ostream &f) : file_(f) {}
  EPSOutFile(const EPSOutFile &) = delete;
  EPSOutFile &operator=(const EPSOutFile &) = delete;
  /**
   * Funkcja zapisująca objekt Header do pliku.
   */
  void putHeader(Header &header);
  /**
   * Funkcja zapisująca komendę do pliku. Przyjmuję obiekt command.
   */
  void putCommand(const Command &c);
   /**
   * Funkcja zapisująca komendę do pliku. Przyjmuję stringową wersję komendy.
   */
  void putCommand(const std::string &c);

  template <typename BATCH_TYPE> void putBatch(const BATCH_TYPE &batch);
};

static auto stringVisit = [](const auto &command) {
  return command.toString();
};

template <typename BATCH_TYPE>
void EPSOutFile::putBatch(const BATCH_TYPE &batch) {
  for (auto command : batch)
    putCommand(std::visit(stringVisit, command));
}
#endif // ZPR_EPSFILETOOLS_HPP
