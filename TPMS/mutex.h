#pragma once
#include <atomic> //test_and_set
#include <thread>
#include <chrono>
#include <iostream>


class mutex {
  std::atomic<bool> _locked{false};
  
  public:
    void lock() {
      while(true) {
        bool expected = false;
        if (_locked.compare_exchange_strong(expected, true, std::memory_order_acquire)) {
          return;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(50));
      }

    }

    bool try_lock() {
      bool expected = false;
      return _locked.compare_exchange_strong(expected, true, std::memory_order_acquire);
    }

    void unlock() {
      _locked.store(false, std::memory_order_release);
    }
};