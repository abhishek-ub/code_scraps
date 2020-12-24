#include <bits/stdc++.h>

class AdvCodeDay2 {
  std::regex  _rgx;
  std::smatch _matches;

  int count_part1(int min, int max, char c, const std::string& pass)
  {
    auto count = std::count(pass.begin(), pass.end(), c);
    if (min <= count && count  <= max) {
      return 1;
    }
    return 0;
  }

public:
  AdvCodeDay2() : _rgx("([0-9]+)-([0-9]+)\\s([a-z]):\\s([a-z]+)")
  {
  }

  void adventofcode_day2_part1()
  {
    int result = 0;
    std::string input;
    while ( std::getline(std::cin, input) && input.length() )
    {
      if (std::regex_search(input, _matches, _rgx)) {
        result += count_part1(std::stoi(_matches[1].str()),
          std::stoi(_matches[2].str()),
          _matches[3].str()[0],
          _matches[4].str()
          );
      } else {
        std:: cout << "no match \n";
      }
    }
    std::cout << result << std::endl;
  }

  void adventofcode_day2_part2()
  {
    int result = 0;
    std::string input, pass;
    char c;
    int i , j;

    while ( std::getline(std::cin, input) && input.length() )
    {
      if (std::regex_search(input, _matches, _rgx)) {
        i     = std::stoi(_matches[1].str());
        j     = std::stoi(_matches[2].str());
        pass  = _matches[4].str();
        c     = _matches[3].str()[0];
        if (i <= 0 || j > pass.length()) continue;
        if ( (c == pass[i-1] && c != pass[j-1]) ||
             (c != pass[i-1] && c == pass[j-1]))
          {
            result++;
          }  
      } else {
        std:: cout << "no match \n";
      }
    }
    std::cout << result << std::endl;
  }
};