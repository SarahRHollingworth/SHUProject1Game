#include "utility.h"

void Utility::BubbleSort(std::vector<int>* vector) {
  for (int i = 0; i < vector->size() - 1; ++i)
  {
    for (int j = 0; j < vector->size() - i - 1; ++i)
    {
      Sort(vector->at(j), vector->at(j + 1));
    }
  }
}

void Utility::Sort(int& num1, int& num2) {
  if (num1 > num2)
    Swap(num1, num2);
}

void Utility::Swap(int& num1, int& num2) {
  int temp = num1;
  num1 = num2;
  num2 = temp;
}