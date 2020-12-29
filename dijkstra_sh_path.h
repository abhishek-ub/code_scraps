#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>
#include <assert.h>

using u64 = uint64_t;

class Graph {
  struct Edge {
    u64 id;
    u64 wt;

    Edge(u64 i, u64 w)
    {
      id = i;
      wt = w;
    };
  };

  u64 _v_count;
  std::vector<std::vector<Edge>> _adj;

public:
  Graph(u64 v_count)
  {
    _adj.reserve(v_count);
    _v_count = v_count;
  };

  ~Graph() {};

  void add_edge(u64 u, u64 v, u64 w)
  {
    assert(u < _v_count);
    assert(v < _v_count);
    _adj[u].emplace_back(v, w);
    _adj[v].emplace_back(u, w);
  }

  void print_shortest_path(u64 origin)
  {
    assert(origin < _v_count);

    std::vector<u64> dist(_v_count, UINT64_MAX);

    auto comp = [] (Edge a, Edge b) {return a.wt > b.wt; };
    std::priority_queue<Edge, std::vector<Edge>, decltype(comp)> pq(comp);

    pq.emplace(origin, 0);
    dist[origin] = 0;

    while (!pq.empty()) {
      Edge top = pq.top();
      pq.pop();

      for (const auto& nbr : _adj[top.id]) {
        if (dist[nbr.id] > dist[top.id] + nbr.wt) {
          dist[nbr.id] = dist[top.id] + nbr.wt;
          pq.emplace(nbr.id, dist[nbr.id]);
        }
      }
    }

    for (int i = 0; i < dist.size(); ++i) {
      std::cout << "shorted dist from  origin " << origin << " to " << i << " = " << dist[i] << std::endl;
    }
  }
};

void test_dkst()
{
  Graph g(9);
  g.add_edge(0, 1, 4); 
  g.add_edge(0, 7, 8); 
  g.add_edge(1, 2, 8); 
  g.add_edge(1, 7, 11); 
  g.add_edge(2, 3, 7); 
  g.add_edge(2, 8, 2); 
  g.add_edge(2, 5, 4); 
  g.add_edge(3, 4, 9); 
  g.add_edge(3, 5, 14); 
  g.add_edge(4, 5, 10); 
  g.add_edge(5, 6, 2); 
  g.add_edge(6, 7, 1); 
  g.add_edge(6, 8, 6); 
  g.add_edge(7, 8, 7); 
  g.print_shortest_path(1);
}