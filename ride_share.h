#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
//#include <barrier>
#include <queue>
#include <stdlib.h>

class Ride {
  std::mutex                            _mtx;
  std::queue<std::condition_variable*>  _r_q;
  std::queue<std::condition_variable*>  _b_q;
  //std::barrier                          _gate;

  bool got_ride()
  {
    //std::cout << " _r_q.size() " << _r_q.size() << " _b_q.size() " << _b_q.size() << std::endl;
    if ((_r_q.size() >= 2) && (_b_q.size() >= 2)) {
      _r_q.front()->notify_one(); _r_q.pop();
      _r_q.front()->notify_one(); _r_q.pop();
      // 2 rs 2 ds
      _b_q.front()->notify_one(); _b_q.pop();
      _b_q.front()->notify_one(); _b_q.pop();
      return true;
    }

    if (_r_q.size() >= 4) {
      for (int i = 0; i < 4; ++i) {
        _r_q.front()->notify_one(); _r_q.pop();
      }
      return true;
    }

    if (_b_q.size() >= 4) {
      for (int i = 0; i < 4; ++i) {
        _b_q.front()->notify_one(); _b_q.pop();
      }
      return true;
    }

    return false;
  }

  void book_common(std::queue<std::condition_variable*>& queue)
  {
    std::unique_lock lk(_mtx);
    std::condition_variable signal;
    queue.emplace(&signal);

    if (!got_ride()) {
      signal.wait(lk);
    }
    //lk.unlock();
    //_gate.arrive_and_wait();
  }

public:
  //Ride() : _gate(4, []{std::cout << "Ride filled \n";}){}
  void book_r(int i)
  {
    std::cout << "RedRider " << i <<  " book\n"; 
    book_common(_r_q);
    std::cout << "RedRider " << i <<  " on the way\n"; 
  }

  void book_b(int i)
  {
    std::cout << "BlueRider " << i <<  " book\n"; 
    book_common(_b_q);
    std::cout << "BlueRider " << i <<  " on the way\n"; 
  }
};


/*
* Only allow rides when we have either
* 1. All 4 RedRider
* 2. All 4 BlueRider
* 3. 2 RedRider and 2 RedRider
*/
void ride_share_test()
{
  Ride r;  
  auto t1 = std::thread([&](){
    r.book_r(1);
  });
  auto t2 = std::thread([&](){
    r.book_r(2);
  });
  auto t3 = std::thread([&](){
    r.book_b(1);
  });
  auto t4 = std::thread([&](){
    r.book_b(2);
  });
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  
  /*
  for (int i = 0; i < 100 ++i) {
    std::thread([&](){
      if (rand() % 2 == 0) {
        r.book_r(i);
      } else {
        r.book_b(i);
      }
    });
  }
  */
}