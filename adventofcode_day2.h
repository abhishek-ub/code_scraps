#include <bits/stdc++.h>

int validate(int min, int max, char c, const std::string& pass)
{
  auto count = std::count(pass.begin(), pass.end(), c);
  if (min <= count && count  <= max) {
    return 1;
  }
  return 0;
}

int adventofcode_day2()
{
  int result = 0;
  std::string input;
  std::regex rgx("([0-9]+)-([0-9]+)\\s([a-z]):\\s([a-z]+)");
  std::smatch matches;
  int min , max;
  std::string pass;
  std::istringstream ss;
  while ( std::getline(std::cin, input) && input.length() )
  {
    if (std::regex_search(input, matches, rgx)) {
      result += validate(std::stoi(matches[1].str()),
        std::stoi(matches[2].str()),
        matches[3].str()[0],
        matches[4].str()
        );
    } else {
      std:: cout << "no match \n";
    }
  }
  std::cout << result << std::endl;
  return 0;
}