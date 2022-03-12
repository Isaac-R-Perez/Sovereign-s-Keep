#include "Game.h"

/*
	Have a TODO list here?


	> Add status to be applied to objects of the Character class
	> Define and code each status
	> Create an enemy class if we need one

	> Finish player class by having logic to handle creating basic attacks and spell combo/casting
	> Finish controls by adding basic attack and spell combination
	> Add a BasicBullet class which is a renderable that holds all of the logic for the player's basic attack, including being modified by statuses and buffs
	> Add pause functionality into the code, the game should stop "updating" everything that is not a menu but should still render normally
	> Create the GUI system
	> Add a menu system
	> Implement all 113 spells into the game, including animations and logic for everything...
	> Implement more enemies
	> Add main menu and all menus needed for the game: pause, main, start, unlocks, options
	> Add file system to store and track all player unlocks
	> Add monster soul mechanic to unlock new elements and stuff for the player
	> Implement a randomized wave system in conjunction will a level system that runs on a timer
	> Audio system
	> Add final boss??



	>implement mechanic for "single element spells", basically just element buffs that scale with element level

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

		game.update(deltaT);

		game.render();

		glfwSwapBuffers(game.getWindow());
		glfwPollEvents();


	}

	game.cleanup();

	return 0;
}