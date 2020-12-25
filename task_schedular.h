#include <iostream>
#include <cstdint>
#include <vector>

std::vector<uint64_t> get_topological_order(
  const std::unordered_map<uint64_t, std::vector<uint64_t>>&  tasks,
  std::unordered_map<uint64_t, uint64_t>& in_orders)
{
  std::vector<uint64_t> topological_order;

  std::queue<uint64_t> visit;

  // populate result with nodes having 0 in_order
  for (const auto in_order : in_orders) {
    if (in_order.second == 0) visit.push(in_order.first);
  }

  uint64_t total_visited = 0; 
  while (!visit.empty()) {
    auto node = visit.front(); 
    visit.pop();
    topological_order.push_back(node);

    if (tasks.find(node) != tasks.end()) {
      for (auto dep : tasks.at(node)) {
        in_orders[dep]--;
        if (in_orders[dep] == 0) visit.push(dep);
      }
    }
    total_visited++;
  }

  if (total_visited != in_orders.size()) throw std::invalid_argument("Tasks list dependancies have loop");
  return topological_order;
}

std::unordered_map<uint64_t, uint64_t> calculate_in_order(const std::unordered_map<uint64_t, std::vector<uint64_t>>&  tasks)
{
  std::unordered_map<uint64_t, uint64_t> in_orders;
  for (auto task : tasks) {
    if (in_orders.find(task.first) == in_orders.end()) {
      in_orders.emplace(task.first, 0);
    }
    for (auto nbr : task.second) {
      if (in_orders.find(nbr) == in_orders.end()) {
          in_orders.emplace(nbr, 1);
      } else {
          in_orders[nbr]++;
      }
    }
  }
  return in_orders;
}

/*
* @input
*   Map of task ids and its dependancies. {1 -> [2,3], 2 -> [3,4]}
*
* @output
*   List of task ids in order of execution if possible.
*/
std::vector<uint64_t> get_shedule(const std::unordered_map<uint64_t, std::vector<uint64_t>>&  tasks)
{
  // calculate in order
  auto in_orders = calculate_in_order(tasks);
  // get topological sort
  return get_topological_order(tasks, in_orders);
}

void get_shedule_test()
{
  std::unordered_map<uint64_t, std::vector<uint64_t>> tasks {
    {5, std::vector<uint64_t>{2, 0}},
    {4, std::vector<uint64_t>{0, 1}},
    {2, std::vector<uint64_t>{3}},
    {3, std::vector<uint64_t>{1}}
  };
  for (auto task : get_shedule(tasks)) std::cout << task << ", ";
}