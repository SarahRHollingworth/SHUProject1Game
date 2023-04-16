#pragma once
#include <cstdlib>
#include <ctime>

struct RandomNumberGenerator {
public:
  void seed(time_t);
  int getRandomNumber(int min, int max);
};