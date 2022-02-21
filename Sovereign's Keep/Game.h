#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <stdexcept>

/*
This class holds all references to all entities in the game. The main class. Will hold all functions for the game as well
*/

class Game {

public:
	
	//Set up window and everything the game needs to function
	bool initialize();

	//will render all Renderable objects
	void render();

	//updates all Renderables
	void update();

	//deletes everything to shut down the program
	void cleanup();



	//getters and setters

	GLFWwindow* getWindow();



private:

	//window that everything is rendered to
	GLFWwindow* window;

	glm::vec3 cameraPosition; //will start at (0.0, 0.0, 1.0), which is pointing down the z axis


	//holds the program for the vertex and fragment shaders
	GLuint renderables_programID;

	//holds the program for the GUI vertex and fragment shaders
	GLuint gui_programID;

	//Vertex Array Object for the game
	GLuint VAO;

	GLuint VBO;




};