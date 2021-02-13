#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

using u64 = uint64_t;

class LRUchar {
  std::list<char> _char_list;
  std::unordered_map<char, std::list<char>::iterator> _map;

public:
  LRUchar() {}

  void insert(char c)
  {
    if (_map.find(c) != _map.end()) {
        _char_list.erase(_map[c]);
    }
    _char_list.emplace_front(c);
    _map[c] = _char_list.begin();
  }

  char get_lru()
  {
    return _char_list.back();
  }
};

char get_first_non_repeating_char(const std::string& str)
{
  LRUchar lru;
  for (char c : str) {
    lru.insert(c);
  }
  return lru.get_lru();
}

void first_non_repeating_char_test()
{
  std::string test = "aaabbbbcccc";
  char val = get_first_non_repeating_char(test);
  std::cout << val << std::endl;
  //assert(val == 'a');
}