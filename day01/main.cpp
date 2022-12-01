#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>

int part_one(const std::map<int, int> &elfs) {
  const auto res = std::max_element(
      elfs.cbegin(), elfs.cend(),
      [](const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
        return p1.second < p2.second;
      });

  return res->second;
}

int part_two(std::map<int, int> &elfs) {
  auto sum_of_top_three = 0;
  for (int i = 0; i < 3; i++) {
    const auto res = std::max_element(
        elfs.cbegin(), elfs.cend(),
        [](const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
          return p1.second < p2.second;
        });

    sum_of_top_three += res->second;
    elfs.erase(res->first);
  }

  return sum_of_top_three;
}
int main(int, char **) {
  std::map<int, int> elfs;
  std::ifstream input("input.txt");

  int elf = 0;
  elfs[elf] = 0;
  for (std::string line; std::getline(input, line);) {
    if (line == "") {
      elf++;
    } else {
      elfs[elf] += std::stoi(line);
    }
  }

  std::cout << "C++" << '\n';
  const auto part = std::getenv("part");
  if (part == nullptr || strcmp(part, "part1") == 0) {
    std::cout << part_one(elfs) << '\n';
  } else {
    std::cout << part_two(elfs) << '\n';
  }
}
