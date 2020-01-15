//============================================================================
// @name        : leaderboard.h
// @author      : Thomas Dooms
// @date        : 12/19/19
// @version     :
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description :
//============================================================================

#pragma once

#include "../parsers/parser.h"
#include "object.h"

#include <filesystem>
#include <fstream>

namespace model {
// big class but almost every function is trivial
// so i decided to keep it in the .h file to reduce clutter.
class Leaderboard : public Object {
public:
  explicit Leaderboard(const std::filesystem::path &path, size_t score)
      : path(path), score(score) {
    scores = parser::loadLeaderboard(path);
    sortScores();
    showName = highscore();
  }

  void update([[maybe_unused]] core::World &world) override {}

  bool highscore() { return score > scores.back().first; }

  void sortScores() {
    constexpr auto comp = [](const auto &lhs, const auto &rhs) {
      return lhs.first < rhs.first;
    };
    std::sort(scores.rbegin(), scores.rend(), comp);
  }

  void complete() {
    if (not highscore())
      return;
    scores.back() = std::make_pair(score, name);
    sortScores();
    parser::storeLeaderboard(path, scores);

    showName = false;
    send(Event::valueChanged);
  }

  [[nodiscard]] char getChar() const noexcept { return current; }
  [[nodiscard]] char getPrevChar() const noexcept {
    if (current == 'a')
      return 'z';
    else
      return static_cast<char>(current - 1);
  }
  [[nodiscard]] char getNextChar() const noexcept {
    if (current == 'z')
      return 'a';
    else
      return static_cast<char>(current + 1);
  }

  [[nodiscard]] const std::string &getName() const noexcept { return name; }

  [[nodiscard]] const auto &getScores() const noexcept { return scores; }

  void nextChar() noexcept {
    if (current == 'z')
      current = 'a';
    else
      current++;
    send(Event::valueChanged);
  }
  void prevChar() noexcept {
    if (current == 'a')
      current = 'z';
    else
      current--;
    send(Event::valueChanged);
  }

  void appendChar() {
    if (name.size() > 12)
      return;
    name += current;
    send(Event::valueChanged);
  }
  void popChar() {
    if (name.empty())
      return;
    name.pop_back();
    send(Event::valueChanged);
  }

  [[nodiscard]] bool getShowName() const noexcept { return showName; }

private:
  std::filesystem::path path;
  std::vector<std::pair<size_t, std::string>> scores;

  std::string name;
  size_t score;

  char current = 'a';

  bool showName;
};
} // namespace model