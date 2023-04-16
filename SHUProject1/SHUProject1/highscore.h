#pragma once
#include <assert.h>

#include "gameManager.h"

struct Highscore {

  // Attributes
private:
  GameManager* gm_ptr;
  std::vector<int> scores;
  
  // Functions
public:
  void initialise(GameManager*);
  void update();

private:
  void AddScore(int);
  void ReorderHighscoreTable();
};