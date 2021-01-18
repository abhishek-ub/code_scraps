#include <iostream>
#include <stdint.h>
#include <bitset>
#include <string>

using namespace std;

using u64 = uint64_t;

template <std::size_t N>
class NQueenProb {
  std::bitset<N>    _row;
  std::bitset<N>    _col;
  std::bitset<2*N>  _dia;
  std::bitset<2*N>  _dib;
  std::bitset<N*N>  _board;


  bool is_safe(u64 row, u64 col)
  {
    if (_row[row]) return false;
    if (_col[col]) return false;
    if (_dia[row + col]) return false;
    if (_dib[N + row - col]) return false;
    return true;
  }
public:
  bool solve(u64 col = 0)
  {
    // backtracking impl
    if (col >= N) return true;  // all queens places

    for (u64 i = 0; i < N; ++i) {
      if (is_safe(i, col)) {
        // place queen on the board
        _row.set(i);
        _col.set(col);
        _dia.set(i + col);
        _dib.set(N + i - col);
        _board.set(i * N + col);
        // move to next column
        if (solve(col + 1)) return true;
        // oterwise backtrack
        _row.reset(i);
        _col.reset(col);
        _dia.reset(i + col);
        _dib.reset(N + i - col);
        _board.reset(i * N + col);

      }
    }
    return false;
  }

  void print_board()
  {

    for (u64 i = 0; i < N; ++i) {
      for (u64 j = 0; j < N; ++j) {
        int queen = _board[i * N + j] ? 1 : 0;
        std::cout << std::to_string(queen) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
};

void solve_n_q_prob()
{
  NQueenProb<9> nq;
  if (nq.solve()) {
    nq.print_board();
  } else {
    std::cout << "no solution found\n";
  }
}