#include <assert.h>

#include "SFML/Graphics.hpp"
#include "sceneManager.h"

using namespace sf;

//dimensions in 2D that are whole numbers
struct Dim2Di
{
	int x, y;
};

//dimensions in 2D that are floating point numbers
struct Dim2Df
{
	float x, y;
};

/*
A box to put Games Constants in.
These are special numbers with important meanings (screen width,
ascii code for the escape key, number of lives a player starts with,
the name of the title screen music track, etc.
*/
namespace GC
{
	//game play related constants to tweak
	const Dim2Di SCREEN_RES{ 1200,800 };

	const char ESCAPE_KEY{ 27 };

	const char a_KEY{ 65 };
	const char A_KEY{ 97 };
	const char d_KEY{ 68 };
	const char D_KEY{ 100 };
	const char SPACE_KEY{ 32 };
}



int main()
{
	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "Asteroid Hero");

	SceneManager sceneManager;
	sceneManager.initialise(window);

	Clock clock;

	// Start the game loop 
	while (window.isOpen())
	{
		float timeElapsed = clock.restart().asSeconds();

		// Process events
		Event event;
		bool inputs[3] = { false, false, false }; // 0 = left, 1 = right, 2 = fire;

		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == GC::ESCAPE_KEY)
					window.close();
			}
		}

		inputs[0] = Keyboard::isKeyPressed(Keyboard::A);
		inputs[1] = Keyboard::isKeyPressed(Keyboard::D);
		inputs[2] = Keyboard::isKeyPressed(Keyboard::Space);

		sceneManager.update(window, timeElapsed, inputs);

		// Clear screen
		window.clear();

		sceneManager.render(window);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}