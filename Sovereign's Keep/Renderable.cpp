#include "Renderable.h"

/*
	a defalt renderable has 6 total points, it is essentailly a square from (-0.1, -0.1) to (0.1, 0.1)
	with an origin at 0.0, 0.0
*/


/*
	This function takes in the width, height, color channels, and the path of the image to generate and bind a texture to this renderable.
	These must be given every time a new renderable is created!
*/

void Renderable::setTexture(int spriteSheet) {
	texture = game->getTextureFromMap(spriteSheet);
}


Renderable::Renderable(Game* g, int rOrder, int defaultSpriteSheet) {
	game = g;
	renderOrder = rOrder;

	objectToWorld = glm::mat4(1.0f);
	origin = glm::vec3(0.0f, 0.0f, 0.0f);

	setTexture(defaultSpriteSheet); //generate the texture for this renderable

	destroy = false;

}


void Renderable::render() {

}

void Renderable::update(double dt)  {

}

void Renderable::updatePosition(glm::mat4 transform) {
	objectToWorld = transform * objectToWorld;
	origin = transform * glm::vec4(origin,1.0);
}

void Renderable::resize(float w, float h) {
	glm::mat4 RESIZE = glm::mat4(1.0f);
	RESIZE = glm::scale(glm::mat4(1.0f), glm::vec3(w, h, 0.0f)) * RESIZE;
	RESIZE = glm::translate(glm::mat4(1.0f), glm::vec3(origin.x, origin.y, 0.0f)) * RESIZE;
	
	objectToWorld = RESIZE;
}