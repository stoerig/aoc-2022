#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

int part_one(const std::vector<int> &elfs) {
  const auto res = std::max_element(elfs.cbegin(), elfs.cend());
  return *res;
}

int part_two(std::vector<int> &elfs) {
  std::sort(elfs.begin(), elfs.end(), std::greater<int>());

  return elfs[0] + elfs[1] + elfs[2];
}
int main(int, char **) {
  std::vector<int> elfs;
  std::ifstream input("input.txt");

  elfs.push_back(0);
  auto elf = 0;
  for (std::string line; std::getline(input, line);) {
    if (line == "") {
      elfs.push_back(0);
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
