#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include <stdint.h>

using namespace std;
using u64 = uint64_t;

bool is_part_sum_possible(const vector<u64>& vec, u64 sum)
{
  u64 part_sum = 0;
  u64 parts = 1;
  for (u64 val : vec) {
    part_sum += val;
    if (part_sum > sum) {
      part_sum = val;
      parts++;
    }
  }
  if (parts <= 5) return true;
  return false;
}

u64 get_min_sum_of_shards(const vector<u64>& vec)
{
  if (vec.size() < 5) return -1;
  u64 start = *max_element(vec.begin(), vec.end());
  u64 end   = accumulate(vec.begin(), vec.end(), 0);

  while (start < end) {
    u64 mid = (start / 2) + (end / 2);
    if (is_part_sum_possible(vec, mid)) {
        end = mid;
    } else {
        start = mid + 1;
    }
  }
  return end;
}

void shard_array_test()
{
  cout << get_min_sum_of_shards({6,4,2,11,1,1,1,1,1,1,10,10}) << endl;
  cout << get_min_sum_of_shards({5,4,4,4,5}) << endl;
}