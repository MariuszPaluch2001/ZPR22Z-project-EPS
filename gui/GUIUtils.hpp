//
// Created by mariusz on 26.12.22.
//
/*
 * Plik z potrzebnymi narzędziami do GUI.
 * Tutaj powinny znajdować się głównie funkcje związane
 * z obsługą plików/zewnętrznych programów.
 */
#ifndef ZPR_GUIUTILS_H
#define ZPR_GUIUTILS_H

#include <iostream>
#include <sys/stat.h>

/**
 * Funkcja do odczytywania rozmiaru plików.
 * Zwraca ona rozmiar pliku w kilobajtach, lub
 * wartość -1 w przypadku braku pliku.
 */
long getFileSize(const std::string &filename) {
  struct stat stat_buf {};
  int rc = stat(filename.c_str(), &stat_buf);
  return rc == 0 ? stat_buf.st_size / 1000 : -1;
}
/**
 * Funkcja konwertująca plik .eps do pliku .png.
 * Wywołuje ona w tym celu program ghostricpt.
 * Celem tej konwersji jest wyświetleniu wyświetlenie pliku
 * .eps w GUI.
 */
int convertEPSFileToPNG(const std::string &path) {
  std::string gs_command_run = "gs -dEPSCrop -sDEVICE=png16m -r200 "
                               "-dDownScaleFactor=8 -o tmp/.output_image.png ";
  gs_command_run += "\"";
  gs_command_run += path;
  gs_command_run += "\"";
  return system(gs_command_run.c_str());
}

#endif // ZPR_GUIUTILS_H
