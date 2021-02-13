#include <iostream>
#include <string>

bool is_match(const std::string& str, const std::string& pat)
{

}

void is_match_test()
{
  std::cout << is_match("aks", "a*")    << std::endl;
  std::cout << is_match("aks", "a.*")   << std::endl;
  std::cout << is_match("aks", "a*s")   << std::endl;
  std::cout << is_match("aks", "a.*s")  << std::endl;
  std::cout << is_match("aks", "a.*k")  << std::endl;
}