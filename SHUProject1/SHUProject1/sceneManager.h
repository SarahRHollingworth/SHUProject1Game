#pragma once
#include "gameManager.h"
#include "uiManager.h"
#include "soundManager.h"

struct SceneManager {

  // Attributes
private:
  GameManager gameManager;
  UIManager uiManager;
  SoundManager soundManager;
  Utility utility;
  Sprite background_spr;
  Texture background_tx;
  enum class State { MENU, GAME };

public:
  void initialise(RenderWindow&);
  void update(RenderWindow&, float timeElapsed, bool* inputs);
  void render(RenderWindow&);

private:
  void initialiseBackground(RenderWindow&);
  void drawBackground(RenderWindow&);

  void playGame();
  void quitGame();
};