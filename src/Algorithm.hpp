//
// Created by kacper on 07.12.2022.
// File contains class representing Algorithm
//

#ifndef ZPR_ALGORITHM_HPP
#define ZPR_ALGORITHM_HPP
#include "GraphicCommands.h"
#include "Scalar2DRepresentation.h"
#include <functional>
#include <variant>
#include <vector>

using RelativeBatch = std::vector<RelativeCommandVar>;
using AbsoluteBatch = std::vector<AbsoluteCommandVar>;
/**
 * Algorytm wyznacza, które z komend można usunąć, a także oferuje usuwanie ich z porcji danych
 */
class Algorithm {
private:
  double min_difference_;
  double scaling_factor_;
  unsigned sorting_range_;

public:
  explicit Algorithm(double min_difference, double scaling_factor = 1,
                     unsigned sorting_range = 10)
      : min_difference_(min_difference), scaling_factor_(scaling_factor),
        sorting_range_(sorting_range) {}
        /**
         * @brief funkcja zwraca ustawioną, minimalną znaczącą odległość między punktami
         */
  double getMinDifference() const { return min_difference_; }
  /**
   * Funkcja ustawiana zadaną minimalną znaczącą odległość między punktami
   */
  void setMinDifference(double min_difference) {
    min_difference_ = min_difference >= 0 ? min_difference : min_difference_;
  }
  /**
   * Funkcja zwraca ustawiony współczynnik skalowania, który mówi jak zmniejszony/zwiększony ma być obrazek
   */
  double getScalingFactor() const { return scaling_factor_; }
  /**
   * Funkcja ustawia współczynnik skalowania, który mówi jak zmniejszony/zwiększony ma być obrazek
   */
  void setScalingFactor(double scaling_factor) {
    scaling_factor_ = scaling_factor > 0 ? scaling_factor : scaling_factor_;
  }
  /**
   * Funkcja zwraca ustawiony zakres sortowania
   */
  unsigned getSortingRange() const { return sorting_range_; }
  /**
   * Funkcja ustawia zakres sortowania
   */
  void setSortingRange(unsigned sorting_range) {
    sorting_range_ = sorting_range;
  }
  /**
   * Funkcja dokonuje przeskalowania podanej porcji danych
   */
  template <typename T> void rescaleBatch(T &) const;
  /**
   * Funkcja dokonuje oszacowania, które komendy można usunąć
   * @return porcję danych po obróbce
   */
  template <typename T> T processBatch(const T &) const;
  /**
   * Funkcja dokonuje sortowania zakresowego próbki
   */
  template <typename T> void sortBatch(T &) const;
};

static auto rescaleVisit = [](double scaling_factor) {
  return [scaling_factor](auto &graphic) { graphic.rescale(scaling_factor); };
};

static auto differenceVisit = [](const auto &prevGraphic,
                                 const auto &nextGraphic) {
  return countDifference(prevGraphic, nextGraphic);
};
static auto midpointVisit = [](const auto &prevGraphic,
                               const auto &nextGraphic) {
  return createMidpoint(prevGraphic, nextGraphic);
};

template <typename T> void Algorithm::rescaleBatch(T &batch) const {
  auto visit = rescaleVisit(scaling_factor_);
  for (auto &graphic : batch)
    std::visit(visit, graphic);
}

template <typename T> T Algorithm::processBatch(const T &batch) const {
  // nie trzeba procesować
  if (batch.size() < 2)
    return batch;
  auto prev_graphic_command = batch.at(0);
  T post_processing{};

  // procesujemy od drugiej próbki
  for (auto iter = batch.cbegin() + 1; iter != batch.cend(); iter++) {
    double difference =
        std::visit(differenceVisit, prev_graphic_command, *iter);
    // jeżeli odległość mniejsza -> możemy stworzyć punkt pośredni
    if (difference <= min_difference_)
      prev_graphic_command =
          std::visit(midpointVisit, prev_graphic_command, *iter);
    // w przeciwnym przypadku - przepisujemy komendę roboczą na wyjście i idziemy dalej
    else {
      post_processing.push_back(prev_graphic_command);
      prev_graphic_command = *iter;
    }
  }
  // wkładamy ostatni element
  post_processing.push_back(prev_graphic_command);
  return post_processing;
}
template <typename T> void Algorithm::sortBatch(T &batch) const {
  // przeglądamy porcje po K elementów
    for (int i = 0; i + sorting_range_ <= batch.size(); i += sorting_range_) {
    auto working_element = batch.at(i);
    auto starting = batch.begin() + 1 + i;
    auto stopping = batch.begin() + i + sorting_range_;
    for (auto iter = starting; iter != stopping; iter++) {
        // zwracamy najbliższy z pozostałych elementów w porcji, do punktu roboczego
      auto minimal = std::min_element(
          iter, stopping, [&working_element](auto &a, auto &b) {
            return std::visit(differenceVisit, working_element, a) <
                   std::visit(differenceVisit, working_element, b);
          });
      // zamieniamy miejscami najbliśzy do roboczego i przeglądany
      // wybrany jest nowym punktem roboczym
      std::iter_swap(iter, minimal);
      working_element = *iter;
    }
  }
}

//Relative Batch nie sortujemy
template <>
void Algorithm::sortBatch<RelativeBatch>(RelativeBatch &batch) const;



#endif // ZPR_ALGORITHM_HPP
