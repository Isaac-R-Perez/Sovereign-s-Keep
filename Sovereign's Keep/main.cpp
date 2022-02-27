#include "Game.h"

/*
	Have a TODO list here?
	> Add status to be applied to objects of the Character class
	> Define and code each status
	> Create an enemy class if we need one

*/

int main() {
	//game class
	Game game;

	double deltaT;

	if (!game.initialize()) {
		return -1;
	}

	while (!glfwWindowShouldClose(game.getWindow())) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		deltaT = static_cast<double> (1.0f / 60.0f); //1 tick, 1/60th of a second


		game.update();

		game.render();

		glfwSwapBuffers(game.getWindow());
		glfwPollEvents();


	}

	game.cleanup();

	return 0;
}