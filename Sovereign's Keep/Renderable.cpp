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

	canCollide = false;

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



void Renderable::flip() {

	//apply a negative scale to the matrix
	glm::mat4 inverted = getO2W() * glm::scale(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 0.0f));
	setO2W(inverted);
}


bool Renderable::checkCollision(Renderable* b) {

	//check if b's hitbox's TOP LEFT is inside of the hitbox
	if (b->getHitBox().topLeft.x > hitbox.topLeft.x && b->getHitBox().topLeft.x < hitbox.topRight.x) {
		if (b->getHitBox().topLeft.y < hitbox.topLeft.y && b->getHitBox().topLeft.y > hitbox.bottomLeft.y) {
			return true;
		}
	}

	if (hitbox.topLeft.x > b->getHitBox().topLeft.x && hitbox.topLeft.x < b->getHitBox().topRight.x) {
		if (hitbox.topLeft.y < b->getHitBox().topLeft.y &&  hitbox.topLeft.y > b->getHitBox().bottomLeft.y) {
			return true;
		}
	}
	

	//check if b's hitbox's TOP RIGHT is inside of the hitbox
	if (b->getHitBox().topRight.x > hitbox.topLeft.x && b->getHitBox().topRight.x < hitbox.topRight.x) {
		if (b->getHitBox().topRight.y < hitbox.topLeft.y && b->getHitBox().topRight.y > hitbox.bottomLeft.y) {
			return true;
		}
	}

	if ( hitbox.topRight.x > b->getHitBox().topLeft.x && hitbox.topRight.x < b->getHitBox().topRight.x) {
		if ( hitbox.topRight.y < b->getHitBox().topRight.y &&  hitbox.topRight.y > b->getHitBox().bottomRight.y) {
			return true;
		}
	}




	//check if b's hitbox's BOTTOM LEFT is inside of the hitbox
	if (b->getHitBox().bottomLeft.x > hitbox.topLeft.x && b->getHitBox().bottomLeft.x < hitbox.topRight.x) {
		if (b->getHitBox().bottomLeft.y < hitbox.topLeft.y && b->getHitBox().bottomLeft.y > hitbox.bottomLeft.y) {
			return true;
		}
	}
	if ( hitbox.bottomLeft.x > b->getHitBox().bottomLeft.x &&  hitbox.bottomLeft.x < b->getHitBox().bottomRight.x) {
		if ( hitbox.bottomLeft.y < b->getHitBox().topLeft.y &&  hitbox.bottomLeft.y > b->getHitBox().bottomLeft.y) {
			return true;
		}
	}




	//check if b's hitbox's BOTTOM RIGHT is inside of the hitbox
	if (b->getHitBox().bottomRight.x > hitbox.topLeft.x && b->getHitBox().bottomRight.x < hitbox.topRight.x) {
		if (b->getHitBox().bottomRight.y < hitbox.topLeft.y && b->getHitBox().bottomRight.y > hitbox.bottomLeft.y) {
			return true;
		}
	}
	if (hitbox.bottomRight.x > b->getHitBox().bottomLeft.x &&  hitbox.bottomRight.x < b->getHitBox().bottomRight.x) {
		if ( hitbox.bottomRight.y < b->getHitBox().topRight.y &&  hitbox.bottomRight.y >  b->getHitBox().bottomRight.y) {
			return true;
		}
	}



	return false;
}