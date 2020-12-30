#include <iostream>
#include <vector>
#include <stdint.h>
#include <assert.h>

using u64 = uint64_t;

class UGraph {
  u64               _size;
  std::vector<bool> _visited;
  std::vector<bool> _rec_stack;

  std::vector<std::vector<u64>> _adj;

  bool g_dsf_cycle(u64 node)
  {
    if (_visited[node]) return false;

    _visited[node]   = true;
    _rec_stack[node] = true;

    for (u64 i : _adj[node]) {
      if (_visited[i] && _rec_stack[i]) return true;

      if (!_visited[i] && g_dsf_cycle(i)) return true;
    }
    return false;
  }

public:
  UGraph(u64 size):
    _size(size),
    _visited(size, false),
    _rec_stack(size, false),
    _adj(size)
  {
  }

  void add_edge(u64 u, u64 v)
  {
    assert(u < _size);
    assert(v < _size);

    _adj[u].push_back(v);
    _adj[v].push_back(u);
  }

  bool has_cycles()
  {
    for (u64 i = 0; i < _size; ++i) {
      if (g_dsf_cycle(i)) return true;
    }
    return false;
  }
};


void find_cycles_test()
{
  UGraph g(5);
  g.add_edge(0, 1); 
  g.add_edge(0, 2); 
  g.add_edge(1, 2); 
  g.add_edge(2, 0); 
  g.add_edge(2, 3); 
  g.add_edge(3, 3); 
  
  if (g.has_cycles()) {
    std::cout << "directed graph has cycles \n";
  }
}