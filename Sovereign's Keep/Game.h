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
#include <map>
#include "Renderable.h"
#include "stb_image.h"

class Renderable;


/*
This class holds all references to all entities in the game. The main class. Will hold all functions for the game as well
*/

const float SCREEN_Y_MOVE_MODIFIER = 1.7777f;

enum class SPRITE_SHEETS
{
	player_default, player_idle, player_walking, player_attacking, player_casting, background,
};


class Game {

public:

	//this is the int value for the map of all textures, use the names included here to generate new textures in the loadAllTextures function.
	


	Game();
	
	//Set up window and everything the game needs to function
	bool initialize();


	//will render all Renderable objects
	void render();

	//updates all Renderables
	void update(double dt);

	//deletes everything to shut down the program
	void cleanup();

	void setupBuffers();


	void renderableToPendingAdd(Renderable* r);

	//this function will generate every single texture into the map of all textures
	void loadAllTextures();

	//this function generates one specified texture
	void generateTexture(GLuint &tex, int w, int h, int nrC, std::string path);

	//input TOP-LEFT xy, TOP_RIGHT xy, BOTTOM_RIGHT xy texture coordinates
	void setTextureCoordinates(float TRx, float TRy, float BRx, float BRy, float BLx, float BLy, float TLx, float TLy);

	void resetTextureCoordinates();

	//getters and setters

	GLFWwindow* getWindow();

	GLuint getVBO() { return VBO; }
	GLuint getVAO() { return VAO; }

	GLuint getRenderablesProgID() { return renderables_programID; }

	bool isPaused() { return paused; }
	bool setPaused(bool p) { paused = p; }

	bool getSpellComboMode() { return spellComboMode; }
	void setSpellComboMode(bool b) { spellComboMode = b; }
	Renderable* getPlayer() { return player; }

	//send in the enum name that corresponds to the spritesheet, should get a reference to that texture in the form of a GLuint
	GLuint& getTextureFromMap(int a);




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
	std::multimap<int, Renderable*> renderQueue;

	//will hold all sprite sheets for EVERYTHING IN THE GAME, use an ENUM for the int
	std::map<int, GLuint> allSpriteSheets;

	//used for generating textures
	unsigned char* data;
	GLuint generatedTexture;

	std::vector<Renderable*> pendingAdd;
	std::vector<Renderable*> pendingDestroy;

	//used for default buffer creation
	
	std::vector<GLfloat> vertices;

	GLuint indices[6];

	bool paused; //if the game is paused, render everything as normal, but only update the menus and track mouse activity

	//use this pointer for ease of referencing the player, be sure to also add/change this pointer to/and the renderQueue!
	Renderable* player;

	//true if SHIFT is held
	bool spellComboMode;

};