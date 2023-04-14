#pragma once
#include "gameManager.h"

struct SceneManager {

  // Attributes
private:
  GameManager gameManager;
  Sprite background_spr;
  Texture background_tx;
  enum class State { MENU, GAME };

public:
  void initialise(RenderWindow&);
  void update(RenderWindow&, float timeElapsed);
  void render(RenderWindow&);

private:
  void initialiseBackground(RenderWindow&);
  void drawBackground(RenderWindow&);

  void playGame();
  void quitGame();
};