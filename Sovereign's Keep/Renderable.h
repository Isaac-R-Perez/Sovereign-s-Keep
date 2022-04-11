#pragma once
#include "Game.h"
#include "GLM/gtc/type_ptr.hpp"

class Game;
/*
This class will be the parent of everything in that game that can be rendered, such as the player, enemies, menu system, and GUI entities
*/

struct HitBox {
	glm::vec4 topLeft;
	glm::vec4 topRight;
	glm::vec4 bottomLeft;
	glm::vec4 bottomRight;
	glm::vec3 origin;

	/*
	CHANGE THIS TO BE A RECTANGLE, DO NOT FORCE IT TO BE A SQUARE!
	*/

	HitBox() {
		topLeft = glm::vec4(1000.0f, 1000.0f, 0.0f, 1.0f);
		topRight = glm::vec4(1000.0f, 1000.0f, 0.0f, 1.0f);
		bottomLeft = glm::vec4(1000.0f, 1000.0f, 0.0f, 1.0f);
		topRight = glm::vec4(1000.0f, 1000.0f, 0.0f, 1.0f);
		origin = glm::vec4(1000.0f, 1000.0f, 0.0f, 1.0f);
	}

	//in every renderable update, send the renderable's origin and hitbox lengths
	void updateHitBox(glm::vec3 og, float xL, float xR, float yB, float yT) {
		origin = og;
		topLeft = glm::vec4(origin.x - xL, origin.y + yT, 0.0f, 1.0f);
		topRight = glm::vec4(origin.x + xR, origin.y + yT, 0.0f, 1.0f);
		bottomLeft = glm::vec4(origin.x - xL, origin.y - yB, 0.0f, 1.0f);
		bottomRight = glm::vec4(origin.x + xR, origin.y - yB, 0.0f, 1.0f);
	}


};


class Renderable {

public:


	Renderable(Game* g, int rOrder, int defaultSpriteSheet);
	~Renderable() {}

	//these are overriden!
	virtual void update(double dt); //update the Renderable

	virtual void render(); //draw Renderable to the screen




	int renderOrder; //from 1 - 6?


	//this function adds this renderable to the pendingDestroy vector
	void kill() { destroy = true; }

	bool shouldDestroy() { return destroy; }

	//flips renderable horizontally
	void flip();

	//this function will return TRUE, if a given renderable's hitbox is WITHIN the caller's hitbox
	bool checkCollision(Renderable* b);


	/*
		GETTERS AND SETTERS
	*/

	Game* getGame() { return game; }

	void setO2W(glm::mat4 s) { objectToWorld = s; }
	glm::mat4& getO2W() { return objectToWorld; }

	glm::vec3& getOrigin() { return origin; }
	void setOrigin(glm::vec3 o) { origin = o; }


	GLuint getTexture() { return texture; }

	void setTexture(int spriteSheet);

	//
	void updatePosition(glm::mat4 transform);


	void setWidth(float w) {	width = w;}
	void setHeight(float h) { height = h; }

	float getWidth() { return width; }
	float getHeight() { return height; }

	void resize(float w, float h);

	void resetSize();

	HitBox& getHitBox() { return hitbox; }

	bool getCanCollide() { return canCollide; }
	void setCanCollide(bool b) { canCollide = b; }
private:

	

	//origin
	glm::vec3 origin;

	//These will store the floats that modify the intial vertices.
	float width;
	float height;
	GLuint texture;


	//transformation matrix
	glm::mat4 objectToWorld;

	//this pointer allows every renderable object to be able to call game functions
	//such as creating new enemies.
	Game* game;

	//if this is true, the game engine will automatically destory in the next update call
	bool destroy;

	//this is a RECTANGLE, pass an origin to the hitbox, typically the renderable's origin
	//a hitbox consists of 4 vec3s, UPDATE EACH POINT in the hitbox
	HitBox hitbox;

	//false if newly created
	bool canCollide;
};




