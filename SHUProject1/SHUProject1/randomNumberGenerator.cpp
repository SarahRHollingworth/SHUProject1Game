#include "randomNumberGenerator.h"

void RandomNumberGenerator::seed(time_t time)
{
  std::srand(time);
}

int RandomNumberGenerator::getRandomNumber(int min, int max)
{
  return min + (std::rand() % (max - min + 1));
}
