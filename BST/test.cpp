#include <iostream>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <vector>
#include "bst.h"

constexpr int MAXI = 100;

int main() {
  int test[MAXI];
  int n;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  for (int i = 0; i < MAXI; i++)
    test[i] = i;
  std::shuffle(test, test+MAXI,  std::default_random_engine(seed));
}
