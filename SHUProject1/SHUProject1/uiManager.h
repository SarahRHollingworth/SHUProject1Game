#pragma once
#include <assert.h>
#include "SFML/Graphics.hpp"

#include "gameManager.h"
#include "highscore.h"

using namespace sf;

struct UIManager {

  // Attributes
private:
  GameManager* gm_ptr;
  Highscore highscore;

  // Functions
public:
  void initialise(RenderWindow&, GameManager*);
  void update(RenderWindow&);
  void render(RenderWindow&);

private:
  void displayScore();
  void displayHealth();
  void displayToolbar();
};