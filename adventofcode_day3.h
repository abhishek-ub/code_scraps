#include <iostream>
#include <string>

void adventofcode_day3()
{
  std::string input;
  std::getline(std::cin, input);
  std::size_t line_len = input.length();
  int start = 1;
  int trees = 0;
  std::getline(std::cin, input);
  while (std::getline(std::cin, input) && input.length()) {
    if (input[start % line_len] == '#') trees++;
    start += 1;
    std::getline(std::cin, input);
  }
  std::cout << trees << std::endl;
}