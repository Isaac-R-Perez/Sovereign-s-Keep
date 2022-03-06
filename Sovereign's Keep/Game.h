#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <stdexcept>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include "Renderable.h"
#include "stb_image.h"

class Renderable;


/*
This class holds all references to all entities in the game. The main class. Will hold all functions for the game as well
*/





class Game {

public:

	Game();
	
	//Set up window and everything the game needs to function
	bool initialize();


	//will render all Renderable objects
	void render();

	//updates all Renderables
	void update();

	//deletes everything to shut down the program
	void cleanup();

	void setupBuffers();




	//getters and setters

	GLFWwindow* getWindow();

	GLuint getVBO() { return VBO; }
	GLuint getVAO() { return VAO; }

	GLuint getRenderablesProgID() { return renderables_programID; }

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

	GLuint EBO;

	//holds ALL renderables and in the correct render order
	/*
	1 - background object
	2 - player object
	3 - enemies
	4 - spells, basic attacks, effects
	5 - GUI objects
	6 - MENU objects
	*/
	std::priority_queue<Renderable*> renderQueue;

	//used for default buffer creation
	
	std::vector<GLfloat> vertices;

	GLuint indices[6];



};